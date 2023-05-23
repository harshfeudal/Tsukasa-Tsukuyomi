#include <cmd_engine.h>

std::tuple<bool, std::string> error_check(dpp::cluster& client, const dpp::slashcommand_t& event, dpp::snowflake user_id, dpp::permission permission, std::string cmd_name)
{
    std::string description;
    bool is_error = false;

    const auto guild_id = event.command.guild_id;
    const auto get_guild_user = dpp::find_guild_member(guild_id, user_id);

    const auto guild = dpp::find_guild(guild_id);
    dpp::user user = client.user_get_sync(user_id);

    const auto is_admin_user = guild->base_permissions(get_guild_user).has(dpp::p_administrator);
    const auto is_admin_issuer = guild->base_permissions(event.command.member).has(dpp::p_administrator);
    const auto is_admin_client = event.command.app_permissions.has(dpp::p_administrator);

    if (!guild->base_permissions(event.command.member).has(permission))
    {
        description = fmt::format("You have no permission to {} members", cmd_name);
        is_error = true;
    }
    else
    {
        if (!event.command.app_permissions.has(permission))
        {
            description = fmt::format("I have no permission to {} members", cmd_name);
            is_error = true;
        }

        if (user_id == guild->owner_id)
        {
            description = fmt::format("Owner is immune!", cmd_name);
            is_error = true;
        }

        if (user_id == event.command.usr.id)
        {
            description = fmt::format("Action failed!", cmd_name);
            is_error = true;
        }

        if (user_id == client.me.id)
        {
            description = fmt::format("I am immune with myself", cmd_name);
            is_error = true;
        }

        if (is_admin_user)
        {
            if (!is_admin_client)
            {
                description = fmt::format("I have no administration permision to {} that user", cmd_name);
                is_error = true;
            }

            if (!is_admin_issuer)
            {
                description = fmt::format("You cannot {} a user that has administration permission", cmd_name);
                is_error = true;
            }
        }

        const auto user_roles = get_guild_user.roles;
        const auto issuer_roles = dpp::find_guild_member(guild_id, event.command.usr.id).roles;

        if (!user_roles.empty() && !issuer_roles.empty() && !is_error)
        {
            const auto user_pos = dpp::find_role(user_roles.at(0))->position;
            const auto issuer_pos = dpp::find_role(issuer_roles.at(0))->position;

            if (issuer_pos < user_pos)
            {
                description = fmt::format("Cannot {} `{}` because their role is higher", cmd_name, user.username);
                is_error = true;
            }
        }
    }

    return { is_error, description };
}