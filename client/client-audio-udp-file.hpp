#pragma once

#include<gst/gst.h>
#include"media.hpp"
#include"client-audio.hpp"

class Audio_udp_file : private Media, virtual public Audio
{
    const gchar* host;
    gint port;
public:
    Audio_udp_file(const gchar* host, gint port);
    ~Audio_udp_file() override;
    void set_location(const char* location) override;
    void set_status(MediaStatus status) override;
    void set_pipeline() override;
};
