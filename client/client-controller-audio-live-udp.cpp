#include "client-controller-audio-live-udp.hpp"

Controller::Controller(gchar * host, gint port, const char * zmqAddress)
{
    message = new Communication_with_headquarters(zmqAddress);
    server = new Audio_server;
    server->set_server_live(host, port);
    is_headquarters_need_set = true;
}

Controller::~Controller()
{
    delete server;
    delete message;
}

void Controller::play_music()
{
    if (is_headquarters_need_set)
    {
        if (message->request_for_headquarters("SETMP3", 6) == "SETTED")
            is_headquarters_need_set = false;
    }
   if (message->request_for_headquarters("PLAY", 4) == "PLAYING")
        server->set_status(MediaStatus::PLAY);
}

void Controller::pause_music()
{
    server->set_status(MediaStatus::PAUSE);
}

void Controller::stop_music()
{
    server->set_status(MediaStatus::STOP);
    if (!(message->request_for_headquarters("STOP", 4) == "STOPED"))
    {
        // HERE SOME ERROR MESSAGE
    }
}

void Controller::set_file_location(const char *)
{
    // FOR VIRTUAL WORKINGconst char
}
