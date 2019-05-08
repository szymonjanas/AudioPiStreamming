#include "server-udp.hpp"

Server::Server()
{}

Server::~Server()
{}

void Server::set_status(std::string status)
{
    if (status == "PLAY")
        Media::set_status(MediaStatus::PLAY);
    if (status == "PAUSE")
        Media::set_status(MediaStatus::PAUSE);
    if (status == "STOP")
        Media::set_status(MediaStatus::STOP);
}

void Server::set_server(gchar* host, gint port)
{
    pipeline = gst_pipeline_new ("audio-streamer");
    source   = gst_element_factory_make ("filesrc",       "file-source");
    parse    = gst_element_factory_make ("mpegaudioparse","bin");
    conv     = gst_element_factory_make ("rtpmpapay",  "pay");
    sink     = gst_element_factory_make ("udpsink", "udpsink");

    if (!pipeline || !source ||!parse || !conv || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        exit(1);
    }
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, parse, conv, sink, NULL);

    gst_element_link (source, parse);
    gst_element_link_many (parse, conv, sink, NULL);

    g_object_set(G_OBJECT(sink), "host", host, "port", port, NULL);
}

void Server::set_location(const char *location)
{
    g_object_set (G_OBJECT (source), "location", location , NULL);
    g_print ("File location: %s\n", location);

}
