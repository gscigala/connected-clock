//
//  sound.cpp
//  BigBen
//
//  Created by Guillaume Scigala on 04/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#include <boost/log/trivial.hpp>
#include "sound.hpp"

Sound::Sound(std::string type, int level): mType(type), mLevel(level)
{
    BOOST_LOG_TRIVIAL(debug) << "Hello from Sound constructor";
}

void Sound::playHour(int hours)
{
    BOOST_LOG_TRIVIAL(info) << "New hour : " << hours;
    
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
    
    
    while(tick > 0)
    {
        playStrike();
        tick--;
    }
}

void Sound::playOneQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "One quarter";
}

void Sound::playHalf(void)
{
    BOOST_LOG_TRIVIAL(info) << "Half hour";
}

void Sound::playThreeQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "Three quarter";
}

void Sound::playStrike(void)
{
    BOOST_LOG_TRIVIAL(info) << "Strike";
}

void Sound::play(std::string path)
{

}
