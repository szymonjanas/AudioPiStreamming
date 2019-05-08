#pragma once

#include<gst/gst.h>
#include"../media/media.hpp"
#include <string>

class Server : private Media
{

public:
    Server();
    ~Server();
    void set_server(gchar* host, gint port);
    void set_location(const char* location);
    void set_status(std::string status);
};
