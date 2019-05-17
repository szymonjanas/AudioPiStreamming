#include "client-communication-with-headquarters.h"

#include <iostream>

Communication_with_headquarters::Communication_with_headquarters(std::string& zmqAddress) :
    zmqAddress(zmqAddress)
{
    bus_message_log_address("Communication", "setted zmq", zmqAddress);
}

std::string Communication_with_headquarters::request_for_headquarters(const void * order, size_t order_size)
{
        zmq::context_t context (1);
        zmq::socket_t socket (context, ZMQ_REQ);
        socket.connect(zmqAddress);

        zmq::message_t request (order_size);
        memcpy (request.data (), order, order_size);
        socket.send (request);

        while (true) {
            zmq::message_t reply;
            socket.recv (&reply);
            unsigned long size = reply.size();
            std::string data(static_cast<char*>(reply.data()), size);
            bus_communication_log("RECIVED REPLY", data);

            if (data.size() > 0)
                return data;
       }
}
