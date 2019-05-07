#pragma once

#include <gst/gst.h>
#include <cstdlib> // for exit function on raspberry

#include "../media/media.hpp"

class Reciver_mp3 : private Media
{
    GstElement *queue, *depay, *decoder, *convert, *resample;
public:
    void set_reciver_mp3(gchar* host, gint port);
    void set_status(MediaStatus status);
};
