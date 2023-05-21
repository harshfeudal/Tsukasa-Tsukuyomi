#include <cmd_engine.h>

void send_confirm(std::string confirmation, std::string description, dpp::cluster& client, const dpp::slashcommand_t& event)
{
    auto create_embed = dpp::embed()
        .set_color(0xa1fe9a)
        .set_title(confirmation)
        .set_description(description);

    client.message_create(dpp::message(event.command.channel_id, create_embed));
}