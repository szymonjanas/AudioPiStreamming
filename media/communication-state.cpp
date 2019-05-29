#include "communication-state.hpp"

Communication_state_converter::Communication_state_converter()
{
    request[Request::SERVER_TEST_CONNECTION] = "SERVER_TEST_CONNECTION";
    request[Request::SERVER_SET_UDP] = "SERVER_SET_UDP";
    request[Request::SERVER_STOP_UDP] = "SERVER_STOP_UDP";

    replay[Replay::SERVER_CONNECTED] = "SERVER_CONNECTED";
    replay[Replay::SERVER_NOT_RESPOND] = "SERVER_NOT_RESPOND";
    replay[Replay::SERVER_SETTED_UDP] = "SERVER_SETTED_UDP";
    replay[Replay::SERVER_STOPED_UDP] = "SERVER_STOPED_UDP";
}

Message_to_headquarter Communication_state_converter::convert_to_server_replay(Replay replay) const
{
    std::string str_replay = this->replay.at(replay);
    Message_to_headquarter message;
    message.first = static_cast<const void *>(str_replay.c_str());
    message.second = this->replay.at(replay).size();
    return message;
}

Message_to_headquarter Communication_state_converter::convert_to_server_request(Request request) const
{
    std::string str_request = this->request.at(request);
    Message_to_headquarter message;
    message.first = static_cast<const void *>(str_request.c_str());
    message.second = this->request.at(request).size();
    return message;
}

Request Communication_state_converter::convert_server_requert_to_enum(std::string request) const
{
    for (auto i : this->request)
        if (i.second == request) return i.first;
    return Request::ERROR;
}

Replay Communication_state_converter::convert_server_replay_to_enum(std::string replay) const
{
    for (auto i : this->replay)
        if (i.second == replay) return i.first;
    return Replay::ERROR;
}
