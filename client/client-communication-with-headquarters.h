#pragma once

#include <zmq.hpp>
#include <string>
#include "messageBus.hpp"
#include <iostream>

class Communication_with_headquarters
{
    zmq::context_t* context;
    zmq::socket_t* socket;
    std::string zmqAddress;
    int TIMEOUT_ms;

    void set_communication();
public:
    Communication_with_headquarters(std::string zmqAddress);
    ~Communication_with_headquarters();

    std::string request_for_headquarters(const void * order, size_t order_size);
};
