#pragma once

#include<gst/gst.h>
#include "media.hpp"
#include"client-audio.hpp"

class Audio_local : private Media, virtual public Audio
{

public:
    Audio_local();
    ~Audio_local() override;
    void set_pipeline() override;
    void set_location(const char* location) override;
    void set_status(MediaStatus status) override;
};

