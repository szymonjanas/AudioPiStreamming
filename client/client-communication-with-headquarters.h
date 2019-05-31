#pragma once

#include <zmq.hpp>
#include <string>
#include "messageBus.hpp"
#include <iostream>
#include <memory>

class Communication_with_headquarters
{
    std::unique_ptr<zmq::context_t> context;
    std::unique_ptr<zmq::socket_t> socket;
    std::string zmqAddress;
    int TIMEOUT_ms;

    void set_communication();

public:

    Communication_with_headquarters(std::string zmqAddress);

    std::string request_for_headquarters(std::string request);

};
