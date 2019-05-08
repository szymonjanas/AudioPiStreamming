#pragma once

#include<gst/gst.h>
#include "../media/media.hpp"
#include <string>

class Local : private Media
{

public:
    void set_pipeline_for_mp3();
    Local();
    ~Local();
    void set_location(const char* location);
    void set_status(std::string status);
};

