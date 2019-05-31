#pragma once

#include "headquarters-communication-controller.hpp"
#include "headquarters-audio-processing.hpp"
#include "communication-state.hpp"

#include <zmq.hpp>
#include <string>
#include "messageBus.hpp"

class Manager
{
    bool is_setted;
    bool is_playing;

    gchar * host;
    gint port;
    std::string zmqAddress;

    Play_audio_live_from_client* audio;
    Communication_controler* communication;

    void set_connection();
    bool set();
    bool play();
    bool stop();


public:
    Manager (gchar * host, gint port, std::string zmqAddress);
    ~Manager();
    void manage();

};
