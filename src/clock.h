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

#ifndef CLOCK_H
#define CLOCK_H

#include "sound.h"

using namespace boost::asio;

/* Clock class
** Watch current time and control audio output
*/
class Clock {
public:
    /* Constructor */
    Clock(Sound &sound, deadline_timer &timer);
    
private:

    /* Sound object */
    Sound &mSound;

    /* Timer to handle new minutes */
    deadline_timer &mTimer;

    /* Start new timer */
    void wait(void);

    /* Check current time and send audio controls */
    void timeout(const boost::system::error_code &e);
};


#endif /* CLOCK_H */

