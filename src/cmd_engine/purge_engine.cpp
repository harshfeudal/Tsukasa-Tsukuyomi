#include <cmd_engine.h>

void purge_engine(dpp::cluster& client, const dpp::slashcommand_t& event, dpp::snowflake channel_id, int64_t amount)
{
    client.messages_get(channel_id, 0, 0, 0, amount, [&](const dpp::confirmation_callback_t& callback) {
        if (!callback.is_error())
        {
            std::vector<dpp::snowflake> message_ids;
            const auto message_delete_map = std::get<dpp::message_map>(callback.value);

            for (const auto& message_deletion : message_delete_map)
                message_ids.emplace_back(message_deletion.first);

            client.message_delete_bulk(message_ids, channel_id);
        }
    });
}