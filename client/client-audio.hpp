#pragma once
#include "media/media.hpp"

class Audio
{

public:
    virtual void set_status(MediaStatus status) = 0;
    virtual void set_pipeline();
    virtual void set_location(const char* location);

    Audio();
    virtual ~Audio();

};
