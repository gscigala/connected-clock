//
//  sound.cpp
//  BigBen
//
//  Created by Guillaume Scigala on 04/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#include <unistd.h>
#include <boost/log/trivial.hpp>
#include "sound.hpp"

Sound::Sound(std::string path, int volume): mPath(path), mVolume(volume/100.0)
{
    BOOST_LOG_TRIVIAL(debug) << "Hello from Sound constructor,"
    << "path = " << mPath
    << ", level = " << mVolume;
}

const void Sound::playHour(int hours)
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

const void Sound::playOneQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "One quarter";
    play(mPath + "/quarter.ogg");
}

const void Sound::playHalf(void)
{
    BOOST_LOG_TRIVIAL(info) << "Half hour";
        play(mPath + "/half.pgg");
}

const void Sound::playThreeQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "Three quarter";
    play(mPath + "/3quarter.ogg");
}

const void Sound::playStrike(void)
{
    BOOST_LOG_TRIVIAL(info) << "Strike";
    play(mPath + "/strike.ogg");
}

const void Sound::play(std::string path)
{
    std::string cmd = "gst-launch-1.0 filesrc location=" + path + " ! oggdemux ! vorbisdec ! audioconvert ! volume volume=" + std::to_string(mVolume) + " ! audioresample ! autoaudiosink";
    
    system(cmd.c_str());
}
