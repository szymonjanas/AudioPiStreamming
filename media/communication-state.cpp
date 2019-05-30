#include "communication-state.hpp"

Communication_state_converter::Communication_state_converter()
{
    request_map[Request::SERVER_TEST_CONNECTION] =  serv_message_t("SERV-TESTC-CONN", 15);
    request_map[Request::SERVER_PLAY_UDP]        =  serv_message_t("SERV-AUDIO-PLAY", 15);
    request_map[Request::SERVER_SET_UDP]         =  serv_message_t("SERV-AUDIO-SETT", 15);
    request_map[Request::SERVER_STOP_UDP]        =  serv_message_t("SERV-AUDIO-STOP", 15);
    request_map[Request::SERVER_WRONG_REQUEST]   =  serv_message_t("SERV-WRONG-REQU", 15);

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
    return request_map.at(request);
}

Replay Communication_state_converter::convert_server_msg_to_replay(std::string replay) const
{
    return replay_map.at(replay);
}
