#pragma once

#include <chrono>
#include <boost/date_time.hpp>
#include <boost/chrono.hpp>


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

	public:
		int64_t year();
		int64_t month();
		int64_t day();
		int64_t day_of_week();

		int64_t hour();
		int64_t minute();
		int64_t second();
		int64_t millisecond();
		int64_t microsecond();
		int64_t nanosecond();
		std::string prepend(int64_t n);
	};
}
#endif // _BXC_TIME