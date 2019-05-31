#include "client-communication-with-headquarters.h"

#include <iostream>

Communication_with_headquarters::Communication_with_headquarters(std::string zmqAddress) : zmqAddress(zmqAddress)
{
    context = std::make_unique<zmq::context_t>(1);
    set_communication();
    bus_message_log_address("Communication", "setted zmq", zmqAddress);
    TIMEOUT_ms = 1000;
}

void Communication_with_headquarters::set_communication()
{
    socket = std::make_unique<zmq::socket_t> (*context, ZMQ_REQ);
    socket->connect(zmqAddress.c_str());
}

std::string Communication_with_headquarters::request_for_headquarters(std::string request)
{
    zmq::message_t request_msg (request.size());
    memcpy (request_msg.data (), static_cast<const void *>(request.c_str()), request.size());
    socket->send (request_msg);
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
        socket.reset();
        set_communication();
        bus_message_error_report("client-communication",
                                 "Communication_with_headquarters",
                                 "request_for_headquarters",
                                 "SERVER NOT RESPOND");
        return "SERV-DONOT-RESPO";
    }
    return "LOCA-ERROR-UNKNO";
}
