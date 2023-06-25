#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <cmd_builder/cmd_layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    const auto channel_id = event.command.channel_id;
    const auto reason_param = event.get_parameter("reason");

    int purge_count = 0;
    
    if (amount_messages == 1)
    {
        const auto message_map = client.messages_get_sync(channel_id, 0, 0, 0, 1);
        auto purge = purge_engine(message_map, channel_id, client, purge_count);

        purge_count += purge;

        auto description = fmt::format("Found and purged {} message", purge_count);
        send_success(description, event);
    }
    else
    {
        if (amount_messages <= 100)
        {
            const auto message_map = client.messages_get_sync(channel_id, 0, 0, 0, amount_messages);
            auto purge = purge_engine(message_map, channel_id, client, purge_count);

            purge_count += purge;

            auto description = fmt::format("Found and purged {} message{}", purge_count, purge_count > 1 ? "s" : "");
            send_success(description, event);
        }
        else
        {
            const int amount_division = amount_messages / 99;
            const int amount_remain = amount_messages % 99;

            for (size_t i = 1; i <= amount_division; i++)
            {
                const auto message_map = client.messages_get_sync(channel_id, 0, 0, 0, i * 99);
                auto purge = purge_engine(message_map, channel_id, client, purge_count);

                purge_count += purge;
            }

            const auto message_map = client.messages_get_sync(channel_id, 0, 0, 0, amount_remain);
            auto purge = purge_engine(message_map, channel_id, client, purge_count);

            purge_count += purge;

            auto description = fmt::format("Found and purged {} message{}", purge_count, purge_count > 1 ? "s" : "");
            send_success(description, event);
        }
    }
}