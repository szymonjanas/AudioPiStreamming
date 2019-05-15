#include "device-communication.h"

#include <iostream>

Communication::Communication()
{

}

bool Communication::set_music_reciver_on(const char * host)
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
        // tcp://127.0.0.1:5555
   // std::cout << "Connecting to hello world device…" << std::endl;
    socket.connect (host);

        zmq::message_t request (8);
        memcpy (request.data (), "MUSIC ON", 8);

       // std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        unsigned long size = reply.size();
        std::string data(static_cast<char*>(reply.data()), size);
        if (data == "PLAYING")
        {
            std::cout << data <<std::endl;
            return true;
        }
}
