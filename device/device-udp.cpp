#include "device-udp.hpp"

Server::Server()
{}

Server::~Server()
{}

void Server::set_status(MediaStatus status)
{
    Media::set_status(status);
}

void Server::set_server(gchar* host, gint port)
{
    pipeline = gst_pipeline_new ("audio-streamer");
    source   = gst_element_factory_make ("filesrc",       "file-source");
    parse    = gst_element_factory_make ("mpegaudioparse","parse");
    pay     = gst_element_factory_make  ("rtpmpapay",     "pay");
    sink     = gst_element_factory_make ("udpsink",       "udpsink");

    if (!pipeline || !source ||!parse || !pay || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        exit(1);
    }
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, parse, pay, sink, NULL);
    gst_element_link_many (source, parse, pay, sink, NULL);

    g_object_set(G_OBJECT(sink), "host", host, "port", port, NULL);
}

void Server::set_server_live(gchar *host, gint port)
{
    pipeline = gst_pipeline_new ("audio-streamer");
    source   = gst_element_factory_make ("pulsesrc",        "live-source");
    conv     = gst_element_factory_make ("audioconvert",    "convert");
    encoder  = gst_element_factory_make ("lamemp3enc",      "encoder");
    pay      = gst_element_factory_make ("rtpmpapay",       "pay");
    sink     = gst_element_factory_make ("udpsink",         "udpsink");

    if (!pipeline || !source ||!conv || !encoder || !pay || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        exit(1);
    }
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, conv, encoder, pay, sink, NULL);
    gst_element_link_many (source, conv, encoder, pay, sink, NULL);

    g_object_set(G_OBJECT(source), "device", "alsa_output.pci-0000_00_14.2.analog-stereo.monitor", NULL);
    g_object_set(G_OBJECT(sink), "host", host, "port", port, NULL);
}

void Server::set_location(const char *location)
{
    g_object_set (G_OBJECT (source), "location", location , NULL);
    g_print ("File location: %s\n", location);
}
