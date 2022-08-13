#include <dpp/dpp.h>
#include <{{.BotName}}/{{.BotName}}.h>
#include <sstream>
#include "botway/botway.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    dpp::cluster bot(Get("{{.BotName}}", "token"));

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    bot.start(false);

    return 0;
}
