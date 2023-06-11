#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <cmd_builder/cmd_layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    const auto channel_id = event.command.channel_id;
    const auto reason_param = event.get_parameter("reason");

    const auto reason = std::holds_alternative<std::string>(reason_param)
        ? std::get<std::string>(reason_param)
        : "No reason provided";

    if (amount_messages <= 100)
    {
        std::function<int()> count_messages_deleted = [&]() -> int
        {
            int count = 0;

            client.messages_get(channel_id, 0, 0, 0, amount_messages, [&](const dpp::confirmation_callback_t& callback)
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
                            break;
                        default:
                            client.message_delete_bulk(message_ids, channel_id);
                            count += message_ids.size();
                            break;
                        }
                    }
                });

            return count;
        };

        int count_deleted = count_messages_deleted();

        if (count_deleted > 0)
        {
            auto description = fmt::format("Found and purged {} messages", count_deleted);
            send_success(description, event);
        }
        else
            send_error("Cannot delete messages older than 14 days", event);
    }
    else
    {
        std::function<int()> count_messages_deleted = [&]() -> int
        {
            int count = 0;

            const int amount_division = amount_messages / 99;
            const int amount_remain = amount_messages % 99;

            for (size_t i = 1; i <= amount_division; i++) {
                client.messages_get(channel_id, 0, 0, 0, i * 99, [&](const dpp::confirmation_callback_t& callback)
                    {
                        if (!callback.is_error())
                        {
                            const auto message_map = std::get<dpp::message_map>(callback.value);
                            std::vector<dpp::snowflake> message_ids;

                            for (const auto& message : message_map) {
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
                                break;
                            default:
                                client.message_delete_bulk(message_ids, channel_id);
                                count += message_ids.size();
                                break;
                            }
                        }
                    });
            }

            client.messages_get(channel_id, 0, 0, 0, amount_remain, [&](const dpp::confirmation_callback_t& callback)
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
                            break;
                        default:
                            client.message_delete_bulk(message_ids, channel_id);
                            count += message_ids.size();
                            break;
                        }
                    }
                });

            return count;
        };

        int count_deleted = count_messages_deleted();

        if (count_deleted > 0)
        {
            auto description = fmt::format("Found and purged {} messages", count_deleted);
            send_success(description, event);
        }
        else
            send_error("Cannot delete messages older than 14 days", event); 
    }
}