#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp

class Controler
{
    public:
    void set_controlling_device();
    void start_reciving_udp(std::string format);
};
