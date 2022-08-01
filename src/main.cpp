#include <dpp/dpp.h>
#include <bwbot/bwbot.h>
#include <sstream>

using namespace std;
using json = nlohmann::json;

json config;

string Get(string botName, string value) {
    string homeDir = getenv("HOME");
    string slash = "/";

#ifdef _WIN32
    homeDir = getenv("HOMEPATH");
    slash = "\\";
#endif

    ifstream configfile(homeDir + slash + ".botway" + slash + "botway.json");

    configfile >> config;

    if (value.find("token") != string::npos) {
        return config["botway"]["bots"][botName]["bot_token"];
    }

    return config["botway"]["bots"][botName][value];
}

int main(int argc, char const *argv[]) {
    dpp::cluster bot(Get("bwbot", "token"));

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
