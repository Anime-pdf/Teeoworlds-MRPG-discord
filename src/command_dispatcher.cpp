#include "command_dispatcher.h"

#include <functional>
#include <utility>

#include <dpp/cluster.h>

CCommandDispatcher::CommandCallback CCommandDispatcher::ms_NotFoundCallback = CCommandDispatcher::NotFoundCallback;
std::map<std::string, CCommandDispatcher::CommandCallback> CCommandDispatcher::ms_CallbackMap = {
        {"ping", CCommandDispatcher::PingCommand},
};

void CCommandDispatcher::SetNotFoundCallback(CCommandDispatcher::CommandCallback Callback) {
    ms_NotFoundCallback = std::move(Callback);
}

void CCommandDispatcher::DispatchCommand(const dpp::slashcommand_t &event) {
    if (auto it = ms_CallbackMap.find(event.command.get_command_name()); it != ms_CallbackMap.end()) {
        it->second(event);
        return;
    }

    if (ms_NotFoundCallback) {
        ms_NotFoundCallback(event);
    }
}

void CCommandDispatcher::PingCommand(const dpp::slashcommand_t &event) {
    event.reply(std::format("Pong! Loop latency: {:.2f}s", event.owner->rest_ping));
}

void CCommandDispatcher::NotFoundCallback(const dpp::slashcommand_t &event) {
    event.reply("Command not found! Command list will be updated soon, hopefully");
}
