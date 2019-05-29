#pragma once
#include <string>
#include <map>
enum class Request{
    ERROR,
    SERVER_TEST_CONNECTION,
    SERVER_SET_UDP,
    SERVER_STOP_UDP
};

enum class Replay{
    ERROR,
    SERVER_CONNECTED,
    SERVER_NOT_RESPOND,
    SERVER_SETTED_UDP,
    SERVER_STOPED_UDP
};

using Message_to_headquarter = std::pair<const void *, size_t>;

class Communication_state_converter
{
    std::map<Request, std::string> request;
    std::map<Replay, std::string> replay;
public:
    Communication_state_converter();

    Message_to_headquarter convert_to_server_request(Request request) const;
    Message_to_headquarter convert_to_server_replay(Replay replay) const;
    Request convert_server_requert_to_enum(std::string request) const;
    Replay convert_server_replay_to_enum(std::string replay) const;
};
