#pragma once

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>


#ifndef _BXC_TIME
#define _BXC_TIME

namespace bxc
{
	class time
	{
	public:
		time();

	private:
		boost::posix_time::ptime ltime();
		auto hrtime();

	public:
		int year();
		int month();
		int day();
		int day_of_week();

		int hour();
		int minute();
		int second();
		int millisecond();
		int microsecond();
		int nanosecond();
		std::string prepend(int n);
	};
}
#endif // _BXC_TIME