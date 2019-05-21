#pragma once

#include <QObject>
#include <QString>
#include "client-main-audio-controller.hpp"


class QT_Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

    Music_main_controller* music;
    QString message;
    void setStatus(const QString & message);
    bool isAlreadySetted;

    Type_Of_Stream type_of_stream;

    bool set_udp_live_with_default_address();
    bool set_local_stream_from_file();
public:
    QT_Controller();
    ~QT_Controller();

    QString status();
public slots:
    void set_udp_live();
    void set_local_stream();
    void set_empty();

    void play();
    void pause();
    void stop();



signals:
    void statusChanged();
};
