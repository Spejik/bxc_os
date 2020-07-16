#pragma once
#include <chrono>
#include <boost/date_time.hpp>
using namespace std;
using namespace std::chrono;

class bxc_time
{
private:
	boost::posix_time::ptime ltime()  { return (boost::posix_time::second_clock::local_time()); };
	nanoseconds hrtime()              { return high_resolution_clock::now().time_since_epoch(); };


public:
	int year       () { return ltime().date().year(); }
	int month      () { return ltime().date().month(); }
	int day        () { return ltime().date().day(); }
	int day_of_week() { return ltime().date().day_of_week(); }

	int hour       () { return duration_cast<hours>       (hrtime()).count(); }
	int minute     () { return duration_cast<minutes>     (hrtime()).count(); }
	int second     () { return duration_cast<seconds>     (hrtime()).count(); }
	int millisecond() { return duration_cast<milliseconds>(hrtime()).count(); }
	int microsecond() { return duration_cast<microseconds>(hrtime()).count(); }
	int nanosecond () { return duration_cast<nanoseconds> (hrtime()).count(); }

	string prepend(int n)
	{
		if (n < 10) return "0" + to_string(n);
		else        return to_string(n);
	}
};
