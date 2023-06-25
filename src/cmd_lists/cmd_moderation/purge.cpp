#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <cmd_builder/cmd_layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    const auto channel_id = event.command.channel_id;
    const auto reason_param = event.get_parameter("reason");

    int purge_count = 0;

    const int amount_division = amount_messages / 99;
    const int amount_remain = amount_messages % 99;

    for (size_t i = 1; i <= amount_division; i++)
    {
        const auto message_map = client.messages_get_sync(channel_id, 0, 0, 0, i * 99);
        std::vector<dpp::snowflake> delete_ids;

        for (const auto& message : message_map)
        {
            if (message.second.sent < time(0) + 1209600 || message.second.pinned || message.second.author.username.empty())
                continue;

            delete_ids.emplace_back(message.first);
        }

        switch (delete_ids.size())
        {
        case 0:
            break;

        case 1:
            client.message_delete(delete_ids.at(0), channel_id);
            break;

        default:
            client.message_delete_bulk(delete_ids, channel_id);
            break;
        }

        purge_count += delete_ids.size();
    }

    const auto message_map = client.messages_get_sync(channel_id, 0, 0, 0, amount_remain);
    std::vector<dpp::snowflake> delete_ids;

    for (const auto& message : message_map)
    {
        if (message.second.sent < time(0) + 1209600 || message.second.pinned || message.second.author.username.empty())
            continue;
            
        delete_ids.emplace_back(message.first);
    }

    switch (delete_ids.size())
    {
    case 0:
        break;

    case 1:
        client.message_delete(delete_ids.at(0), channel_id);
        break;

    default:
        client.message_delete_bulk(delete_ids, channel_id);
        break;
    }

    purge_count += delete_ids.size();

    auto description = fmt::format("Found and purged {} message{}", purge_count, purge_count > 1 ? "s" : "");
    send_success(description, event);
}