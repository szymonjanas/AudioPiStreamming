#include "client-communication-with-headquarters.h"

#include <iostream>

Communication_with_headquarters::Communication_with_headquarters(const char * host)
{
//    zmq::context_t context (1);
//    zmq::socket_t socket (context, ZMQ_REQ);
    this->context = new zmq::context_t(1);
    this->socket = new zmq::socket_t(*context, ZMQ_REQ);
    socket->connect (host);
}

std::string Communication_with_headquarters::request_for_headquarters(const void * order, size_t order_size)
{
        zmq::message_t request (order_size);
        memcpy (request.data (), order, order_size);
        socket->send (request);

        zmq::message_t reply;
        socket->recv (&reply);
        unsigned long size = reply.size();
        std::string data(static_cast<char*>(reply.data()), size);

        return data;
}
