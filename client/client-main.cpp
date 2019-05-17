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

    std::cout << "WORKING" << std::endl;

    gchar* Host = "192.168.1.7";
    gint Port = 5000;
    const char * zmqAddress = "tcp://192.168.1.2:5555";

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
            bus_on_off(true);
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
        bool run_flag = true;
        while (run_flag)
        {
            //Music_live_udp_controller ctrl(Host,Port,zmqAddress);
            //ctrl.play_music();

        }

    }



   // int Argc = 1;
   // char** Argv = new char* ();
   // Argv[0] = "foo";

    //gst_init (&Argc, &Argv);

   // Controler ctrl;
   // ctrl.play_music();



//    Local local;
//    local.set_pipeline_for_mp3();
//    local.set_location("../PigeonJohn-TheBomb.mp3");
//    local.set_status(MediaStatus::PLAY);

//    Server client;
//    client.set_server_live(localHost, localPort);
//    client.set_location("../PigeonJohn-TheBomb.mp3");
//    client.set_status(MediaStatus::PLAY);

}
