#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <cmd_builder/cmd_layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    const auto channel_id = event.command.channel_id;
    const auto reason_param = event.get_parameter("reason");
    
    int count = 0;
    int count_deleted = 0;

    const auto reason = std::holds_alternative<std::string>(reason_param)
        ? std::get<std::string>(reason_param)
        : "No reason provided";

    auto purge_callback = [&](const dpp::confirmation_callback_t& callback)
    {
        if (!callback.is_error())
        {
            const auto message_map = std::get<dpp::message_map>(callback.value);
            std::vector<dpp::snowflake> message_ids;

            for (const auto& message : message_map)
            {
                if (time(0) - message.second.sent > 1209600 || message.second.author.username.empty() || message.second.pinned)
                    continue;

                message_ids.emplace_back(message.first);
            }

            switch (message_ids.size())
            {
            case 0: break;
            case 1:
                client.message_delete(message_ids.at(0), channel_id);

                count++;
                count_deleted = count;

                break;
            default:
                client.message_delete_bulk(message_ids, channel_id);

                count += message_ids.size();
                count_deleted = count;

                break;
            }
        }
    };

    client.messages_get(channel_id, 0, 0, 0, amount_messages, purge_callback);

    if (count_deleted > 0)
    {
        auto description = fmt::format("Found and purged {} messages", count_deleted);
        send_success(description, event);
    }
    else
        send_error("Cannot delete messages older than 14 days", event);
}