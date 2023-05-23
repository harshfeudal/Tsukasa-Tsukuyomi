#include <spdlog/spdlog.h>

#include <cmd_list.h>
#include <builder/layout.h>

void kick(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	const auto user_id = std::get<dpp::snowflake>(event.get_parameter("member"));
	const auto guild_id = event.command.guild_id;

	const auto guild = dpp::find_guild(guild_id);
	const auto guild_member = guild->members.find(user_id);

	bool is_higher = false;
	bool is_failed = false;

	std::string description;
	dpp::user user = client.user_get_sync(user_id);

	if (guild_member == guild->members.end())
	{
        description = fmt::format("User `{}` is not staying in this guild!", user.format_username());
		send_error(description, event);

		is_failed = true;
	}

	if (!is_failed)
	{
		const auto is_error = error_check(client, event, user_id, dpp::p_kick_members, "kick");
		const auto client_roles = dpp::find_guild_member(guild_id, client.me.id).roles;
		const auto user_roles = dpp::find_guild_member(guild_id, user_id).roles;
	
		uint8_t client_pos;
		uint8_t	user_pos;
	
		if (!client_roles.empty() && !user_roles.empty() && (guild_member != guild->members.end()))
		{
			const auto client_pos = dpp::find_role(client_roles.at(0))->position;
			const auto user_pos = dpp::find_role(user_roles.at(0))->position;
	
			if (client_pos < user_pos) {
				description = fmt::format("Cannot kick `{}` because my role is lower", user.username);
				is_higher = true;
			}
		}
	
		if (!std::get<bool>(is_error) && !is_higher)
		{
			const auto reason_param = event.get_parameter("reason");
			const auto reason = std::holds_alternative<std::string>(reason_param)
				? std::get<std::string>(reason_param)
				: "No reason provided";
	
			client.set_audit_reason(reason);
			client.guild_member_kick(guild_id, user_id);
	
			description = fmt::format("User `{}` has been kicked!", user.format_username());
			send_success(description, event);
		}
		else
		{
			if (is_higher)
				send_error(description, event);
			else
				send_error(std::get<std::string>(is_error), event);
		}
	}
}