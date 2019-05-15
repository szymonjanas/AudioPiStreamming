#include"base-audio-processing.hpp"

void Reciver_mp3::set_status(MediaStatus status)
{
    Media::set_status(status);
}

void Reciver_mp3::set_reciver_mp3(gchar* host, gint port)
{
    pipeline = gst_pipeline_new ("audio-streamer");
    source   = gst_element_factory_make ("udpsrc",       "udp-source");
   // queue    = gst_element_factory_make ("queue","queue");
    depay    = gst_element_factory_make ("rtpmpadepay",  "depay");
    parse    = gst_element_factory_make ("mpegaudioparse", "parse");
    decoder  = gst_element_factory_make ("mpg123audiodec", "decoder");
    convert  = gst_element_factory_make ("audioconvert", "convert");
    resample = gst_element_factory_make ("audioresample", "resample");
    sink     = gst_element_factory_make ("autoaudiosink", "sink");

    if (!pipeline || !source //|| !queue
            || !depay
      || !parse || !convert || !decoder || !resample || !sink) {
    g_printerr ("One element could not be created. Exiting.\n");
    exit(1);
    }

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (pipeline),
    source, //queue,
                      depay,parse, decoder, convert, resample, sink, NULL);
    gst_element_link_many (source, //queue,
                           depay, parse, decoder, convert, resample, sink, NULL);


    GstCaps* caps;
    caps = gst_caps_new_simple("application/x-rtp", NULL);
    g_object_set(G_OBJECT(source), "caps", caps, NULL);
    gst_caps_unref(caps);

    g_object_set(G_OBJECT(source), "address", host, "port", port, NULL);
}
