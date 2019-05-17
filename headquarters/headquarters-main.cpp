#include <gst/gst.h>
#include "headquarters-audio-processing.hpp"
#include "headquarters-controler.hpp"
#include <sstream>
#include <iostream>

int main (  int   argc,
        char *argv[])
{

    std::cout << "WORKING" << std::endl;
    int Argc = 1;
    char** Argv = new char* ();
    Argv[0] = "foo";
    gst_init (&Argc, &Argv);

    Controler ctrl;
    ctrl.play_music();

//    Reciver_mp3 reciver;
//    reciver.set_reciver_mp3("192.168.1.7", 5000);
//    reciver.set_status(MediaStatus::PLAY);
}
