#include "communication-state.hpp"

Communication_state_converter::Communication_state_converter()
{
    message_size = 15;
    request_map[Request::SERVER_TEST_CONNECTION] =  "SERV-TESTC-CONN";
    request_map[Request::SERVER_PLAY_UDP]        =  "SERV-AUDIO-PLAY";
    request_map[Request::SERVER_SET_UDP]         =  "SERV-AUDIO-SETT";
    request_map[Request::SERVER_STOP_UDP]        =  "SERV-AUDIO-STOP";
    request_map[Request::SERVER_WRONG_REQUEST]   =  "SERV-WRONG-REQU";

    replay_map["SERV-DONOT-RESPO"] = Replay::SERVER_NOT_RESPOND;
    replay_map["SERV-TESTC-CONND"] = Replay::SERVER_CONNECTED;
    replay_map["SERV-AUDIO-PLAYD"] = Replay::SERVER_PLAYED_UDP;
    replay_map["SERV-AUDIO-SETTD"] = Replay::SERVER_SETTED_UDP;
    replay_map["SERV-AUDIO-STOPD"] = Replay::SERVER_STOPED_UDP;
    replay_map["SERV-WRONG-REQUD"] = Replay::SERVER_WRONG_REQUEST;
    replay_map["LOCA-ERROR-UNKNO"] = Replay::LOCAL_SOMETHING_WRONG;
}

serv_message_t Communication_state_converter::convert_request_to_server_msg(Request request) const
{
    serv_message_t serv_msg;
    serv_msg.first = static_cast<const void *>(request_map.at(request).c_str());
    serv_msg.second = message_size;
    return serv_msg;
}

Replay Communication_state_converter::convert_server_msg_to_replay(std::string replay) const
{
    return replay_map.at(replay);
}

Request Communication_state_converter::convert_client_request_msg(std::string request) const
{
    for (auto i : request_map)
    {
        if (i.second == request)
            return i.first;
    }
}

serv_message_t Communication_state_converter::convert_replay_to_client(Replay replay) const
{
    for (auto i : replay_map)
    {
        if (i.second == replay)
        {
            return serv_message_t(static_cast<const void *>(i.first.c_str()), message_size);
        }
    }
}

