#include <cmd_engine.h>

void send_error(std::string description, const dpp::slashcommand_t& event)
{
    auto create_embed = dpp::embed()
        .set_color(0x8c7cff)
        .set_title("Error!")
        .set_description(description);

    const auto message = dpp::message().add_embed(create_embed).set_flags(dpp::m_ephemeral);
    event.reply(message);
}