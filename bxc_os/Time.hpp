#pragma once

#include <fmt/format.h>
#include <fmt/compile.h>
#include <spdlog/spdlog.h>
#include <boost/date_time.hpp>
#include <boost/chrono.hpp>

#include <chrono>


namespace Time
{
	inline boost::posix_time::ptime ltime() { return boost::posix_time::microsec_clock::local_time(); }
	
	inline int64_t year() { return ltime().date().year(); }
	inline int64_t month() { return ltime().date().month(); }
	inline int64_t day() { return ltime().date().day(); }
	inline int64_t day_of_week() { return ltime().date().day_of_week(); }
	 
	inline int64_t hour() { return ltime().time_of_day().hours(); }
	inline int64_t minute() { return ltime().time_of_day().minutes(); }
	inline int64_t second() { return ltime().time_of_day().seconds(); }
	inline int64_t millisecond() { return ltime().time_of_day().total_milliseconds(); }
	inline int64_t microsecond() { return ltime().time_of_day().total_microseconds(); }
	inline int64_t nanosecond() { return ltime().time_of_day().total_nanoseconds(); }
	
	inline std::string prepend(int64_t n)
	{
		return fmt::format(FMT_COMPILE("{:02}"), n);
	}
};
