#include "device-controler.hpp"
#include <iostream>


void Controler::play_music()
{
    Communication pi;
    Server server;
    server.set_server_live("192.168.1.7", 5000);

    if (pi.set_music_reciver_on("tcp://192.168.1.7:5555"))
        server.set_status(MediaStatus::PLAY);
    char info;
    std::cout << "WRITE COMMAND: p - play, P - pause, s - stop" << std::endl;

    std::cin >> info;
    switch (info)
    {
        case 'p':
            server.set_status(MediaStatus::PLAY);
            break;
        case 'P':
            server.set_status(MediaStatus::PAUSE);
            break;
        case 's':
            server.set_status(MediaStatus::STOP);
            break;
    }
}
