#include "client-main-audio-controller.hpp"

Music_main_controller::Music_main_controller()
{
    is_file_location_needed = false;
    is_ip_port_needed = false;
    is_file_location_set = false;
    is_ip_port_set = false;
}

Music_main_controller::~Music_main_controller()
{
    delete music;

}

void Music_main_controller::set_type_of_stream(Type_Of_Stream type)
{
    this->type = type;
    switch (type) {
        case Type_Of_Stream::UDP_FILE:
            is_file_location_needed = true;
            is_ip_port_needed = true;
            break;
        case Type_Of_Stream::UDP_LIVE:
            is_ip_port_needed = true;
            break;
        case Type_Of_Stream::LOCAL_FILE:
            is_file_location_needed = true;
            break;
    }
}

void Music_main_controller::set_status_of_stream(MediaStatus status)
{
    switch (type) {
        case Type_Of_Stream::UDP_FILE:
            if (is_file_location_set and is_ip_port_set)
            {
                music = new Music_file_udp_controller(host, port, zmqAddress);
                music->set_file_location(file_location);
            }
            break;
        case Type_Of_Stream::UDP_LIVE:
            if (is_ip_port_set)
            {
                music = new Music_live_udp_controller(host, port, zmqAddress);
            }
            break;
        case Type_Of_Stream::LOCAL_FILE:
            if (is_file_location_set)
            {
                music = new Music_local_mp3_controller;
                music->set_file_location(file_location);
            }
            break;
    }
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
}

void Music_main_controller::set_file_location(const char * file_location)
{
    if (is_file_location_needed)
    {
        this->file_location = file_location;
        is_file_location_set = true;
    }
}

void Music_main_controller::set_server_address(gchar * Host, gint Port, const char * ZmqAddress)
{
    if (is_ip_port_needed)
    {
        host = Host;
        port = Port;
        zmqAddress = ZmqAddress;
        is_ip_port_set = true;
    }
}
