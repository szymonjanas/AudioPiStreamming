#include "client-main-audio-controller.hpp"

Music_main_controller::Music_main_controller(const gchar * Host, gint Port, std::string& zmqAddress)
    : zmqAddress(zmqAddress), host(Host)
{
   // music = NULL;
    is_file_location_set = false;
    port = Port;
    is_stop = true;
}

Music_main_controller::~Music_main_controller()
{
    delete music;
}

void Music_main_controller::set_type_of_stream(Type_Of_Stream type)
{
    //if (music != NULL) delete music;
    switch (type) {
        case Type_Of_Stream::UDP_FILE:
            if (is_file_location_set)
            {
                music = new Music_file_udp_controller(host, port, zmqAddress);
                music->set_file_location(file_location);
                is_stop = false;
            }
            break;
        case Type_Of_Stream::UDP_LIVE:
                music = new Music_controller_live_mp3_udp(host, port, zmqAddress);
                is_stop = false;
            break;
        case Type_Of_Stream::LOCAL_FILE:
            if (is_file_location_set)
            {
                music = new Music_local_mp3_controller;
                music->set_file_location(file_location);
                is_stop = false;
            }
            break;
    }
}

bool Music_main_controller::set_status_of_stream(MediaStatus status)
{
    switch (status)
    {
        case MediaStatus::PLAY:
            music->play_music();
            break;
        case MediaStatus::PAUSE:
            music->pause_music();
            break;
        case MediaStatus::STOP:
            music->stop_music();
            break;
    }
    return true;
}

void Music_main_controller::set_file_location(const char * file_location)
{
        this->file_location = file_location;
        is_file_location_set = true;
}
