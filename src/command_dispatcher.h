#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include <dpp/dispatcher.h>

class CCommandDispatcher final {
    typedef std::function<void(const dpp::slashcommand_t)> CommandCallback;

    static std::map<std::string, CommandCallback> ms_CallbackMap;
    static CommandCallback ms_NotFoundCallback;

    static void PingCommand(const dpp::slashcommand_t& event);

    static void NotFoundCallback(const dpp::slashcommand_t& event);

public:
    static void SetNotFoundCallback(CommandCallback Callback);
    static void DispatchCommand(const dpp::slashcommand_t& event);
};

#endif // COMMAND_DISPATCHER_H
