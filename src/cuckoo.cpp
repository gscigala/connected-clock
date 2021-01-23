#include <chrono>
#include <thread>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>

#include "cuckoo.h"

using namespace boost::posix_time;

Cuckoo::Cuckoo(Sound &sound, bool tick, deadline_timer &timer)
  : Clock(sound, tick, timer)
{
}

Cuckoo::~Cuckoo()
{
}

void Cuckoo::tick()
{
	BOOST_LOG_TRIVIAL(debug) << "Tick";

	if (mTick) {
		mSound.play("tick.ogg");
	} else {
		BOOST_LOG_TRIVIAL(debug) << "Tick sound disabled";
	}
}

void Cuckoo::oneQuarter()
{
}

void Cuckoo::half()
{
	BOOST_LOG_TRIVIAL(debug) << "Half hour";
	mSound.play("half.ogg");

	const ptime now = second_clock::local_time();
	const int hours = (int)now.time_of_day().hours();

	std::string filename;
	int i;

	BOOST_LOG_TRIVIAL(debug) << "Half hour : " << hours << " and an half";

	if (hours == 0) {
		i = 12;
	} else if (hours <= 12) {
		i = hours;
	} else {
		i = hours - 12;
	}

	filename.append("half-");
	filename.append(std::to_string(i));
	filename.append(".ogg");

	mSound.play(filename);
}

void Cuckoo::threeQuarter()
{
}

void Cuckoo::hour()
{
	const ptime now = second_clock::local_time();
	const int hours = (int)now.time_of_day().hours();

	std::string filename;
	int i;

	BOOST_LOG_TRIVIAL(debug) << "New hour : " << hours;

	if (hours == 0) {
		i = 12;
	} else if (hours <= 12) {
		i = hours;
	} else {
		i = hours - 12;
	}

	filename.append("hour-");
	filename.append(std::to_string(i));
	filename.append(".ogg");

	/* Play */
	BOOST_LOG_TRIVIAL(info) << "Play " << i << " cuckoo";
	while (i > 0) {
		strike();
		i--;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	mSound.play(filename);
}

void Cuckoo::fiveMinutes()
{
}

void Cuckoo::strike()
{
	BOOST_LOG_TRIVIAL(debug) << "Cuckoo";
	mSound.play("cuckoo.ogg");
}
