#pragma once

#include "headquarters-communication.h"
#include "headquarters-audio-processing.hpp"

#include <zmq.hpp>
#include <string>

class Manager
{
    gchar * host;
    gint port;
    const char * zmqAddress;

    Play_audio_live_from_client* play;
    Communication* communication;
public:
    Manager (gchar * host, gint port, const char * zmqAddress);
    ~Manager();
    void start();
};
