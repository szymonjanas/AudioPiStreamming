#include "base-controler.hpp"



void Controler::play_music()
{
    Reciver_mp3 music;

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);

    // tcp://127.0.0.1:5555
    socket.bind ("tcp://192.168.1.7:5555");

    while (true) {
        zmq::message_t request;
        socket.recv (&request);
        unsigned long size = request.size();
        std::string data(static_cast<char*>(request.data()), size);
        if (data == "MUSIC ON"){

            zmq::message_t reply (7);
            memcpy (reply.data (), "PLAYING", 7);
            socket.send (reply);
            music.set_reciver_mp3("192.168.1.7", 5000);
            music.set_status(MediaStatus::PLAY);
        }
    }
}
