#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <builder/layout.h>

void profile(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	const auto user = std::holds_alternative<dpp::snowflake>(event.get_parameter("user")) 
		? std::get<dpp::snowflake>(event.get_parameter("user")) 
		: event.command.usr.id;

	const auto user_info = client.user_get_sync(user);

	const auto button_url = fmt::format("discord://-/users/{}", user);
	const auto create_day = dpp::utility::timestamp(user.get_creation_time(), dpp::utility::tf_relative_time);
	const auto user_url = fmt::format("https://discord.com/users/{}", user);

	auto create_button = dpp::component()
		.set_label("View profile")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_link)
		.set_url(button_url);

	const auto accent_color = user_info.accent_color == 0x000000 ? 0xd8baba : user_info.accent_color;

	auto create_embed = dpp::embed()
		.set_title(user_info.username)
		.set_url(user_url)
		.set_color(accent_color)
		.set_thumbnail(user_info.get_avatar_url(1024, dpp::i_webp))
		.add_field("Username", user_info.username, true)
		.add_field("Created", create_day, true)
		.set_image(user_info.get_banner_url(1024, dpp::i_webp))
		.set_footer(
			dpp::embed_footer()
			.set_text(std::to_string(user))
		)
		.set_timestamp(time(0));

	event.reply(dpp::message().add_embed(create_embed).add_component(dpp::component().add_component(create_button)));
}