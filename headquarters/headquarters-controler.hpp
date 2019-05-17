#pragma once

#include "headquarters-communication.h"
#include "headquarters-audio-processing.hpp"

#include <zmq.hpp>
#include <string>
#include "messageBus.hpp"

class Manager
{
    gchar * host;
    gint port;
    std::string& zmqAddress;

    Play_audio_live_from_client* play;
    Communication* communication;
public:
    Manager (gchar * host, gint port, std::string& zmqAddress);
    ~Manager();
    void start();
};
