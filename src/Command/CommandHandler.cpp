#include "../../include/CommandHandler.hpp"

CommandHandler::CommandHandler(Server& server): _server(server), _commands() {}

CommandHandler::~CommandHandler() {}