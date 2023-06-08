#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <builder/layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    bool is_valid_to_purge = true;
    bool is_purged = false;

    auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    const auto reason_param = event.get_parameter("reason");
    const auto reason = std::holds_alternative<std::string>(reason_param)
        ? std::get<std::string>(reason_param)
        : "No reason provided";

    client.messages_get(event.command.channel_id, 0, 0, 0, 2000, [&](const dpp::confirmation_callback_t& callback)
        {
            if (!callback.is_error())
            {
                std::vector<dpp::snowflake> message_ids;
                const auto message_map = std::get<dpp::message_map>(callback.value);

                for (const auto& messages : message_map)
                {
                    if (messages.second.sent > time(0) + 1209600)
                    {
                        is_valid_to_purge = false;
                        break;
                    }
                    else
                    {
                        if (!messages.second.pinned)
                            message_ids.emplace_back(messages.first);
                        else
                            continue;
                    }
                }

                std::vector<dpp::snowflake> delete_ids;
                for (int i = 0; i < amount_messages; ++i)
                    delete_ids.push_back(message_ids.at(i));

                if (is_valid_to_purge)
                {
                    if (delete_ids.size() == 1)
                    {
                        client.message_delete(delete_ids.at(0), event.command.channel_id);
                        is_purged = true;
                    }
                    else
                    {
                        const auto amount_division = message_ids.size() / 99;

                        switch (amount_division)
                        {
                        case 0: break;
                        default:
                            for (int i = 1; i <= amount_division; ++i)
                            {
                                std::vector<dpp::snowflake> delete_limit;
                                for (int j = 0; j < i + 99; ++j)
                                    delete_limit.push_back(delete_ids.at(j));

                                client.message_delete_bulk(delete_limit, event.command.channel_id);
                                delete_limit.clear();
                            }
                        }

                        const auto amount_remain = amount_messages - amount_division * 99;
                        std::vector<dpp::snowflake> remain_delete;

                        for (int i = amount_messages - amount_remain; i < amount_messages; ++i)
                            remain_delete.push_back(delete_ids.at(i));

                        client.message_delete_bulk(remain_delete, event.command.channel_id);
                        is_purged = true;
                    }
                }
            }
        });

    if (!is_valid_to_purge)
        send_error("Cannot delete too old messages, please try again", event);

    if (is_purged)
    {
        const auto description = fmt::format("Deleted {} messages in <#{}>", amount_messages, event.command.channel_id);
        send_success(description, event);
    }
}