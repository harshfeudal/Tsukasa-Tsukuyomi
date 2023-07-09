#pragma once
#pragma warning (disable: 4251)
#pragma warning (disable: 4244)

#include <dpp/dpp.h>

#include <cmd_engine.h>

// Common commands
void ping(dpp::cluster& client, const dpp::slashcommand_t& event);
void profile(dpp::cluster& client, const dpp::slashcommand_t& event);

// Moderation commands
void ban(dpp::cluster& client, const dpp::slashcommand_t& event);
void kick(dpp::cluster& client, const dpp::slashcommand_t& event);
void nickname(dpp::cluster& client, const dpp::slashcommand_t& event);
void purge(dpp::cluster& client, const dpp::slashcommand_t& event);
void timeout(dpp::cluster& client, const dpp::slashcommand_t& event);
void unban(dpp::cluster& client, const dpp::slashcommand_t& event);
void untimeout(dpp::cluster& client, const dpp::slashcommand_t& event);