#pragma once

#include <gst/gst.h>
#include "media.hpp"

class Play_audio_live_from_client : private Media
{
    GstElement *queue, *depay, *decoder, *convert, *resample;
public:
    bool set_live_player_udp_mp3(gchar* host, gint port);
    void set_status(MediaStatus status);
};
