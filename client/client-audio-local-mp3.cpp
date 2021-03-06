#include"client-audio-local-mp3.hpp"

Audio_local::Audio_local()
{

}

Audio_local::~Audio_local()
{}

bool Audio_local::set_pipeline()
{
    pipeline = gst_pipeline_new ("audio-player");
    source   = gst_element_factory_make ("filesrc",       "file-source");
    parse    = gst_element_factory_make ("mpegaudioparse","mp3-parse");
    decoder  = gst_element_factory_make ("mpg123audiodec","mp3-decoder");
    conv     = gst_element_factory_make ("audioconvert",  "converter");
    sink     = gst_element_factory_make ("autoaudiosink", "audio-sink");

    if (!pipeline || !source ||!parse || !decoder || !conv || !sink) {
      g_printerr ("One element could not be created. Exiting.\n");
      return false;
    }

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, parse, decoder, conv, sink, NULL);
    gst_element_link_many (source, parse, decoder, conv, sink, NULL);
    return true;
}

void Audio_local::set_location(const char *location)
{
    g_object_set (G_OBJECT (source), "location", location , NULL);
    g_print ("File location: %s\n", location);
}

void Audio_local::set_status(MediaStatus status)
{
    Media::set_status(status);
}
