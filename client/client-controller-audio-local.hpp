#pragma once
#include "client-audio-local.hpp"
#include "client-controller-audio.hpp"


class Music_local_mp3_controller : virtual public Music_controller
{
    Audio_local* local;

public:
    Music_local_mp3_controller();
    ~Music_local_mp3_controller();
    void set_file_location(const char*) override;
    void play_music() override;
    void pause_music() override;
    void stop_music() override;
};
