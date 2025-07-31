#include "command_dispatcher.h"

// https://github.com/brainboxdotcc/DPP/pull/1468
#include <dpp/dpp.h>
#ifdef _WIN32
#undef poll
#undef pollfd
#endif

#include <crow.h>

int main() {
    dpp::cluster bot(std::getenv("TOKEN"));

    bot.on_log(dpp::utility::cout_logger());
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

    CROW_ROUTE(app, "/send/<string>")
            ([&bot](const crow::request& req, crow::response& res, const std::string& msg) {
                bot.message_create(dpp::message(dpp::snowflake(std::getenv("CHANNEL")), msg));
                res.end("Message sent to Discord!");
            });

    std::cout << "HTTP server running on http://localhost:18080\n";
    app.port(18080).multithreaded().run();

    discord_thread.join();
    return 0;
}
