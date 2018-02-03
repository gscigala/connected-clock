//
//  clock.h
//  BigBen
//
//  Created by Guillaume Scigala on 03/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#ifndef clock_h
#define clock_h

class Clock {
public:
    Clock(boost::asio::deadline_timer &timer);
    
private:
    boost::asio::deadline_timer &mTimer;
    int mPreviousSeconds;
    
    void wait(void);
    void timeout(const boost::system::error_code &e);
    
    void newHour(const int hours);
    void oneQuarter(void);
    void oneHalf(void);
    void threeQuarter(void);
    
    void hourBell(void);
};


#endif /* clock_h */

