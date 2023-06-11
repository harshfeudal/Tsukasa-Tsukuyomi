#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <cmd_builder/cmd_layout.h>

void ban(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	const auto user_id = std::get<dpp::snowflake>(event.get_parameter("member"));
	const auto guild_id = event.command.guild_id;

	const auto guild = dpp::find_guild(guild_id);
	const auto tgt_user = guild->members.find(user_id);

	const auto is_error = error_check(client, event, user_id, dpp::p_ban_members, "ban");

	if (!std::get<bool>(is_error))
	{
		const auto reason_param = event.get_parameter("reason");
		const auto reason = std::holds_alternative<std::string>(reason_param)
			? std::get<std::string>(reason_param)
			: "No reason provided";

		dpp::user user = client.user_get_sync(user_id);

		bool is_already = false;
		std::string description;

		try
		{
			client.guild_get_ban_sync(guild_id, user_id);
			description = fmt::format("User `{}` has been banned before", user.format_username());

			send_error(description, event);
			is_already = true;
		}
		catch (...) {}

		if (!is_already)
		{
			client.set_audit_reason(reason);
			client.guild_ban_add(guild_id, user_id);

			description = fmt::format("User `{}` has been banned!", user.format_username());

			if (tgt_user == guild->members.end())
				description = fmt::format("Cannot find `{}` in this server, but has been banned anyway.", user.format_username());

			send_success(description, event);
		}
	}
	else
		send_error(std::get<std::string>(is_error), event);
}