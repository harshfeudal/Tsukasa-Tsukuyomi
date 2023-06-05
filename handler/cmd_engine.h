#pragma once
#pragma warning(disable: 4834)
#pragma warning(disable: 4251)

#include <spdlog/spdlog.h>
#include <dpp/dpp.h>

void send_error(std::string description, const dpp::slashcommand_t& event);
void send_success(std::string description, const dpp::slashcommand_t& event);
void send_confirm(std::string confirmation, std::string description, dpp::cluster& client, const dpp::slashcommand_t& event);

std::tuple<uint64_t, bool, std::string> time_format(const std::string& input);
std::tuple<bool, std::string> error_check(dpp::cluster& client, const dpp::slashcommand_t& event, dpp::snowflake user_id, dpp::permission permission, std::string cmd_name);