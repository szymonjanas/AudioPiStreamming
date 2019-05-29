#include "client-communication-controller-with-headquarters.hpp"

Communication_Controller::Communication_Controller(const std::string& zmqAddress) :
    Communication_with_headquarters (zmqAddress)
{

}

bool Communication_Controller::check_connection()
{
    Message_to_headquarter msg = converter.convert_to_server_request(
                                                Request::SERVER_TEST_CONNECTION );
    Replay replay = converter.convert_server_replay_to_enum
                                (request_for_headquarters
                                    (msg.first, msg.second));
    if (replay == Replay::SERVER_CONNECTED)
        return true;
    return false;
}

Replay Communication_Controller::send_request(Request request)
{
    if (check_connection())
    {
        Message_to_headquarter msg = converter.convert_to_server_request(request);
        Replay replay = converter.convert_server_replay_to_enum(
                    request_for_headquarters(msg.first, msg.second));
        return replay;
    }
    else
        return Replay::SERVER_NOT_RESPOND;
}
