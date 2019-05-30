#include "client-communication-with-headquarters.h"

#include <iostream>

Communication_with_headquarters::Communication_with_headquarters(std::string zmqAddress) : zmqAddress(zmqAddress)
{
    context = new zmq::context_t (1);
    set_communication();
    bus_message_log_address("Communication", "setted zmq", zmqAddress);
    TIMEOUT_ms = 1000;
}

void Communication_with_headquarters::set_communication()
{
    socket = new zmq::socket_t (*context, ZMQ_REQ);
    socket->connect(zmqAddress.c_str());
}

Communication_with_headquarters::~Communication_with_headquarters()
{
    delete socket;
    delete context;
}

std::string Communication_with_headquarters::request_for_headquarters(const void * order, size_t order_size)
{
    zmq::message_t request (order_size);
    memcpy (request.data (), order, order_size);
    socket->send (request);
    bus_message_short("REQUEST SEND");

    zmq::pollitem_t element[] = {{static_cast<void *>(*socket), 0, ZMQ_POLLIN, 0}};
    zmq::poll(&element[0], 1, TIMEOUT_ms);

    if (element[0].revents != 0 and ZMQ_POLLIN) {
        zmq::message_t reply;
        socket->recv (&reply);
        unsigned long size = reply.size();
        std::string data(static_cast<char*>(reply.data()), size);
        bus_communication_log("RECIVED REPLY", data);
        return data;
    }
    else if (element[0].revents == 0 and ZMQ_POLLIN)
    {
        delete socket;
        set_communication();
        bus_message_error_report("client-communication",
                                 "Communication_with_headquarters",
                                 "request_for_headquarters",
                                 "SERVER NOT RESPOND");
        return "SERV-DONOT-RESPO";
    }
}
