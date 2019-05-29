#pragma once
#include <string>
#include <map>
enum class Request{
    TEST_CONNECTION,
    ERROR
};

enum class Replay{
    TEST_PASS,
    TEST_FAIL,
    ERROR
};

using Message_to_headquarter = std::pair<const void *, size_t>;

class Communication_state_converter
{
    std::map<Request, std::string> request;
    std::map<Replay, std::string> replay;
public:
    Communication_state_converter();
    Message_to_headquarter convert_request_to_string(Request request) const;
    Message_to_headquarter convert_replay_to_string(Replay replay) const;
    Request convert_requert_to_enum(std::string request) const;
    Replay convert_replay_to_enum(std::string replay) const;
};
