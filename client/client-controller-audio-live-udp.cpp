#include "client-controller-audio-live-udp.hpp"

Music_controller_live_mp3_udp::Music_controller_live_mp3_udp(gchar * host, gint port, std::string& zmqAddress)
{
    message = new Communication_with_headquarters(zmqAddress);
    server = new Audio_server;
    server->set_server_live(host, port);
    is_headquarters_need_set = true;
}

Music_controller_live_mp3_udp::~Music_controller_live_mp3_udp()
{
    delete server;
    delete message;
}

void Music_controller_live_mp3_udp::play_music()
{
    if (is_headquarters_need_set)
    {
        if (message->request_for_headquarters("SETMP3", 6) == "SETTED")
            is_headquarters_need_set = false;
    }
   if (message->request_for_headquarters("PLAY", 4) == "PLAYING")
        server->set_status(MediaStatus::PLAY);
}

void Music_controller_live_mp3_udp::pause_music()
{
    server->set_status(MediaStatus::PAUSE);
}

void Music_controller_live_mp3_udp::stop_music()
{
    server->set_status(MediaStatus::STOP);
    if (!(message->request_for_headquarters("STOP", 4) == "STOPED"))
    {
        // HERE SOME ERROR MESSAGE
    }
}

void Music_controller_live_mp3_udp::set_file_location(const char *)
{
    // FOR VIRTUAL WORKINGconst char
}
