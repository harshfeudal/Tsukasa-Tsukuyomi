#pragma once

#include <map>

#include <dpp/dpp.h>

#include <cmd_lists.h>
#include <builder/command.h>
#include <builder/button.h>
#include <cmd_engine.h>

// Create a command list
inline std::map<std::string, Command> commands
{
	// Common commands
	{
		"ocr",
		{
			"Read imagine-to-text attachment", ocr,
			{
				dpp::command_option(dpp::co_attachment, "attachment", "Add attachment", true)
			}
		}
	},
	{ 
		"ping", 
		{ 
			"Check bot latency", ping 
		} 
	},
	{ 
		"profile", 
		{ 
			"Get user infomation", profile, 
			{ 
				dpp::command_option(dpp::co_user, "user", "Target a user", false)
			} 
		} 
	},

	// Moderation commands
	{
		"ban",
		{
			"Ban a member", ban,
			{
				dpp::command_option(dpp::co_user, "member", "Member to ban", true),
				dpp::command_option(dpp::co_string, "reason", "The reason to ban, if any", false)
			}
		}
	},
	{
		"kick",
		{
			"Kick a member", kick,
			{
				dpp::command_option(dpp::co_user, "member", "Member to kick", true),
				dpp::command_option(dpp::co_string, "reason", "The reason to kick, if any", false)
			}
		}
	},
    {
        "nickname",
        {
            "Change member nickname", nickname,
            {
                dpp::command_option(dpp::co_user, "user", "Target a user", true),
                dpp::command_option(dpp::co_string, "setnick", "New nickname, to be changed or removed", false)
            }
        }
    },
    {
        "purge",
        {
            "Delete message(s)", purge,
            {
                dpp::command_option(dpp::co_integer, "amount", "Amount of message(s) to delete", true).set_min_value(static_cast<int64_t>(1)).set_max_value(static_cast<int64_t>(1000)),
                dpp::command_option(dpp::co_string, "reason", "The reason to purge, if any", false)
            }
        }
    },
	{
		"timeout",
		{
			"Timeout a member", timeout,
			{
				dpp::command_option(dpp::co_user, "member", "Member to timeout", true),
				dpp::command_option(dpp::co_string, "duration", "How long they should be timed out for", true),
				dpp::command_option(dpp::co_string, "reason", "The reason to timeout, if any", false)
			}
		}
	},
	{
		"unban",
		{
			"Unban a member", unban,
			{
				dpp::command_option(dpp::co_user, "member", "Member to unban", true),
				dpp::command_option(dpp::co_string, "reason", "The reason to unban, if any", false)
			}
		}
	},
    {
        "untimeout",
        {
            "Remove timeout from a user", untimeout,
            {
                dpp::command_option(dpp::co_user, "member", "Member to remove timeout", true),
                dpp::command_option(dpp::co_string, "reason", "The reason to remove timeout, if any", false)
            }
        }
    },
};