// https://github.com/brainboxdotcc/DPP/pull/1468
#include <dpp/dpp.h>
#ifdef _WIN32
#undef poll
#undef pollfd
#endif
#include <crow.h>

#include <utility/utils.h>
#include <config/config_env.h>
#include <log/logger_adapter.h>

#include "command_dispatcher.h"

int main() {
    g_Logger.Log(LogLevel::Trace, "Logger test");

    std::unique_ptr<IConfig> Config = std::make_unique<EnvConfig>();

    std::string token = Config->GetString("DC_TOKEN", "");
    dpp::snowflake channel = Config->GetString("DC_CHANNEL", "");
    int port = Config->GetInt("DC_WEB_PORT", 18080);

    if(token.empty() || channel.empty())
    {
        g_Logger.Log(LogLevel::Critical, "One of essential config vars are missing");
        return 1;
    }

    dpp::cluster bot(token);

    bot.on_log(DppLogAdapter::Logger());
    bot.on_slashcommand(CCommandDispatcher::DispatchCommand);

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct reg>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong", bot.me.id));
        }
    });

    std::thread discord_thread([&bot]() {
        bot.start(dpp::st_wait);
    });

    crow::SimpleApp app;
    CrowLogAdapter CrowLogger;
    crow::logger::setHandler(&CrowLogger);

    CROW_ROUTE(app, "/send/<string>")
            ([&bot, channel](const crow::request& req, crow::response& res, const std::string& msg) {
                bot.message_create(dpp::message(channel, msg));
                res.end("Message sent to Discord!");
            });

    g_Logger.Log(LogLevel::Info, "HTTP server running on http://localhost:{}", port);
    app.port(18080).multithreaded().run();

    discord_thread.join();
    return 0;
}
