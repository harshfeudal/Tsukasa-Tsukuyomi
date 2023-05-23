#include <spdlog/spdlog.h>

#include <cmd_list.h>
#include <builder/layout.h>

void nickname(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto user_id = std::get<dpp::snowflake>(event.get_parameter("user"));
    const auto nickname = std::holds_alternative<std::string>(event.get_parameter("setnick"))
        ? std::get<std::string>(event.get_parameter("setnick"))
        : "";
    
    const auto guild = dpp::find_guild(event.command.guild_id);
    const auto get_user = client.user_get_sync(user_id);

    dpp::user user = client.user_get_sync(user_id);
    auto target_user = dpp::find_guild_member(event.command.guild_id, user_id);

    const auto is_admin_user = guild->base_permissions(target_user).has(dpp::p_administrator);
    const auto guild_member = guild->members.find(user_id);

    auto description = fmt::format("Nickname changed from `{}` is: `{}`", get_user.username, nickname);
    bool is_error = false;

    if (guild_member == guild->members.end())
    {
        description = fmt::format("User `{}` is not staying in this guild!", user.format_username());
        send_error(description, event);

        is_error = true;
    }

    if (user_id == guild->owner_id)
    {
        description = fmt::format("Failed to change nickname from `{}`", get_user.username);
        send_error(description, event);

        is_error = true;
    }

    if (!is_error && !is_admin_user)
    {
        if (nickname == "")
            description = fmt::format("Nickname has reset from {}", get_user.username);

        if (user_id == client.me.id)
        {
            client.guild_set_nickname(event.command.guild_id, nickname);
            send_success(description, event);
        }
        else
        {
            target_user.set_nickname(nickname);
            client.guild_edit_member(target_user);
    
            send_success(description, event);
        }
    }
}