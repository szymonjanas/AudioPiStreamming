#include "headquarters-communication.h"

Communication::Communication(std::string& zmqAddress) :
    zmqAddress(zmqAddress)
{
    bus_message_log_address("Communication", "setted", zmqAddress);
    context = new zmq::context_t (1);
    socket = new zmq::socket_t (*context, ZMQ_REP);
    socket->bind(zmqAddress);
}

Communication::~Communication()
{
    delete socket;
    delete context;
}

std::string Communication::waiting_for_request_from_client()
{
    bus_message_short("WAITING FOR REQUEST");

    zmq::message_t request;
    socket->recv (&request);
    unsigned long size = request.size();
    std::string data(static_cast<char*>(request.data()), size);
    bus_communication_log("REQUEST RECIVED", data);

    return data;
}

void Communication::send_confirm_or_refuse(const void *message, size_t message_size)
{
    zmq::message_t request (message_size);
    memcpy (request.data (), message, message_size);
    socket->send (request);
}
