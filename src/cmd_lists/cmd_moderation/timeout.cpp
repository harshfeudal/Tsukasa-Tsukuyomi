#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <cmd_builder/cmd_layout.h>

void timeout(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto user_id = std::get<dpp::snowflake>(event.get_parameter("member"));
    const auto duration_str = std::get<std::string>(event.get_parameter("duration"));
    const auto guild_id = event.command.guild_id;

    const auto reason_param = event.get_parameter("reason");
    const auto reason = std::holds_alternative<std::string>(reason_param)
        ? std::get<std::string>(reason_param)
        : "No reason provided";

    const auto time_format_func = time_format(duration_str);
    const auto duration = time(0) + std::get<uint64_t>(time_format_func);
    const auto duration_timestamp = dpp::utility::timestamp(duration, dpp::utility::tf_short_datetime);

    std::string description;
    dpp::user user = client.user_get_sync(user_id);

    const auto is_error = error_check(client, event, user_id, dpp::p_moderate_members, "timeout");

    const auto get_user = dpp::find_guild_member(guild_id, user_id);
    const auto guild = dpp::find_guild(guild_id);
    const auto is_admin_user = guild->base_permissions(get_user).has(dpp::p_administrator);

    if (!std::get<bool>(is_error) && std::get<bool>(time_format_func))
    {
        const auto get_user = dpp::find_guild_member(guild_id, user_id);

        if (get_user.is_communication_disabled())
            client.guild_member_timeout(guild_id, user_id, NULL);

        client.set_audit_reason(reason);
        client.guild_member_timeout(guild_id, user_id, duration);

        description = fmt::format("User `{}` has been timed out until: {}!", user.format_username(), duration_timestamp);
        send_success(description, event);
    }
    else
    {
        if (!std::get<bool>(time_format_func))
            send_error(std::get<std::string>(time_format_func), event);
        else
            send_error(std::get<std::string>(is_error), event);
    }
}