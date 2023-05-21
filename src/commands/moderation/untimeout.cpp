#include <spdlog/spdlog.h>

#include <cmd_list.h>
#include <builder/layout.h>

void untimeout(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto user_id = std::get<dpp::snowflake>(event.get_parameter("member"));
    const auto guild_id = event.command.guild_id;

    std::string description;
    dpp::user user = client.user_get_sync(user_id);

    const auto is_error = error_check(client, event, user_id, dpp::p_moderate_members, "un-timeout");

    const auto get_user = dpp::find_guild_member(guild_id, user_id);
    const auto guild = dpp::find_guild(guild_id);
    const auto is_admin_user = guild->base_permissions(get_user).has(dpp::p_administrator);

    if (!std::get<bool>(is_error))
    {
        const auto reason_param = event.get_parameter("reason");
        const auto reason = std::holds_alternative<std::string>(reason_param)
            ? std::get<std::string>(reason_param)
            : "No reason provided";

        const auto get_user = dpp::find_guild_member(guild_id, user_id);

        if (get_user.is_communication_disabled())
        {
            client.guild_member_timeout(guild_id, user_id, NULL);
            description = fmt::format("Timeout removed from user `{}`", user.format_username());
        }  
        else
            description = fmt::format("User `{}` haven't been timed out before", user.format_username());

        send_success(description, event);
    }
    else
        send_error(std::get<std::string>(is_error), event);
}