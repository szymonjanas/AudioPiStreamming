#pragma once
#include "client-communication-with-headquarters.h"
#include "client-audio-udp.hpp"
#include "client-controller-audio.hpp"

class Controller : virtual public Music_controller
{
    Audio_server* server;
    Communication_with_headquarters* message;
    bool is_headquarters_need_set;
public:
    Controller(gchar * host, gint port, const char * zmqAddress);
    ~Controller();
    void play_music() override;
    void pause_music() override;
    void stop_music() override;
    void set_file_location(const char *) override;
};
