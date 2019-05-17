#include "client-controller-audio-local.hpp"

Music_local_mp3_controller::Music_local_mp3_controller()
{
    local = new Audio_local;
    local->set_pipeline_for_mp3();
}

void Music_local_mp3_controller::set_file_location(const char * location)
{
    local->set_location(location);
}

Music_local_mp3_controller::~Music_local_mp3_controller()
{
    delete local;
}

void Music_local_mp3_controller::play_music()
{
    local->set_status(MediaStatus::PLAY);
}

void Music_local_mp3_controller::pause_music()
{
    local->set_status(MediaStatus::PAUSE);
}

void Music_local_mp3_controller::stop_music()
{
    local->set_status(MediaStatus::STOP);
}
