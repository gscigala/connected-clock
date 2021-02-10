#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/trivial.hpp>

#include "westminster.h"

using namespace boost::posix_time;

Westminster::Westminster(Sound &sound, deadline_timer &timer, bool tick)
	: Clock(sound, timer, tick)
{
}

Westminster::~Westminster()
{
}

void Westminster::tick()
{
	BOOST_LOG_TRIVIAL(debug) << "Tick";
	BOOST_LOG_TRIVIAL(debug) << "No tick sound for westminster";
}

void Westminster::oneQuarter()
{
	BOOST_LOG_TRIVIAL(debug) << "One quarter";
	mSound.play("quarter.ogg");
}

void Westminster::half()
{
	BOOST_LOG_TRIVIAL(debug) << "Half hour";
	mSound.play("half.ogg");
}

void Westminster::threeQuarter()
{
	BOOST_LOG_TRIVIAL(debug) << "Three quarter";
	mSound.play("3quarter.ogg");
}

void Westminster::hour()
{
	const ptime now = second_clock::local_time();
	const int hours = (int)now.time_of_day().hours();

	int i;

	BOOST_LOG_TRIVIAL(debug) << "New hour : " << hours;

	mSound.play("hour.ogg");

	if (hours == 0) {
		i = 12;
	} else if (hours <= 12) {
		i = hours;
	} else {
		i = hours - 12;
	}

	BOOST_LOG_TRIVIAL(info) << "Play " << i << " strikes";

	while (i > 0) {
		strike();
		i--;
	}
}

void Westminster::fiveMinutes()
{
	hour();
}

void Westminster::strike()
{
	BOOST_LOG_TRIVIAL(debug) << "Strike";
	mSound.play("strike.ogg");
}
