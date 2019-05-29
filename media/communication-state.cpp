#include "communication-state.hpp"

Communication_state_converter::Communication_state_converter()
{
    request[Request::TEST_CONNECTION] = "TEST_CONNECTION";

    replay[Replay::TEST_PASS] = "TEST_PASS";
    replay[Replay::TEST_FAIL] = "TEST_FAIL";
}

Message_to_headquarter Communication_state_converter::convert_replay_to_string(Replay replay) const
{
    std::string str_replay = this->replay.at(replay);
    Message_to_headquarter message;
    message.first = static_cast<const void *>(str_replay.c_str());
    message.second = this->replay.at(replay).size();
    return message;
}

Message_to_headquarter Communication_state_converter::convert_request_to_string(Request request) const
{
    std::string str_request = this->request.at(request);
    Message_to_headquarter message;
    message.first = static_cast<const void *>(str_request.c_str());
    message.second = this->request.at(request).size();
    return message;
}

Request Communication_state_converter::convert_requert_to_enum(std::string request) const
{
    for (auto i : this->request)
        if (i.second == request) return i.first;
    return Request::ERROR;
}

Replay Communication_state_converter::convert_replay_to_enum(std::string replay) const
{
    for (auto i : this->replay)
        if (i.second == replay) return i.first;
    return Replay::ERROR;
}
