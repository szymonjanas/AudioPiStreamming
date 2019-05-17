#include "client-controller-audio-live-udp.hpp"

Music_live_udp_controller::Music_live_udp_controller(gchar * host, gint port, const char * zmqAddress)
{
    message = new Communication_with_headquarters(zmqAddress);
    server = new Audio_server;
    server->set_server_live(host, port);
}

Music_live_udp_controller::~Music_live_udp_controller()
{
    delete server;
    delete message;
}

void Music_live_udp_controller::play_music()
{
   if (message->request_for_headquarters("PLAY", 4) == "PLAYING")
        server->set_status(MediaStatus::PLAY);
}

void Music_live_udp_controller::pause_music()
{
    server->set_status(MediaStatus::PAUSE);
}

void Music_live_udp_controller::stop_music()
{
    server->set_status(MediaStatus::STOP);
    if (!(message->request_for_headquarters("STOP", 4) == "STOPED"))
    {
        // HERE SOME ERROR MESSAGE
    }
}

void Music_live_udp_controller::set_file_location(const char *)
{
    // FOR VIRTUAL WORKINGconst char
}
