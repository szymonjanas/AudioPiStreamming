#include <gst/gst.h>
#include "client-audio-processing.hpp"

int main (  int   argc,
        char *argv[])
{
    gst_init (&argc, &argv);
    Reciver_mp3 reciver;
    reciver.set_reciver_mp3("192.168.1.7", 5000);
    reciver.set_status(MediaStatus::PLAY);
}
