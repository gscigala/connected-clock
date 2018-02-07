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

#ifndef sound_hpp
#define sound_hpp

#include <gst/gst.h>
#include <glib.h>

/* Sound class
** Play audio output
*/
class Sound
{
public:
    /* Constructor */
    Sound(std::string path, int level);

    /* Play hour melody with strikes */
    void playHour(int hours);

    /* Play one quarter melody */
    void playOneQuarter(void);

    /* Play half hour melody */
    void playHalf(void);

    /* Play three quarter melody */
    void playThreeQuarter(void);
    
private:

    /* Data root location */
    const std::string mPath;

    /* GStreamer loop */
    GMainLoop *mLoop;

    /* GStreamer pipeline */
    GstElement *mPipeline;

    /* GStreamer source element */
    GstElement *mSrc;

    /* Play one strike */
    void playStrike(void);

    /* Play OGG file located with the path variable */
    void play(std::string path);
};

#endif /* sound_hpp */
