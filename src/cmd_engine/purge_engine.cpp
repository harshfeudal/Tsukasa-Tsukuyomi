#include <cmd_engine.h>

int purge_engine(const dpp::message_map message_map, dpp::snowflake channel_id, dpp::cluster& client, int purge_count)
{
    std::vector<dpp::snowflake> delete_ids;

    for (const auto& message : message_map)
    {
        if (message.second.sent < time(0) + 1209600 || message.second.pinned || message.second.author.username.empty())
            continue;
            
        delete_ids.emplace_back(message.first);
        purge_count += 1;
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

    return purge_count;
}