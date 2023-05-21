#include <spdlog/spdlog.h>

#include <cmd_list.h>
#include <builder/layout.h>

void ocr(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	const auto attachment_id = std::get<dpp::snowflake>(event.get_parameter("attachment"));
	const auto find_attachment = event.command.resolved.attachments.find(attachment_id);

	if (find_attachment != event.command.resolved.attachments.end())
	{
		const auto& attachment = find_attachment->second;
		const auto attachment_url = attachment.url;
	}

    // Working with deep learning - data will be soon added
}