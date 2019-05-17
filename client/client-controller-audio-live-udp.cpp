#include "client-controller-audio-live-udp.hpp"

Music_controller_live_mp3_udp::Music_controller_live_mp3_udp(gchar * host, gint port, std::string& zmqAddress)
{
    message = new Communication_with_headquarters(zmqAddress);
    server = new Audio_server;
    server->set_server_live(host, port);
    is_headquarters_need_set = true;
    is_play = false;
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
    if (!is_play)
        if (message->request_for_headquarters("PLAY", 4) == "PLAYING")
        {
            is_play = true;
            server->set_status(MediaStatus::PLAY);
        }
    if (is_play)
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
        bus_message_error_report("Controller audio live udp", "Music controller mp3 udp live", "stop music", "Headquarters does not replay");
}

void Music_controller_live_mp3_udp::set_file_location(const char *)
{
    // FOR VIRTUAL WORKING
}
