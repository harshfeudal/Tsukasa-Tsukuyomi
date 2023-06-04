#include <spdlog/spdlog.h>

#include <cmd_lists.h>
#include <builder/layout.h>

void purge(dpp::cluster& client, const dpp::slashcommand_t& event)
{
    const auto amount_messages = std::get<int64_t>(event.get_parameter("amount"));

    
}