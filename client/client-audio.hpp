#pragma once
#include "media/media.hpp"

class Audio
{

public:
    virtual void set_status(MediaStatus status) = 0;
    virtual bool set_pipeline() = 0;
    virtual void set_location(const char* location) = 0;

    Audio();
    virtual ~Audio();

};
