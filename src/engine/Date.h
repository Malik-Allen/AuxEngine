// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_DATE_H
#define AUX_DATE_H

#include <string>

namespace AuxEngine
{
	class Date
	{
	public:
		explicit Date(int day, int month, int year);
		Date(const Date& other);
		Date(Date&& other) noexcept;
		Date& operator=(const Date& other);
		Date& operator=(Date&& other) noexcept;
		bool operator==(const Date& other) const;
		bool operator>(const Date& other) const;
		bool operator>=(const Date& other) const;
		bool operator<(const Date& other) const;
		bool operator<=(const Date& other) const;

		int day() const;
		int month() const;
		int year() const;

		// Formated YYYY-M
		std::string toStringYearMonth() const;

		int daysTo(const Date& endDate) const;

		static Date CurrentDate();

	private:
		int day_ = 1;
		int month_ = 1;
		int year_ = 1945;

		bool isLeapYear(int year) const;
		bool isValidDate(int day, int month, int year) const;

		static const int DaysInTheMonth_[12];
	};
}

#endif