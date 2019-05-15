#pragma once

#include <zmq.hpp>
#include <string>

class Communication
{


public:
    Communication();
    bool set_music_reciver_on(const char * host);

};
