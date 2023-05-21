#include <spdlog/spdlog.h>

#include <cmd_list.h>
#include <builder/layout.h>

void unban(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	const auto user_id = std::get<dpp::snowflake>(event.get_parameter("member"));
	const auto guild_id = event.command.guild_id;

	const auto is_error = error_check(client, event, user_id, dpp::p_ban_members, "unban");

	if (!std::get<bool>(is_error))
	{
		const auto reason_param = event.get_parameter("reason");
		const auto reason = std::holds_alternative<std::string>(reason_param)
			? std::get<std::string>(reason_param)
			: "No reason provided";

		dpp::user user = client.user_get_sync(user_id);

		bool is_worked = false;
		std::string description;

		try
		{
			client.guild_get_ban_sync(guild_id, user_id);
			is_worked = true;
		}
		catch (...)
		{
			description = fmt::format("User `{}` hasn't been banned before", user.format_username());
			send_error(description, event);
		}

		if (is_worked)
		{
			client.set_audit_reason(reason);
			client.guild_ban_delete(guild_id, user_id);

			description = fmt::format("Unbanned user `{}`!", user.format_username());
			send_success(description, event);
		}
	}
	else
		send_error(std::get<std::string>(is_error), event);
}