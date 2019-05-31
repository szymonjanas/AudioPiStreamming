#pragma once

#include <QObject>
#include <QString>
#include "client-audio-controller.hpp"

class QT_Controller : public QObject, private Audio_controller
{
    const gchar* Host;
    gint Port;
    std::string zmqAddress;

    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

    QString message;
    void setStatus(const QString & message);

    Type_of_music_stream type_of_stream;

    bool set_udp_address();
    void set_file_location();
public:
    QT_Controller();
    ~QT_Controller();

    QString status();
public slots:
    void set_udp_live();
    void set_local_file();
    void set_udp_file();
    void set_empty();
    bool set();

    void play();
    void pause();
    void stop();



signals:
    void statusChanged();
};
