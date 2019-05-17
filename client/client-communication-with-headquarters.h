#pragma once

#include <zmq.hpp>
#include <string>
#include "messageBus.hpp"

class Communication_with_headquarters
{
    zmq::context_t* context;
    zmq::socket_t* socket;
    std::string& zmqAddress;
public:
    Communication_with_headquarters(std::string& zmqAddress);
    ~Communication_with_headquarters();

    std::string request_for_headquarters(const void * order, size_t order_size);
};
