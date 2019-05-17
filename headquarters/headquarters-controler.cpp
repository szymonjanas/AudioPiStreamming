#include "headquarters-controler.hpp"

Manager::Manager(gchar * host, gint port, const char * zmqAddress)
{
    this->host = host;
    this->port = port;
    this->zmqAddress = zmqAddress;
}

Manager::~Manager()
{
    delete play;
    delete communication;
}

void Manager::start()
{
    communication = new Communication (zmqAddress);
    play = new Play_audio_live_from_client;
    while (true) {
        std::string request = communication->waiting_for_request_from_client();
        if (request == "SETMP3")
        {
            play->set_player_udp_mp3(host, port);
            communication->send_confirm_or_refuse("MP3SETTED", 9);
        }
        if (request == "PLAY")
        {
            play->set_status(MediaStatus::PLAY);
            communication->send_confirm_or_refuse("PLAYING", 7);
        }
        if (request == "PAUSE")
        {
            play->set_status(MediaStatus::PAUSE);
            communication->send_confirm_or_refuse("PAUSED", 6);
        }
        if (request == "STOP")
        {
            play->set_status(MediaStatus::STOP);
            communication->send_confirm_or_refuse("STOPED", 6);
        }
    }
}

