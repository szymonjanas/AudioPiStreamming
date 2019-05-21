#include "client-qt-controller.hpp"

QT_Controller::QT_Controller()
{
    isAlreadySetted = false;
    type_of_stream = Type_Of_Stream::EMPTY;
    music = nullptr;
}

QT_Controller::~QT_Controller()
{
    delete music;
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

bool QT_Controller::set_udp_live_with_default_address()
{
    if (!isAlreadySetted){
        const gchar* Host = "192.168.1.7";
        gint Port = 5000;
        std::string zmqAddress = "tcp://192.168.1.7:5555";
        music = new Music_main_controller(Host, Port, zmqAddress);
        music->set_type_of_stream(Type_Of_Stream::UDP_LIVE);
        isAlreadySetted = true;
        return true;
    }
    else {
        QString err = "Stop first!";
        setStatus(err);
        return false;
    }
}

bool QT_Controller::set_local_stream_from_file()
{
    if (!isAlreadySetted){
        QString msg = "Playing local from file ...";
        setStatus(msg);
        const gchar* Host = "192.168.1.7";
        gint Port = 5000;
        std::string zmqAddress = "tcp://192.168.1.7:5555";
        music = new Music_main_controller(Host, Port, zmqAddress);
        music->set_file_location("../PigeonJohn-TheBomb.mp3");
        music->set_type_of_stream(Type_Of_Stream::LOCAL_FILE);
        isAlreadySetted = true;
        return true;
    }
    else {
        QString err = "Stop first!";
        setStatus(err);
        return false;
    }
}

void QT_Controller::play()
{
    switch (type_of_stream) {
        case Type_Of_Stream::UDP_LIVE:
            set_udp_live_with_default_address();
            break;
        case Type_Of_Stream::LOCAL_FILE:
            set_local_stream_from_file();
            break;
        case Type_Of_Stream::UDP_FILE:
            break;
        case Type_Of_Stream::EMPTY:

            isAlreadySetted = false;
            break;
    }
    if (isAlreadySetted){
    QString msg = "Streamming music live ...";
    setStatus(msg);
    music->set_status_of_stream(MediaStatus::PLAY);
    }
}

void QT_Controller::pause()
{
    if (isAlreadySetted){
    QString msg = "Pause streamming music live ...";
    setStatus(msg);
    music->set_status_of_stream(MediaStatus::PAUSE);
    }
}

void QT_Controller::stop()
{
    if (isAlreadySetted){
    QString msg = "Stoped stream music live.";
    setStatus(msg);
    music->set_status_of_stream(MediaStatus::STOP);
    isAlreadySetted = false;
    }
}

void QT_Controller::set_udp_live()
{
    type_of_stream = Type_Of_Stream::UDP_LIVE;
}

void QT_Controller::set_local_stream()
{
    type_of_stream = Type_Of_Stream::LOCAL_FILE;
}

void QT_Controller::set_empty()
{
    stop();
    if (music != nullptr)
    {
        delete music;
        music = nullptr;
    }
    if (type_of_stream != Type_Of_Stream::EMPTY)
        type_of_stream = Type_Of_Stream::EMPTY;

}
