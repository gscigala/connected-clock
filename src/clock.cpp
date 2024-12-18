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

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>

#include "clock.h"

using namespace boost::posix_time;
namespace ph = boost::asio::placeholders;

Clock::Clock(Sound &sound, bool tick, deadline_timer &timer)
	: mSound(sound), mTick(tick), mTimer(timer)
{
	BOOST_LOG_TRIVIAL(trace) << "Hello from Clock constructor";
	BOOST_LOG_TRIVIAL(info) << "Tick = " << mTick;
	wait();
}

Clock::~Clock()
{
}

void Clock::wait(void)
{
	mTimer.expires_from_now(millisec(10));
	mTimer.async_wait(
		boost::bind(&Clock::timeout, this, ph::error));
}

void Clock::timeout(const boost::system::error_code &e)
{
	if (e)
		return;

	const ptime now = second_clock::local_time();
	const int hours = (int)now.time_of_day().hours();
	const int minutes = (int)now.time_of_day().minutes();
	const int seconds = (int)now.time_of_day().seconds();

	static int lastSeconds = -1;
	static int lastMinutes = -1;

	BOOST_LOG_TRIVIAL(trace) << "Timeout, it is " << hours << ":" << minutes
				 << ":" << seconds;

	if (seconds != lastSeconds) {
		BOOST_LOG_TRIVIAL(trace) << "New second : " << seconds;
		lastSeconds = seconds;
		tick();
	}

	if (minutes != lastMinutes) {
		lastMinutes = minutes;
		BOOST_LOG_TRIVIAL(trace) << "New minute : " << minutes;

		switch (minutes) {
		case 0:
			hour();
			break;

		case 5:
			fiveMinutes();
			break;

		case 15:
			oneQuarter();
			break;

		case 30:
			half();
			break;

		case 45:
			threeQuarter();
			break;

		default:
			break;
		}
	}

	/* Restart timer */
	wait();
}
