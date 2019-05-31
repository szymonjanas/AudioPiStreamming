#include "client-qt-controller.hpp"

QT_Controller::QT_Controller()
{
    type_of_stream = Type_of_music_stream::EMPTY;
}

QT_Controller::~QT_Controller()
{

}

void QT_Controller::setStatus(const QString & message)
{
    this->message = message;
    emit statusChanged();
}

QString QT_Controller::status()
{
    return message;
}

bool QT_Controller::set_udp_address()
{
    if (!get_set_status())
    {
        Host = "192.168.1.7";
        Port = 5000;
        zmqAddress = "tcp://192.168.1.7:5555";
        set_network_udp(Host, Port);
        set_communication_with_headquarters(zmqAddress);
        return true;
    }
    return false;
}

void QT_Controller::set_file_location()
{
    Audio_controller::set_file_location("../PigeonJohn-TheBomb.mp3");
}

void QT_Controller::play()
{
    if (!get_set_status())
            set();
    if (!get_play_status())
    {
        if (Audio_controller::play())
            setStatus("Playing...");
        else
            setStatus("Can not play!");
    }
}

void QT_Controller::pause()
{
    Audio_controller::pause();
    setStatus("Paused");
}

void QT_Controller::stop()
{
    Audio_controller::stop();
    setStatus("Stopped.");
}

bool QT_Controller::set()
{
    switch (type_of_stream)
    {
        case Type_of_music_stream::UDP_FILE:
            set_udp_address();
            set_type_of_stream(type_of_stream);
            set_file_location();
            return true;
        case Type_of_music_stream::UDP_LIVE:
            set_udp_address();
            set_type_of_stream(type_of_stream);
            return true;
        case Type_of_music_stream::LOCAL_FILE:
            set_type_of_stream(type_of_stream);
            set_file_location();
            return true;
        case Type_of_music_stream::EMPTY:
            return false;
    }
    return false;
}

void QT_Controller::set_udp_live()
{
    if (!get_set_status())
    {
        type_of_stream = Type_of_music_stream::UDP_LIVE;
        setStatus("Remote live play...");
    }
}

void QT_Controller::set_local_file()
{
    if (!get_set_status())
    {
        type_of_stream = Type_of_music_stream::LOCAL_FILE;
        setStatus("Local file play...");
    }
}

void QT_Controller::set_udp_file()
{
    if (!get_set_status())
    {
        type_of_stream = Type_of_music_stream::UDP_FILE;
        setStatus("Remote file play...");
    }
}

void QT_Controller::set_empty()
{
    setStatus("");
    stop();
    type_of_stream = Type_of_music_stream::EMPTY;
}
