#include "client-audio-udp-live.hpp"

Audio_udp_live::Audio_udp_live(const gchar* host, gint port) :
    host(host), port(port)
{

}

Audio_udp_live::~Audio_udp_live()
{

}

bool Audio_udp_live::set_pipeline()
{
    pipeline = gst_pipeline_new ("audio-streamer");
    source   = gst_element_factory_make ("pulsesrc",        "live-source");
    conv     = gst_element_factory_make ("audioconvert",    "convert");
    encoder  = gst_element_factory_make ("lamemp3enc",      "encoder");
    pay      = gst_element_factory_make ("rtpmpapay",       "pay");
    sink     = gst_element_factory_make ("udpsink",         "udpsink");

    if (!pipeline || !source ||!conv || !encoder || !pay || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        return false;
    }
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, conv, encoder, pay, sink, NULL);
    gst_element_link_many (source, conv, encoder, pay, sink, NULL);

    g_object_set(G_OBJECT(source), "device", "alsa_output.pci-0000_00_14.2.analog-stereo.monitor", NULL);
    g_object_set(G_OBJECT(sink), "host", host, "port", port, NULL);
    return true;
}

void Audio_udp_live::set_status(MediaStatus status)
{
    Media::set_status(status);
}

void Audio_udp_live::set_location(const char *)
{
}
