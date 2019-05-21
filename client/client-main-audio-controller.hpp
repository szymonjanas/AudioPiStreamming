#pragma once
#include "client-controller-audio-live-udp.hpp"
#include "client-controller-audio-local.hpp"
#include "client-controller-audio-udp.hpp"
#include "client-controller-audio.hpp"
#include <string>

enum class Type_Of_Stream {UDP_LIVE, UDP_FILE, LOCAL_FILE};


class Music_main_controller
{
    Music_controller* music;
    bool is_file_location_set;

    const char * file_location;
    const gchar * host;
    gint port;
    std::string& zmqAddress;

    Type_Of_Stream type;
    bool is_stop;
public:
    Music_main_controller(const gchar * Host, gint Port, std::string& zmqAddress);
    ~Music_main_controller();
    void set_type_of_stream(Type_Of_Stream type);
    bool set_status_of_stream(MediaStatus status);
    void set_file_location(const char * file_location);
};
