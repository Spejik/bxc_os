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
		<< "- Nanosecond:  " << nanosecond() << std::endl
		;
}

boost::posix_time::ptime bxc::time::ltime () { return boost::posix_time::second_clock::local_time(); }
auto bxc::time::hrtime() { return std::chrono::high_resolution_clock::now().time_since_epoch(); }

int bxc::time::year       () { return ltime().date().year();        }
int bxc::time::month      () { return ltime().date().month();       }
int bxc::time::day        () { return ltime().date().day();         }
int bxc::time::day_of_week() { return ltime().date().day_of_week(); }

int bxc::time::hour       () { return ltime().time_of_day().hours(); }
int bxc::time::minute     () { return ltime().time_of_day().hours(); }
int bxc::time::second     () { return ltime().time_of_day().seconds(); }
int bxc::time::millisecond() { return ltime().time_of_day().total_milliseconds(); }
int bxc::time::microsecond() { return ltime().time_of_day().hours(); }
int bxc::time::nanosecond () { return std::chrono::duration_cast<std::chrono::nanoseconds> (hrtime()).count(); }

std::string bxc::time::prepend(int n)
{
	if (n < 10) return "0" + std::to_string(n);
	else        return std::to_string(n);
}