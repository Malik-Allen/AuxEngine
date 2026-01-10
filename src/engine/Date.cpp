// MIT License, Copyright (c) 2025 Malik Allen

#include "engine/Date.h"
#include "engine/DebugLog.h"

#include <chrono>

namespace AuxEngine
{
	const int Date::DaysInTheMonth_[] = { 31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31 };

	Date::Date(int day, int month, int year)
	{
		day_ = day;
		month_ = month;
		year_ = year;
	}

	Date::Date(const Date& other)
	{
		day_ = other.day_;
		month_ = other.month_;
		year_ = other.year_;
	}

	Date::Date(Date&& other) noexcept
	{
		day_ = other.day_;
		month_ = other.month_;
		year_ = other.year_;

		other.day_ = other.month_ = other.year_ = 0;
	}

	Date& Date::operator=(const Date& other)
	{
		day_ = other.day_;
		month_ = other.month_;
		year_ = other.year_;
		return *this;
	}

	Date& Date::operator=(Date&& other) noexcept
	{
		if (this != &other)
		{
			day_ = other.day_;
			month_ = other.month_;
			year_ = other.year_;

			other.day_ = other.month_ = other.year_ = 0;
		}
		return *this;
	}

	bool Date::operator==(const Date& other) const
	{
		return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
	}

	bool Date::operator>(const Date& other) const
	{
		if (year_ > other.year_)
		{
			return true;
		}
		else if (year_ == other.year_)
		{
			if (month_ > other.month_)
			{
				return true;
			}
			else if (month_ == other.month_)
			{
				return day_ > other.day_;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>=(const Date& other) const
	{
		return *this > other || *this == other;
	}

	bool Date::operator<(const Date& other) const
	{
		if (year_ < other.year_)
		{
			return true;
		}
		else if (year_ == other.year_)
		{
			if (month_ < other.month_)
			{
				return true;
			}
			else if (month_ == other.month_)
			{
				return day_ < other.day_;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<=(const Date& other) const
	{
		return *this < other || *this == other;
	}

	int Date::day() const
	{
		return day_;
	}

	int Date::month() const
	{
		return month_;
	}

	int Date::year() const
	{
		return year_;
	}

	std::string Date::to_string() const
	{
		char buffer[11];
		std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year_, month_, day_);
		return std::string(buffer);
	}

	Date Date::from_string(const std::string& date_string)
	{
		int y = 0, m = 0, d = 0;
		if (sscanf(date_string.c_str(), "%4d-%2d-%2d", &y, &m, &d) == 3)
		{
			return Date(d, m, y);
		}
		// If parsing fails, return a default invalid date
		return Date(1, 1, 1);
	}


	std::string Date::toStringYearMonth() const
	{
		return std::to_string(year_) + "-" + std::to_string(month_);
	}

	int Date::daysTo(const Date& date) const
	{
		std::chrono::sys_days startDate = std::chrono::year_month_day{ std::chrono::year{year()}, std::chrono::month{static_cast<unsigned int>(month())}, std::chrono::day{static_cast<unsigned int>(day())} };
		std::chrono::sys_days endDate = std::chrono::year_month_day{ std::chrono::year{date.year()}, std::chrono::month{static_cast<unsigned int>(date.month())}, std::chrono::day{static_cast<unsigned int>(date.day())} };
		return std::chrono::duration_cast<std::chrono::days>(endDate - startDate).count();
	}

	Date Date::CurrentDate()
	{
		// Get current time as system_clock::time_point
		auto now = std::chrono::system_clock::now();

		// Convert to a day-precision time_point
		auto dp = std::chrono::floor<std::chrono::days>(now);

		// Convert to a civil calendar date
		std::chrono::year_month_day ymd = std::chrono::year_month_day{ dp };

		std::chrono::year currentYear = ymd.year();
		std::chrono::month currentMonth = ymd.month();
		std::chrono::day currentDay = ymd.day();

		return Date(static_cast<unsigned int>(currentDay), static_cast<unsigned int>(currentMonth), static_cast<int>(currentYear));
	}

	bool Date::isLeapYear(int year) const
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool Date::isValidDate(int day, int month, int year) const
	{
		// Basic range checks
		if (year < 1 || month < 1 || month > 12 || day < 1)
		{
			return false;
		}

		// Adjust for leap year
		if (month == 2 && isLeapYear(year))
		{
			return day <= 29;
		}

		return day <= Date::DaysInTheMonth_[month - 1];
	}
}