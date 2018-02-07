//
//  clock.cpp
//  BigBen
//
//  Created by Guillaume Scigala on 03/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>
#include "clock.hpp"

using namespace boost::posix_time;

Clock::Clock(Sound &sound, deadline_timer &timer):
    mSound(sound),
    mTimer(timer)
{
    BOOST_LOG_TRIVIAL(trace) << "Hello from Clock constructor";
    wait();
}

void Clock::wait(void)
{
    mTimer.expires_from_now(millisec(500));
    mTimer.async_wait(boost::bind(&Clock::timeout, this, placeholders::error));
}

void Clock::timeout(const boost::system::error_code &e) {
    if (e)
        return;
    
    const ptime now = second_clock::local_time();
    const int hours = (int) now.time_of_day().hours();
    const int minutes = (int) now.time_of_day().minutes();
    const int seconds = (int) now.time_of_day().seconds();
    
    BOOST_LOG_TRIVIAL(trace) << "Timeout, it is "
        << hours << ":" << minutes << ":" << seconds;
    
    if(seconds == 0)
    {
        BOOST_LOG_TRIVIAL(trace) << "New minute : " << minutes;
        
        switch (minutes) {
            case 0:
            case 5:
                mSound.playHour(hours);
                break;
                
            case 15:
                mSound.playOneQuarter();
                break;
                
            case 30:
                mSound.playHalf();
                break;
                
            case 45:
                mSound.playThreeQuarter();
                break;
                
            default:
                break;
        }
    }
    
    //Restart timer
    wait();
}
