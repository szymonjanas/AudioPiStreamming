#pragma once
#include "client-audio-local-mp3.hpp"
#include "client-audio-udp-file.hpp"
#include "client-audio-udp-live.hpp"
#include "client-communication-controller-with-headquarters.hpp"

#include <memory>

enum class Type_of_music_stream{
    UDP_LIVE,
    UDP_FILE,
    LOCAL_FILE,
    EMPTY
};

class Audio_controller
{
    bool is_setted;
    bool is_playing;
    bool is_location_needed;
    bool is_location_setted;
    bool is_server_communication_connected;
    bool is_server_communication_needed;
    bool server_not_respond;
    Type_of_music_stream now_setted;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Communication_Controller> communication;
    const gchar* host;
    gint port;

    bool send_request_to_server_set_udp();
    bool set_udp_live();
    bool set_udp_file();
    bool set_local_file();

public:
    Audio_controller();
    ~Audio_controller();

    void clean();
    bool play();
    bool pause();
    bool stop();
    bool set_file_location(const char * file_location);
    bool set_network_udp(const gchar* host, gint port);
    bool set_type_of_stream(Type_of_music_stream type);
    bool set_communication_with_headquarters(std::string zmqAddress);
    bool check_connection();
    bool get_set_status();
    bool get_play_status();
    void operator=(Audio_controller&) = delete;

};
