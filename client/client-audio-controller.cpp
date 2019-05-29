#include "client-audio-controller.hpp"

Music_controller::Music_controller()
{
    audio = std::make_unique<Audio>(nullptr);
    clean();
}

Music_controller::~Music_controller()
{

}

void Music_controller::clean()
{
    is_setted = false;
    is_playing = false;
    now_setted = Type_of_music_stream::EMPTY;
    audio.reset(nullptr);
    is_location_needed = false;
    is_location_setted = false;
    is_server_communication_connected = false;
    is_server_communication_needed = false;
    communication.reset(nullptr);
}

bool Music_controller::play()
{
    if (is_location_needed)
        if(!is_location_setted) return false;

    if (is_server_communication_needed)
        if (!is_server_communication_connected) return false;

    if (is_setted)
    {
        audio->set_status(MediaStatus::PLAY);
        return true;
    }
    return false;
}

bool Music_controller::pause()
{
    if (is_setted)
    {
        audio->set_status(MediaStatus::PAUSE);
        return true;
    }
    return false;
}

bool Music_controller::stop()
{
    if (is_setted)
    {
        audio->set_status(MediaStatus::STOP);
        if (is_server_communication_connected)
            for (unsigned short i = 0; i < 3; ++i)
                if (communication->send_request(Request::SERVER_STOP_UDP) == Replay::SERVER_STOPED_UDP)
                    i = 4;
        clean();
        return true;
    }
    return false;
}

bool Music_controller::set_file_location(const char * file_location)
{
    if (is_location_needed)
    {
        audio->set_location(file_location);
        is_location_setted = true;
        return true;
    }
    return false;
}

bool Music_controller::set_type_of_stream(Type_of_music_stream type = Type_of_music_stream::LOCAL_FILE)
{
    return set_type_of_stream(type, "", 0);
}

bool Music_controller::set_type_of_stream(Type_of_music_stream type, const gchar* host, gint port)
{
    bool is_empty = false;
    if (now_setted == Type_of_music_stream::EMPTY)
        is_empty = true;
    else {
        stop();
        is_empty = true;
    }

    if (is_empty)
    {
        switch (type)
        {
            case Type_of_music_stream::EMPTY:
                break;
            case Type_of_music_stream::UDP_LIVE:
                if (!is_server_communication_connected) return false;
                if (communication->send_request(Request::SERVER_SET_UDP) != Replay::SERVER_SETTED_UDP) return false;
                audio = std::make_unique<Audio>(Audio_udp_live(host, port));
                audio->set_pipeline();
                now_setted = Type_of_music_stream::UDP_LIVE;
                is_server_communication_needed = true;
                break;
            case Type_of_music_stream::UDP_FILE:
                if (!is_server_communication_connected) return false;
                if (communication->send_request(Request::SERVER_SET_UDP) != Replay::SERVER_SETTED_UDP) return false;
                audio = std::make_unique<Audio>(Audio_udp_file(host, port));
                audio->set_pipeline();
                now_setted = Type_of_music_stream::UDP_FILE;
                is_location_needed = true;
                break;
            case Type_of_music_stream::LOCAL_FILE:
                if (is_server_communication_connected) return false;
                audio = std::make_unique<Audio>(Audio_local());
                audio->set_pipeline();
                now_setted = Type_of_music_stream::UDP_LIVE;
                is_location_needed = true;
                break;
        }
        if (type != Type_of_music_stream::EMPTY)
            is_setted = true;
    }
}

bool Music_controller::set_communication_with_headquarters(std::string zmqAddress)
{
    this->zmqAddress=zmqAddress;
    communication = std::make_unique<Communication_Controller>(Communication_Controller(this->zmqAddress));
    for (unsigned short i = 0; i < 3; ++i)
        if (communication->check_connection())
        {
            is_server_communication_connected = true;
            return true;
        }
    bus_message_error_report("client-controller-audio",
                             "Music-controller",
                             "set-communication",
                             "SERVER NOT RESPOND");
    is_server_communication_connected = false;
    return false;
}
