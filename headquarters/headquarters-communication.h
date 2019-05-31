#pragma once

#include <string>
#include <zmq.hpp>
#include <iostream>
#include "messageBus.hpp"
#include <memory>

class Communication
{
    std::string zmqAddress;
    std::unique_ptr<zmq::context_t> context;
    std::unique_ptr<zmq::socket_t> socket;

    void set_communication();
public:
    Communication(std::string zmqAddress);
    ~Communication();
    std::string waiting_for_request_from_client();
    void send_confirm_or_refuse(const void *message, size_t message_size);
};
