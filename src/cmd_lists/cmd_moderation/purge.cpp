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

    client.messages_get(event.command.channel_id, 0, 0, 0, amount_messages, [&](const dpp::confirmation_callback_t& callback)
        {
            if (!callback.is_error())
            {
                std::vector<time_t> message_collector;
                const auto collector_map = std::get<dpp::message_map>(callback.value);

                for (const auto& messages : collector_map)
                    message_collector.emplace_back(messages.second.sent);

                if (message_collector.at(message_collector.size() - 1) < 1209601)
                    is_valid_to_purge = false;

                if (is_valid_to_purge)
                {
                    std::vector<dpp::snowflake> message_ids;
                    const auto message_map = std::get<dpp::message_map>(callback.value);

                    for (const auto& messages : message_map)
                    {
                        if (!messages.second.pinned)
                            message_ids.emplace_back(messages.first);
                    }

                    for (int i = 0; i < message_ids.size(); i++)
                    {
                        std::vector<dpp::snowflake> delete_id;
                        delete_id.push_back(message_ids.at(i));

                        if (delete_id.size() >= 100 || delete_id.at(i) == message_ids.at(message_ids.size() - 1))
                        {
                            client.message_delete_bulk(delete_id, event.command.channel_id);
                            delete_id.clear();
                        } 
                    }
                }
                else
                    send_error("Cannot delete too old messages, please try again", event);
            }
        });
}