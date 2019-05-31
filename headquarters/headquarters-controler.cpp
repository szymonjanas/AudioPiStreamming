#include "headquarters-controler.hpp"

Manager::Manager(gchar * host, gint port, std::string zmqAddress)
    :zmqAddress(zmqAddress)
{
    this->host = host;
    this->port = port;

    set_connection();

    is_setted = false;
    is_playing = false;
}

Manager::~Manager()
{
    delete audio;
    delete communication;
}

void Manager::set_connection()
{
    communication = new Communication_controler (zmqAddress);
}

bool Manager::set()
{
    audio = new Play_audio_live_from_client;
    if (audio->set_live_player_udp_mp3(host, port))
    {
        is_setted = true;
        return true;
    }
    return false;
}

bool Manager::play()
{
    if (is_setted){
        audio->set_status(MediaStatus::PLAY);
        is_playing = true;
        return true;
    }
    return false;
}

bool Manager::stop()
{
    if (is_setted and is_playing)
    {
        audio->set_status(MediaStatus::STOP);
        delete audio;
        is_setted = false;
        is_playing = false;
        return true;
    }
    return false;
}

void Manager::manage()
{
    while (true) {

        Request request = communication->get_request_from_client();

        switch (request)
        {
            case Request::SERVER_SET_UDP:
                if (set())
                    communication->send_replay(Replay::SERVER_SETTED_UDP);
                else communication->send_replay(Replay::SERVER_REQUEST_DENIDED);
                break;
            case Request::SERVER_STOP_UDP:
                if (stop())
                    communication->send_replay(Replay::SERVER_STOPED_UDP);
                else communication->send_replay(Replay::SERVER_REQUEST_DENIDED);
                break;
            case Request::SERVER_WRONG_REQUEST:
                communication->send_replay(Replay::SERVER_WRONG_REQUEST);
                break;
            case Request::SERVER_TEST_CONNECTION:
                communication->send_replay(Replay::SERVER_CONNECTED);
                break;
            case Request::SERVER_PLAY_UDP:
                if (play())
                    communication->send_replay(Replay::SERVER_PLAYED_UDP);
                else communication->send_replay(Replay::SERVER_REQUEST_DENIDED);
                break;
        }
    }
}
