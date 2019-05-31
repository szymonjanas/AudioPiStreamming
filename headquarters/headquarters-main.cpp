#include <gst/gst.h>
#include "headquarters-audio-processing.hpp"
#include "headquarters-controler.hpp"
#include <sstream>
#include <iostream>
//#include "messageBus.hpp"

int main (  int   argc,
        char *argv[])
{

    std::cout << "WORKING..." << std::endl;
    bus_on();
    bus_on_communication();
    gchar* Host = "192.168.1.7";
    gint Port = 5000;
    std::string zmqAddress = "tcp://192.168.1.7:5555";

    bool help_not_used = true;
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp (argv[i], "-h") or !strcmp(argv[i], "--help"))
        {
            help_not_used = false;
        }
        if (!strcmp (argv[i], "-b") or !strcmp(argv[i], "--bus"))
        {
            bus_on();
            if (bus_status())
                bus_message_short("BUS TURN ON!");
        }
        if (!strcmp (argv[i], "-t") or !strcmp(argv[i], "--test"))
        {
            Host = "127.0.0.1";
            Port = 5000;
            zmqAddress = "tcp://127.0.0.1:5555";
            bus_message_short("LOCAL TEST ENABLED");
        }
    }

    while (true)
    {
        bus_message_short("PROGRAM RUNNING...");
        Manager manager(Host, Port, zmqAddress);
        manager.manage();
    }
}
