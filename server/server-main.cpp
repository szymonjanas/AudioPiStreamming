#include<gst/gst.h>
#include"server-local.hpp"
#include"server-rtsp.hpp"

int main (  int   argc,
        char *argv[])
{
    gst_init (&argc, &argv);

//    Local local;
//    local.set_pipeline_for_mp3();
//    local.set_location("../PigeonJohn-TheBomb.mp3");
//    local.set_status(MediaStatus::PLAY);

    Server server;
    server.set_server("192.168.1.7", 5000);
    server.set_location("../PigeonJohn-TheBomb.mp3");
    server.set_status(MediaStatus::PLAY);

}
