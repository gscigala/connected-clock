//
//  clock.h
//  BigBen
//
//  Created by Guillaume Scigala on 03/02/2018.
//  Copyright © 2018 Silence. All rights reserved.
//

#ifndef clock_h
#define clock_h

#include "sound.hpp"

using namespace boost::asio;

class Clock {
public:
    Clock(Sound &sound, deadline_timer &timer);
    
private:
    
    Sound &mSound;
    deadline_timer &mTimer;
    
    void wait(void);
    void timeout(const boost::system::error_code &e);
};


#endif /* clock_h */

