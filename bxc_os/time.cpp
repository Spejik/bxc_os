#include "time.h"


bxc::time::time() {
	std::cout 
		<< "Constructing class bxc::time..." << std::endl
		<< "- Year:        " << year() << std::endl 
		<< "- Month:       " << month() << std::endl
		<< "- Day:         " << day() << std::endl
		<< "- Day Of Week: " << day_of_week() << std::endl
		<< "- Hour:        " << hour() << std::endl
		<< "- Minute:      " << minute() << std::endl
		<< "- Second:      " << second() << std::endl
		<< "- Millisecond: " << millisecond() << std::endl
		<< "- Microsecond: " << microsecond() << std::endl
		<< "- Nanosecond:  " << nanosecond() << std::endl;
}

boost::posix_time::ptime bxc::time::ltime () { return boost::posix_time::microsec_clock::local_time(); }

int64_t bxc::time::year       () { return ltime().date().year();        }
int64_t bxc::time::month      () { return ltime().date().month();       }
int64_t bxc::time::day        () { return ltime().date().day();         }
int64_t bxc::time::day_of_week() { return ltime().date().day_of_week(); }

int64_t bxc::time::hour       () { return ltime().time_of_day().hours(); }
int64_t bxc::time::minute     () { return ltime().time_of_day().minutes(); }
int64_t bxc::time::second     () { return ltime().time_of_day().seconds(); }
int64_t bxc::time::millisecond() { return ltime().time_of_day().total_milliseconds(); }
int64_t bxc::time::microsecond() { return ltime().time_of_day().total_microseconds(); }
int64_t bxc::time::nanosecond () { return ltime().time_of_day().total_nanoseconds(); }

std::string bxc::time::prepend(int64_t n)
{
	if (n < 10) return "0" + std::to_string(n);
	else        return std::to_string(n);
}