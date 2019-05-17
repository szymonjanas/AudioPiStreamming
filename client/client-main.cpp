#include<gst/gst.h>
//#include"client-local.hpp"
//#include"client-udp.hpp"
#include "client-controller-audio.hpp"
#include <iostream>
#include "messageBus.hpp"
#include "client-main-audio-controller.hpp"

void show_help()
{
    std::cout << "=================================================================" << std::endl <<
                 "= HELP FOR AUDIO PI DEVICE                                      =" << std::endl <<
                 "= -b | --bus      turn on console message bus                   =" << std::endl <<
                 "= -t | --test     set local address for test                    =" << std::endl <<
                 "=================================================================" << std::endl;
}

int main (  int   argc,
        char *argv[])
{

    bus_on();
    bus_on_communication();
    std::cout << "CLIENT WORKING" << std::endl;

    gchar* Host = "192.168.1.7";
    gint Port = 5000;
    std::string zmqAddress = "tcp://192.168.1.7:5555";

    bool help_not_used = true;
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp (argv[i], "-h") or !strcmp(argv[i], "--help"))
        {
            show_help();
            help_not_used = false;
        }
        if (!strcmp (argv[i], "-b") or !strcmp(argv[i], "--bus"))
        {
            bus_on();
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

    if (help_not_used)
    {
        Music_main_controller music(Host, Port, zmqAddress);
        music.set_type_of_stream(Type_Of_Stream::UDP_LIVE);
        while (true)
        {
            char status = getchar();
            switch (status)
            {
                case 'p':
                    music.set_status_of_stream(MediaStatus::PLAY);
                    break;
                case 'P':
                    music.set_status_of_stream(MediaStatus::PAUSE);
                    break;
                case 's':
                    music.set_status_of_stream(MediaStatus::STOP);
                    break;

            }
        }
    }


//    local.set_location("../PigeonJohn-TheBomb.mp3");

//    client.set_location("../PigeonJohn-TheBomb.mp3");

}
