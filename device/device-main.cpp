#include<gst/gst.h>
//#include"device-local.hpp"
//#include"device-udp.hpp"
#include "device-controler.hpp"
#include <iostream>

int main (  int   argc,
        char *argv[])
{

    std::cout << "WORKING" << std::endl;
    //Controler ctrl;
    //ctrl.set_music_reciver_on("tcp://127.0.0.1:5555");

    int Argc = 1;
    char** Argv = new char* ();
    Argv[0] = "foo";

    gst_init (&Argc, &Argv);

    Controler ctrl;
    ctrl.play_music();

//    gchar* piHost = "192.168.1.7";
//    gint piPort = 5000;
//    gchar* localHost = "127.0.0.1";
//    gint localPort = 5000;

//    Local local;
//    local.set_pipeline_for_mp3();
//    local.set_location("../PigeonJohn-TheBomb.mp3");
//    local.set_status(MediaStatus::PLAY);

//    Server device;
//    device.set_server_live(localHost, localPort);
//    device.set_location("../PigeonJohn-TheBomb.mp3");
//    device.set_status(MediaStatus::PLAY);

}
