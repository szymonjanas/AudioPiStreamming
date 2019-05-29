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
    Type_of_music_stream now_setted;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Communication_Controller> communication;
    std::string zmqAddress;

    void clean();
public:
    Audio_controller();
    ~Audio_controller();

    bool play();
    bool pause();
    bool stop();
    bool set_file_location(const char * file_location);
    bool set_type_of_stream();
    bool set_type_of_stream(Type_of_music_stream type, const gchar* host, gint port);
    bool set_communication_with_headquarters(std::string zmqAddress);

    void operator=(Audio_controller&) = delete;
};



