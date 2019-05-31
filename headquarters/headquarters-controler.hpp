#pragma once

#include "headquarters-communication-controller.hpp"
#include "headquarters-audio-processing.hpp"
#include "communication-state.hpp"

#include <zmq.hpp>
#include <string>
#include "messageBus.hpp"
#include <memory>

class Manager
{
    bool is_setted;
    bool is_playing;

    gchar * host;
    gint port;
    std::string zmqAddress;

    std::unique_ptr<Play_audio_live_from_client> audio;
    std::unique_ptr<Communication_controler> communication;

    void set_connection();
    bool set();
    bool play();
    bool stop();


public:
    Manager (gchar * host, gint port, std::string zmqAddress);
    ~Manager();
    void manage();

};
