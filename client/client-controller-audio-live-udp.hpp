#pragma once
#include "client-communication-with-headquarters.h"
#include "client-audio-udp.hpp"
#include "client-controller-audio.hpp"
#include "messageBus.hpp"

class Music_controller_live_mp3_udp : virtual public Music_controller
{
    Audio_server* server;
    Communication_with_headquarters* message;
    bool is_headquarters_need_set;
    bool is_play;
public:
    Music_controller_live_mp3_udp(const gchar * host, gint port, std::string& zmqAddress);
    ~Music_controller_live_mp3_udp();
    void play_music() override;
    void pause_music() override;
    void stop_music() override;
    void set_file_location(const char *) override;
};
