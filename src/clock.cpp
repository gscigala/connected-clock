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

Clock::Clock(deadline_timer &timer): mTimer(timer), mPreviousSeconds(0)
{
    BOOST_LOG_TRIVIAL(debug) << "Hello from Clock constructor";
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
    
    //Restart timer
    wait();
    
    const ptime now = second_clock::local_time();
    const int hours = (int) now.time_of_day().hours();
    const int minutes = (int) now.time_of_day().minutes();
    const int seconds = (int) now.time_of_day().seconds();
    
    BOOST_LOG_TRIVIAL(debug) << "Timeout, it is "
        << hours << ":" << minutes << ":" << seconds;
    
    if((seconds == 0) && (mPreviousSeconds != seconds))
    {
        BOOST_LOG_TRIVIAL(debug) << "New minute : " << minutes;
        
        switch (minutes) {
            case 0:
            case 5:
                newHour(hours);
                break;
                
            case 15:
                oneQuarter();
                break;
                
            case 30:
                oneHalf();
                break;
                
            case 45:
                threeQuarter();
                break;
                
            default:
                break;
        }
    }
    
    mPreviousSeconds = seconds;
}

void Clock::newHour(const int hours)
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
        hourBell();
        tick--;
    }
}

void Clock::oneQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "One quarter";
}

void Clock::oneHalf(void)
{
    BOOST_LOG_TRIVIAL(info) << "One half";
}

void Clock::threeQuarter(void)
{
    BOOST_LOG_TRIVIAL(info) << "Three quarter";
}

void Clock::hourBell(void)
{
    BOOST_LOG_TRIVIAL(info) << "Hour bell";
}
