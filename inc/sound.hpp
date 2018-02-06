//
//  sound.hpp
//  BigBen
//
//  Created by Guillaume Scigala on 04/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#ifndef sound_hpp
#define sound_hpp

#include <gst/gst.h>
#include <glib.h>

class Sound
{
public:
    Sound(std::string path, int level);
    
    void playHour(int hours);
    void playOneQuarter(void);
    void playHalf(void);
    void playThreeQuarter(void);
    
private:
    
    const std::string mPath;

    GMainLoop *mLoop;
    GstElement *mPipeline, *mSrc;

    void playStrike(void);
    void play(std::string path);
};

#endif /* sound_hpp */
