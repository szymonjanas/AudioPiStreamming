#include "client-communication-controller-with-headquarters.hpp"

Communication_Controller::Communication_Controller(const std::string& zmqAddress) :
    Communication_with_headquarters (zmqAddress)
{

}

Communication_Controller::~Communication_Controller()
{

}

bool Communication_Controller::check_connection()
{
    for (unsigned short i = 0; i < 3; ++i)
    {
        serv_message_t msg = converter.convert_request_to_server_msg(
                    Request::SERVER_TEST_CONNECTION );
        Replay replay = converter.convert_server_msg_to_replay
                (request_for_headquarters
                 (msg.first, msg.second));
        if (replay == Replay::SERVER_CONNECTED)
            return true;
    }
    return false;
}

Replay Communication_Controller::send_request(Request request)
{
    if (check_connection())
    {
        serv_message_t msg = converter.convert_request_to_server_msg(request);
        Replay replay = converter.convert_server_msg_to_replay(
                    request_for_headquarters(msg.first, msg.second));
        return replay;
    }
    else
        return Replay::SERVER_NOT_RESPOND;
}
