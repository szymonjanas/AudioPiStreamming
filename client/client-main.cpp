#include<gst/gst.h>
//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQmlContext>
#include "client-audio-controller.hpp"
#include <iostream>
#include "messageBus.hpp"

//#include "client-qt-controller.hpp"

void show_help()
{
    std::cout << "=================================================================" << std::endl <<
                 "= HELP FOR AUDIO PI DEVICE                                      =" << std::endl <<
                 "= -b | --bus      turn on console message bus                   =" << std::endl <<
                 "= -t | --test     set local address for test                    =" << std::endl <<
                 "=================================================================" << std::endl;
}

int main (  int   argc,
        char *argv[])
{

    bus_on();
    bus_on_communication();

//    const gchar* Host = "192.168.1.7";
//    gint Port = 5000;
//    std::string zmqAddress = "tcp://192.168.1.7:5555";
    const gchar* Host = "192.168.43.53";
    gint Port = 5000;
    std::string zmqAddress = "tcp://192.168.43.53:5555";

    bool help_not_used = true;
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp (argv[i], "-h") or !strcmp(argv[i], "--help"))
        {
            show_help();
            help_not_used = false;
        }
        if (!strcmp (argv[i], "-b") or !strcmp(argv[i], "--bus"))
        {
            bus_on();
            bus_message_short("BUS TURN ON!");
        }
        if (!strcmp (argv[i], "-t") or !strcmp(argv[i], "--test"))
        {
            Host = "127.0.0.1";
            Port = 5000;
            zmqAddress = "tcp://127.0.0.1:5555";
            bus_message_short("LOCAL TEST ENABLED");
        }
    }

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    QQmlContext* context = engine.rootContext();
//    QT_Controller ctrl;
//    context->setContextProperty("qtControl", &ctrl);


    if (help_not_used)
    {
        Audio_controller audio;

        bool first_time = true;
        while (true)
        {
            char status = getchar();
            switch (status)
            {
                case 'p':
                    bus_message_short("TEST SWITCH");
                    if (first_time){
                        bus_message_short("TEST");
                        first_time = false;
                        audio.set_type_of_stream(Type_of_music_stream::UDP_LIVE, Host, Port);
                        audio.set_communication_with_headquarters(zmqAddress);
                    }
                    audio.play();
                    break;
                case 'P':
                    if (!first_time)
                        audio.pause();
                    break;
                case 's':
                    if (!first_time){
                        audio.stop();
                        first_time = true;
                    }
                    break;
            }
        }
    }

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//    return app.exec();




//    local.set_location("../PigeonJohn-TheBomb.mp3");

//    client.set_location("../PigeonJohn-TheBomb.mp3");

}
