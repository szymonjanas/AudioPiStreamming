#pragma once

#include <string>
#include <zmq.hpp>

class Communication
{
    zmq::context_t* context;
    zmq::socket_t* socket;
public:
    Communication(const char * zmqAddress);
    ~Communication();
    std::string waiting_for_request_from_client();
    void send_confirm_or_refuse(const void *message, size_t message_size);
};
