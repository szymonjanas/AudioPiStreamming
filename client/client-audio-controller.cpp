#include "client-audio-controller.hpp"

Audio_controller::Audio_controller()
{
    clean();
}

Audio_controller::~Audio_controller()
{

}

void Audio_controller::clean()
{
    is_setted = false;
    is_playing = false;
    now_setted = Type_of_music_stream::EMPTY;
    audio.reset();
    is_location_needed = false;
    is_location_setted = false;
    is_server_communication_connected = false;
    is_server_communication_needed = false;
    server_not_respond = false;
    communication.reset();
}

bool Audio_controller::play()
{
    if (is_location_needed)
        if(!is_location_setted) return false;

    if (is_server_communication_needed)
        if (!is_server_communication_connected) return false;

    if (is_setted)
    {
        if (is_server_communication_needed)
            if (is_server_communication_connected)
                communication->send_request(Request::SERVER_PLAY_UDP);

        audio->set_status(MediaStatus::PLAY);
        is_playing = true;
        return true;
    }
    return false;
}

bool Audio_controller::pause()
{
    if (is_location_setted)
    {
        if (is_setted)
        {
            audio->set_status(MediaStatus::PAUSE);
            is_playing = false;
            return true;
        }
        return false;
    }
}

bool Audio_controller::stop()
{
    if (is_setted or server_not_respond)
    {

        if (is_playing)
            audio->set_status(MediaStatus::STOP);
        if (is_server_communication_needed)
            if (is_server_communication_connected)
                if (communication->send_request(Request::SERVER_STOP_UDP) != Replay::SERVER_STOPED_UDP)
                    return false;
        clean();
        return true;
    }
    return false;
}

bool Audio_controller::set_file_location(const char * file_location)
{
    if (is_location_needed)
    {
        audio->set_location(file_location);
        is_location_setted = true;
        return true;
    }
    return false;
}

bool Audio_controller::send_request_to_server_set_udp()
{
    if (!is_server_communication_connected) return false;
    if (communication->send_request(Request::SERVER_SET_UDP) != Replay::SERVER_SETTED_UDP)
        return false;
    return true;
}

bool Audio_controller::set_udp_live()
{
    if (!send_request_to_server_set_udp())
        return false;

    audio = std::make_unique<Audio_udp_live>(host, port);
    audio->set_pipeline();

    now_setted = Type_of_music_stream::UDP_LIVE;
    is_server_communication_needed = true;

    return true;
}

bool Audio_controller::set_udp_file()
{
    if (!send_request_to_server_set_udp())
        return false;

    audio = std::make_unique<Audio_udp_file>(host, port);
    audio->set_pipeline();

    now_setted = Type_of_music_stream::UDP_FILE;
    is_server_communication_needed = true;
    is_location_needed = true;

    return true;
}

bool Audio_controller::set_local_file()
{
    audio = std::make_unique<Audio_local>();
    audio->set_pipeline();
    now_setted = Type_of_music_stream::UDP_LIVE;
    is_location_needed = true;
    return true;
}

bool Audio_controller::set_network_udp(const gchar* host, gint port)
{
    this->host = host;
    this->port = port;
}

bool Audio_controller::set_type_of_stream(Type_of_music_stream type)
{
    bool is_empty = false;
    if (now_setted == Type_of_music_stream::EMPTY)
        is_empty = true;
    else
    {
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
                if (!set_udp_live()) return false;
                break;
            case Type_of_music_stream::UDP_FILE:
                if (!set_udp_file()) return false;
                break;
            case Type_of_music_stream::LOCAL_FILE:
                if (!set_local_file()) return false;
                break;
        }
        if (type != Type_of_music_stream::EMPTY)
            is_setted = true;
        return true;
    }
    return false;
}

bool Audio_controller::set_communication_with_headquarters(std::string zmqAddress)
{
    communication = std::make_unique<Communication_Controller>(zmqAddress);
    if (communication->check_connection())
    {
        is_server_communication_connected = true;
        server_not_respond = false;
        return true;
    }
    else server_not_respond = true;
    is_server_communication_connected = false;

    return false;
}

bool Audio_controller::check_connection()
{
    if (is_server_communication_needed)
        if (is_server_communication_connected){
            if (communication->check_connection())
                return true;
            else
            {
                is_server_communication_connected = false;
                return false;
            }
        }
}

bool Audio_controller::get_set_status()
{
    return is_setted;
}

bool Audio_controller::get_play_status()
{
    return is_playing;
}
