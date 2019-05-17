#include "client-controller-audio-udp.hpp"

Music_file_udp_controller::Music_file_udp_controller(gchar * host, gint port, const char * zmqAddress)
{
    server = new Audio_server;
    server->set_server(host, port);
    message = new Communication_with_headquarters(zmqAddress);
}

Music_file_udp_controller::~Music_file_udp_controller()
{
    delete server;
    delete message;
}

void Music_file_udp_controller::set_file_location(const char * location)
{
    server->set_location(location);
}

void Music_file_udp_controller::play_music()
{
    if (message->request_for_headquarters("PLAY", 4) == "PLAYING")
        server->set_status(MediaStatus::PLAY);
}

void Music_file_udp_controller::pause_music()
{
    if (message->request_for_headquarters("PAUSE", 5) == "PAUSED")
        server->set_status(MediaStatus::PAUSE);
}

void Music_file_udp_controller::stop_music()
{
    server->set_status(MediaStatus::STOP);
    if (!(message->request_for_headquarters("STOP", 4) == "STOPED"))
    {
        // HERE SOME ERROR MESSAGE
    }
}
