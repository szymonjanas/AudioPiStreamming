#pragma once

#include<gst/gst.h>

enum class MediaStatus {PLAY, PAUSE, STOP};

class Media
{

public:
    GstBus *bus;
    guint bus_watch_id;
    GMainLoop *loop;
    GstElement *pipeline, *decoder, *pay, *encoder , *source, *parse, *conv, *sink, *bin;

    static gboolean bus_call(   GstBus* bus, GstMessage* msg, gpointer data);
    static void on_pad_added (  GstElement *element,
                                GstPad     *pad,
                                gpointer    data);
    void delete_pipeline();
    void set_flag_for_new_pipeline();
    Media();
    ~Media();
    void set_status(MediaStatus status);
};
