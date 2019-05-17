#pragma once

#include<gst/gst.h>
#include "../media/media.hpp"

class Audio_local : private Media
{

public:
    void set_pipeline_for_mp3();
    Audio_local();
    ~Audio_local();
    void set_location(const char* location);
    void set_status(MediaStatus status);
};

