#include "headquarters-communication-controller.hpp"

Communication_controler::Communication_controler(std::string zmqAddress) :
     Communication(zmqAddress)
{

}

Request Communication_controler::get_request_from_client()
{
    std::string request_msg = waiting_for_request_from_client();
    Request request = converter.convert_client_request_msg(request_msg);
    return request;
}

void Communication_controler::send_replay(Replay replay)
{
    std::string msg = converter.convert_replay_to_client(replay);
    send_confirm_or_refuse(msg);
}
