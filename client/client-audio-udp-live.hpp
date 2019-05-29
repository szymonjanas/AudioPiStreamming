#pragma once

#include<gst/gst.h>
#include"../media/media.hpp"
#include"client-audio.hpp"

class Audio_udp_live : private Media, virtual public Audio
{
    const gchar* host;
    gint port;
public:
    Audio_udp_live(const gchar* host, gint port);
    ~Audio_udp_live() override;
    void set_pipeline() override;
    void set_status(MediaStatus status) override;
    void set_location(const char*) override;
};
