#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <builder/layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    bool is_valid_to_purge = true;
    const auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    const auto reason_param = event.get_parameter("reason");
    const auto reason = std::holds_alternative<std::string>(reason_param)
        ? std::get<std::string>(reason_param)
        : "No reason provided";

    const auto amount_division = amount_messages / 100;
    const auto amount_mod = amount_messages % 100;

    client.messages_get(event.command.channel_id, 0, 0, 0, amount_messages, [&](const dpp::confirmation_callback_t& callback)
        {
            if (!callback.is_error())
            {
                std::vector<dpp::snowflake> message_ids;
                const auto message_map = std::get<dpp::message_map>(callback.value);

                for (const auto& messages : message_map)
                    message_ids.emplace_back(messages.second);

                std::vector<time_t> message_collector;
                const auto collector_map = std::get<dpp::message_map>(callback.value);

                for (const auto& messages : collector_map)
                    message_collector.emplace_back(messages.second.sent);

                if (message_collector.at(message_collector.size() - 1) < 1209601)
                    is_valid_to_purge = false;
            }
        });

    if (is_valid_to_purge)
    {
        switch (amount_mod)
        {
        case 0: break;
        default:
            for (int i = 1; i < amount_mod + 1; i++)
            {
                client.messages_get(event.command.channel_id, 0, 0, 0, 100, [&](const dpp::confirmation_callback_t& callback)
                    {
                        if (!callback.is_error())
                        {
                            std::vector<dpp::snowflake> message_ids;
                            const auto message_map = std::get<dpp::message_map>(callback.value);

                            for (const auto& messages : message_map)
                                message_ids.emplace_back(messages.second);

                            client.message_delete_bulk(message_ids, event.command.channel_id);
                        }
                    });
            }
        }

        client.messages_get(event.command.channel_id, 0, 0, 0, amount_division, [&](const dpp::confirmation_callback_t& callback)
            {
                if (!callback.is_error())
                {
                    std::vector<dpp::snowflake> message_ids;
                    const auto message_map = std::get<dpp::message_map>(callback.value);

                    for (const auto& messages : message_map)
                        message_ids.emplace_back(messages.second);

                    client.message_delete_bulk(message_ids, event.command.channel_id);
                }
            });

        const auto description = fmt::format("Deleted {} messages in <#{}>", amount_messages, event.command.channel_id);
        send_success(description, event);
    }
    else
        send_error("Cannot delete too old messages, please try again", event);
}