#include "headquarters-communication.h"

Communication::Communication(std::string& zmqAddress) :
    zmqAddress(zmqAddress)
{
}

Communication::~Communication()
{
}

std::string Communication::waiting_for_request_from_client()
{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.connect(zmqAddress);
    while (true)
    {
        zmq::message_t request;
        socket.recv (&request);
        unsigned long size = request.size();
        std::string data(static_cast<char*>(request.data()), size);
        if (data.size() > 0)
            return data;
    }
}

void Communication::send_confirm_or_refuse(const void *message, size_t message_size)
{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.connect(zmqAddress);
    zmq::message_t request (message_size);
    memcpy (request.data (), message, message_size);
    socket.send (request);
}
