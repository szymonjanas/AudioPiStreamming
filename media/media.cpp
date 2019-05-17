#include "media.hpp"

static bool delete_flag = true;

Media::Media()
{
    int Argc = 1;
    char** Argv = new char* ();
    Argv[0] = "foo";
    gst_init (&Argc, &Argv);

    loop = g_main_loop_new (NULL, FALSE);
    delete_flag = true;
}

Media::~Media()
{
    if (delete_flag)
    {
        g_print ("Deleting pipeline\n");
        gst_object_unref (GST_OBJECT (pipeline));
        g_source_remove (bus_watch_id);
    }
    g_main_loop_unref (loop);
}

void Media::set_flag_for_new_pipeline()
{
    delete_flag = true;
}

void Media::delete_pipeline()
{
    delete_flag = false;
    g_print ("Deleting pipeline\n");
    gst_object_unref (GST_OBJECT (pipeline));
    g_source_remove (bus_watch_id);
}

void Media::on_pad_added (GstElement *element,
                   GstPad     *pad,
                   gpointer    data)
{
    GstPad *sinkpad;
    GstElement *decoder = (GstElement *) data;

    g_print ("Dynamic pad created, linking elements\n");

    sinkpad = gst_element_get_static_pad (decoder, "sink");

    gst_pad_link (pad, sinkpad);

    gst_object_unref (sinkpad);
}

gboolean Media::bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
      GMainLoop *loop = (GMainLoop *) data;

      switch (GST_MESSAGE_TYPE (msg)) {

        case GST_MESSAGE_EOS:
          g_print ("End of stream\n");
          g_main_loop_quit (loop);
          break;

        case GST_MESSAGE_ERROR: {
          gchar  *debug;
          GError *error;

          gst_message_parse_error (msg, &error, &debug);
          g_free (debug);

          g_printerr ("Error: %s\n", error->message);
          g_error_free (error);

          g_main_loop_quit (loop);
          break;
        }
        default:
          break;
      }

      return TRUE;
}

void Media::set_status(MediaStatus status)
{
    switch(status)
    {
    case MediaStatus::PLAY:
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
        set_flag_for_new_pipeline();
        g_print ("Running...\n");
        break;
    case MediaStatus::PAUSE:
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
        g_print ("Paused,\n");
        break;
    case MediaStatus::STOP:
        g_print ("Returned, stopping playback\n");
        gst_element_set_state (pipeline, GST_STATE_NULL);
        delete_pipeline();
        break;
    }
}
