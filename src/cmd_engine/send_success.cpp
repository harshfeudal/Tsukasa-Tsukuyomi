#include <cmd_engine.h>

void send_success(std::string description, const dpp::slashcommand_t& event)
{
    auto create_embed = dpp::embed()
        .set_color(0x38ff9b)
        .set_title("Success!")
        .set_description(description);

    const auto message = dpp::message().add_embed(create_embed);
    event.reply(message);
}