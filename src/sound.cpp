/******************************************************************************
 **  Copyright (c) 2018, Connected Clock. All Rights Reserved.
 **
 **  This file is part of Connected Clock.
 **
 **  Connected Clock is free software; you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation; either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Connected Clock is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Foobar; if not, write to the Free Software
 **  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 **
 ******************************************************************************/

#include <boost/log/trivial.hpp>

#include "sound.h"

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
    GMainLoop *loop = (GMainLoop *) data;

    switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
        BOOST_LOG_TRIVIAL(debug) << "End of stream";
        g_main_loop_quit (loop);
        break;

    case GST_MESSAGE_ERROR: {
        gchar  *debug;
        GError *error;

        gst_message_parse_error (msg, &error, &debug);
        g_free (debug);

        BOOST_LOG_TRIVIAL(error) << "gstreamer error: " << error->message;
        g_error_free (error);

        g_main_loop_quit (loop);
        break;
    }
    default:
        break;
    }

    return TRUE;
}

static void on_pad_added (GstElement *element, GstPad *pad, gpointer data)
{
    GstPad *sinkpad;
    GstElement *decoder = (GstElement *) data;

    /* We can now link this pad with the vorbis-decoder sink pad */
    BOOST_LOG_TRIVIAL(debug) << "Dynamic pad created, linking demuxer/decoder";

    sinkpad = gst_element_get_static_pad (decoder, "sink");

    gst_pad_link (pad, sinkpad);

    gst_object_unref (sinkpad);
}


Sound::Sound(std::string path, int volume): mPath(path)
{
    BOOST_LOG_TRIVIAL(trace) << "Hello from Sound constructor,"
                             << "path = " << mPath
                             << ", volume = " << volume << "%";

    GstElement *demux, *dec, *conv, *vol, *res, *sink;
    GstBus *bus;

    // init gstreamer
    gst_init(NULL, NULL);
    mLoop = g_main_loop_new(NULL, FALSE);
    BOOST_LOG_TRIVIAL(debug) << "Gstreamer init done";


    // Create gstreamer elements
    mPipeline = gst_pipeline_new("pipeline");
    mSrc = gst_element_factory_make("filesrc", "source");
    demux = gst_element_factory_make("oggdemux", "demux");
    dec = gst_element_factory_make("vorbisdec", "decoder");
    conv = gst_element_factory_make("audioconvert", "conv");
    vol = gst_element_factory_make("volume", "volume");
    res = gst_element_factory_make("audioresample", "resample");
    sink = gst_element_factory_make("alsasink", "sink");

    // we set the volume value to the volume element
    g_object_set(G_OBJECT(vol), "volume", volume/100.0, NULL);

    // we add a message handler for EOS
    bus = gst_pipeline_get_bus (GST_PIPELINE (mPipeline));
    gst_bus_add_watch (bus, bus_call, mLoop);
    gst_object_unref (bus);

    // we add all elements into the pipeline
    gst_bin_add_many (GST_BIN (mPipeline), mSrc, demux, dec, conv, vol, res, sink, NULL);

    // we link the elements together
    // file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> volume -> resample-> alsa-output
    gst_element_link(mSrc, demux);
    gst_element_link_many(dec, conv, vol, res, sink, NULL);
    g_signal_connect(demux, "pad-added", G_CALLBACK(on_pad_added), dec);
}

void Sound::playHour(int hours)
{
    BOOST_LOG_TRIVIAL(info) << "New hour : " << hours;
    
    play(mPath + "/hour.ogg");
    
    int tick;
    
    if(hours == 0)
    {
        tick = 12;
    }
    else if(hours <= 12)
    {
        tick = hours;
    }
    else
    {
        tick = hours - 12;
    }
    
    BOOST_LOG_TRIVIAL(info) << "Play " << tick << " strikes";
    
    while(tick > 0)
    {
        playStrike();
        tick--;
    }
}

void Sound::playOneQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "One quarter";
    play(mPath + "/quarter.ogg");
}

void Sound::playHalf(void)
{
    BOOST_LOG_TRIVIAL(info) << "Half hour";
    play(mPath + "/half.ogg");
}

void Sound::playThreeQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "Three quarter";
    play(mPath + "/3quarter.ogg");
}

void Sound::playStrike(void)
{
    BOOST_LOG_TRIVIAL(info) << "Strike";
    play(mPath + "/strike.ogg");
}

void Sound::play(std::string path)
{
    BOOST_LOG_TRIVIAL(debug) << "Play : " << path;

    // Set path
    g_object_set(G_OBJECT(mSrc), "location", path.c_str(), NULL);

    // play
    gst_element_set_state (mPipeline, GST_STATE_PLAYING);
    g_main_loop_run (mLoop);
  
    gst_element_set_state (mPipeline, GST_STATE_NULL);
}
