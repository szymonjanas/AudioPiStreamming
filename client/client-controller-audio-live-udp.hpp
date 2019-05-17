#pragma once
#include "client-communication-with-headquarters.h"
#include "client-audio-udp.hpp"
#include "client-controller-audio.hpp"

class Music_live_udp_controller : virtual public Music_controller
{
    Audio_server* server;
    Communication_with_headquarters* message;
public:
    Music_live_udp_controller(gchar * host, gint port, const char * zmqAddress);
    ~Music_live_udp_controller();
    void play_music() override;
    void pause_music() override;
    void stop_music() override;
    void set_file_location(const char *) override;
};
