#include"server-local.hpp"

Local::Local()
{

}

Local::~Local()
{

}

void Local::set_pipeline_for_mp3()
{
    pipeline = gst_pipeline_new ("audio-player");
    source   = gst_element_factory_make ("filesrc",       "file-source");
    parse    = gst_element_factory_make ("mpegaudioparse","mp3-parse");
    decoder  = gst_element_factory_make ("mpg123audiodec","mp3-decoder");
    conv     = gst_element_factory_make ("audioconvert",  "converter");
    sink     = gst_element_factory_make ("autoaudiosink", "audio-output");

    if (!pipeline || !source ||!parse || !decoder || !conv || !sink) {
      g_printerr ("One element could not be created. Exiting.\n");
      exit(1);
    }

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
                      source, parse, decoder, conv, sink, NULL);

    gst_element_link (source, parse);
    gst_element_link_many (parse, decoder, conv, sink, NULL);

}

void Local::set_location(const char *location)
{
    g_object_set (G_OBJECT (source), "location", location , NULL);
    g_print ("File location: %s\n", location);
}

void Local::set_status(MediaStatus status)
{
    Media::set_status(status);
}
