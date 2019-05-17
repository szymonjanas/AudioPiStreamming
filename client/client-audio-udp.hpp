#pragma once

#include<gst/gst.h>
#include"../media/media.hpp"

class Audio_server : private Media
{

public:
    Audio_server();
    ~Audio_server();
    void set_server(gchar* host, gint port);
    void set_location(const char* location);
    void set_status(MediaStatus status);
    void set_server_live(gchar* host, gint port);
};
