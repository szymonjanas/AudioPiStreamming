#pragma once
#include "client-controller-audio-live-udp.hpp"
#include "client-controller-audio-local.hpp"
#include "client-controller-audio-udp.hpp"
#include "client-controller-audio.hpp"

enum class Type_Of_Stream {UDP_LIVE, UDP_FILE, LOCAL_FILE};


class Music_main_controller
{
    Music_controller* music;
    bool is_file_location_needed;
    bool is_ip_port_needed;
    bool is_file_location_set;
    bool is_ip_port_set;

    const char * file_location;
    gchar * host;
    gint port;
    const char * zmqAddress;

    Type_Of_Stream type;
public:
    Music_main_controller();
    ~Music_main_controller();
    void set_type_of_stream(Type_Of_Stream);
    void set_status_of_stream(MediaStatus);
    void set_file_location(const char *);
    void set_server_address(gchar *, gint, const char *);
};
