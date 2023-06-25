#pragma warning(push)
#pragma warning(disable: 4251)
#pragma warning(disable: 6385)
#pragma warning(disable: 6285)
#pragma warning(disable: 4700)

#include <dpp/dpp.h>
#include <spdlog/spdlog.h>

#include <dotenv.h>
#include <decoder.h>

#include <cmd_builder/cmd_configure.h>

#pragma warning(pop)

int main()
{
	Dotenv env(".env");

	const auto encode_token = env.get("ENCODE_CLIENT_TOKEN");
	const auto token = Decoder::Decode(encode_token);

	dpp::cluster client(token, dpp::i_all_intents);
	client.on_log(dpp::utility::cout_logger());

	client.on_ready([&client](const dpp::ready_t& event)
		{
			client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Tonikaku Kawaii"));
			create_slash_commands(client);

			fmt::print("[{}]: {} is online!\n", dpp::utility::current_date_time(), client.me.format_username());
			fmt::print("[{}]: Successfully registered slash commands!\n", dpp::utility::current_date_time());
		});

	client.on_button_click([](const dpp::button_click_t& event) { button_handler(event); });

	client.on_slashcommand([&client](const dpp::slashcommand_t& event)
		{
			dpp::command_interaction data = event.command.get_command_interaction();
			auto filter = commands.find(data.name);

			if (filter != commands.end())
				filter->second.function(client, event);
		});

	SetConsoleTitle(TEXT("Tsukasa Tsukuyomi Bot"));

	client.start(dpp::st_wait);
	return 0;
}