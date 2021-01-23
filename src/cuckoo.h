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

#ifndef CUCKOO_H
#define CUCKOO_H

#include "clock.h"

/* Cuckoo class
** Watch current time with cuckoo type
*/
class Cuckoo : public Clock {
    public:
	Cuckoo(Sound &sound, bool tick, deadline_timer &timer);
	~Cuckoo();

    private:
	void tick();
	void oneQuarter();
	void half();
	void threeQuarter();
	void hour();
	void fiveMinutes();
	void strike();
};

#endif /* CUCKOO_H */
