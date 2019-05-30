#pragma once
#include <string>
#include <map>
#include <zmq.hpp>
#include "messageBus.hpp"

enum class Request{
    SERVER_TEST_CONNECTION,
    SERVER_PLAY_UDP,
    SERVER_SET_UDP,
    SERVER_STOP_UDP,
    SERVER_WRONG_REQUEST
};

enum class Replay{
    SERVER_NOT_RESPOND,
    SERVER_CONNECTED,
    SERVER_PLAYED_UDP,
    SERVER_SETTED_UDP,
    SERVER_STOPED_UDP,
    SERVER_WRONG_REQUEST,
    LOCAL_SOMETHING_WRONG
};

using serv_message_t = std::pair<const void *, size_t>;

class Communication_state_converter
{
    std::map<Request, serv_message_t> request_map;
    std::map<std::string, Replay> replay_map;
public:
    Communication_state_converter();

    serv_message_t convert_request_to_server_msg(Request request) const;
    Replay convert_server_msg_to_replay(std::string replay) const;
};
