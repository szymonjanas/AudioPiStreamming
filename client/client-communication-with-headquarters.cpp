#include "client-communication-with-headquarters.h"

#include <iostream>

Communication_with_headquarters::Communication_with_headquarters(const std::string& zmqAddress) :
    zmqAddress(zmqAddress)
{
    bus_message_log_address("Communication", "setted zmq", zmqAddress);
    context = new zmq::context_t (1);
    socket = new zmq::socket_t (*context, ZMQ_REQ);
    socket->connect(zmqAddress);

}

Communication_with_headquarters::~Communication_with_headquarters()
{
    delete context;
    delete socket;
}

std::string Communication_with_headquarters::request_for_headquarters(const void * order, size_t order_size)
{

        zmq::message_t request (order_size);
        memcpy (request.data (), order, order_size);
        socket->send (request);
        bus_message_short("REQUEST SEND");

        zmq::message_t reply;
        socket->recv (&reply);
        unsigned long size = reply.size();
        std::string data(static_cast<char*>(reply.data()), size);
        bus_communication_log("RECIVED REPLY", data);
        return data;
}
