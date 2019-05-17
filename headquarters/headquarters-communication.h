#pragma once

#include <string>
#include <zmq.hpp>
#include <iostream>
#include "messageBus.hpp"

class Communication
{
    std::string& zmqAddress;
public:
    Communication(std::string& zmqAddress);
    ~Communication();
    std::string waiting_for_request_from_client();
    void send_confirm_or_refuse(const void *message, size_t message_size);
};
