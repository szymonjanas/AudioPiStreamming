#pragma once

#include <zmq.hpp>
#include <string>

class Communication_with_headquarters
{
    zmq::context_t* context;
    zmq::socket_t* socket;
public:
    Communication_with_headquarters(const char * host);

    std::string request_for_headquarters(const void * order, size_t order_size);
};
