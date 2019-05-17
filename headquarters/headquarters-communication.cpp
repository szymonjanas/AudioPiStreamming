#include "headquarters-communication.h"

Communication::Communication(const char * zmqAddress)
{
    this->context = new zmq::context_t(1);
    this->socket = new zmq::socket_t(*context, ZMQ_REQ);
    socket->connect (zmqAddress);
}

Communication::~Communication()
{
    delete context;
    delete socket;
}

std::string Communication::waiting_for_request_from_client()
{
    while (true)
    {
        zmq::message_t request;
        socket->recv (&request);
        unsigned long size = request.size();
        std::string data(static_cast<char*>(request.data()), size);
        if (data.size() > 0)
            return data;
    }
}

void Communication::send_confirm_or_refuse(const void *message, size_t message_size)
{
    zmq::message_t request (message_size);
    memcpy (request.data (), message, message_size);
    socket->send (request);
}
