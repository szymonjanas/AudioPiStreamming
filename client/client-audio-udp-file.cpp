#include "client-audio-udp-file.hpp"

Audio_udp_file::Audio_udp_file(const gchar* host, gint port) :
                               host(host), port(port)
{}

Audio_udp_file::~Audio_udp_file()
{}

void Audio_udp_file::set_status(MediaStatus status)
{
    Media::set_status(status);
}

bool Audio_udp_file::set_pipeline()
{
    pipeline = gst_pipeline_new ("audio-streamer");
    source   = gst_element_factory_make ("filesrc",       "file-source");
    parse    = gst_element_factory_make ("mpegaudioparse","parse");
    pay     = gst_element_factory_make  ("rtpmpapay",     "pay");
    sink     = gst_element_factory_make ("udpsink",       "udpsink");

    if (!pipeline || !source ||!parse || !pay || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        return false;
    }
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, parse, pay, sink, NULL);
    gst_element_link_many (source, parse, pay, sink, NULL);

    g_object_set(G_OBJECT(sink), "host", host, "port", port, NULL);
    return true;
}

void Audio_udp_file::set_location(const char *location)
{
    g_object_set (G_OBJECT (source), "location", location , NULL);
    g_print ("File location: %s\n", location);
}
