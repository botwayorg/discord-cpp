#pragma once
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
