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

#include <boost/asio.hpp>

#include "sound.h"

using namespace boost::asio;

/* Clock class
** Watch current time and control audio output
*/
class Clock {
    public:
	Clock(Sound &sound, bool tick, deadline_timer &timer);

	virtual ~Clock() = 0;

    protected:
	/* Sound object */
	Sound &mSound;

	/* Status of tick sound every second */
	bool mTick;

    private:
	/* Timer to handle new minutes */
	deadline_timer &mTimer;

	/* Start new timer */
	void wait(void);

	/* At timeout, check current time and send audio controls */
	void timeout(const boost::system::error_code &e);

	virtual void tick() = 0;
	virtual void oneQuarter() = 0;
	virtual void half() = 0;
	virtual void threeQuarter() = 0;
	virtual void hour() = 0;
	virtual void fiveMinutes() = 0;
	virtual void strike() = 0;
};

#endif /* CLOCK_H */
