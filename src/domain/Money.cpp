// MIT License, Copyright (c) 2025 Malik Allen

#include "domain/Money.h"

#include <format>
#include <stdexcept>

namespace AuxEngine
{
	static constexpr int64_t SCALE{ 100 }; // 100 Cents
	static constexpr int64_t DECIMAL_PLACES{ 2 };

	bool Currency::operator==(const Currency& other) const
	{
		return numericCode_ == other.numericCode_;
	}

	Money::Money(const int64_t cents, const Currency& currency)
		: value_(cents)
		, currency_(currency)
	{
	}

	Money::Money(const Money& other)
		: value_(other.value_)
		, currency_(other.currency_)
	{
	}

	Money::Money(Money&& other) noexcept
	{
		value_ = other.value_;
		currency_ = other.currency_;

		other.value_ = 0;
		other.currency_ = Currency();
	}

	Money& Money::operator=(const Money& other)
	{
		value_ = other.value_;
		currency_ = other.currency_;
		return *this;
	}

	Money& Money::operator=(Money&& other) noexcept
	{
		if (this != &other)
		{
			value_ = other.value_;
			currency_ = other.currency_;

			other.value_ = 0;
			other.currency_ = Currency();
		}
		return *this;
	}

	bool Money::operator==(const Money& other) const
	{
		return value_ == other.value_ && currency_ == other.currency_;
	}

	bool Money::operator>(const Money& other) const
	{
		return value_ > other.value_;
	}

	bool Money::operator>=(const Money& other) const
	{
		return value_ >= other.value_;
	}

	bool Money::operator<(const Money& other) const
	{
		return value_ < other.value_;
	}

	bool Money::operator<=(const Money& other) const
	{
		return value_ <= other.value_;
	}

	Money Money::operator-() const
	{
		return Money(-value_, currency_);
	}

	Money Money::operator+(const Money& other) const
	{
		return Money(value_ + other.value_, currency_);
	}

	Money Money::operator+=(const Money& other)
	{
		value_ += other.value_;
		return *this;
	}

	Money Money::operator-(const Money& other) const
	{
		return Money(value_ - other.value_, currency_);
	}

	Money Money::operator-=(const Money& other)
	{
		value_ -= other.value_;
		return *this;
	}

	Money Money::operator*(const int64_t scalar) const
	{
		return Money(value_ * scalar, currency_);
	}

	Money operator*(const int64_t scalar, const Money& m)
	{
		return m * scalar;
	}

	Money Money::operator*=(const int64_t scalar)
	{
		value_ *= scalar;
		return *this;
	}

	Money Money::operator/(const int64_t scalar) const
	{
		if (scalar == 0)
		{
			throw std::runtime_error("Cannot divide by zero!");
		}
		return Money(value_ / scalar, currency_);
	}

	Money Money::operator/=(const int64_t scalar)
	{
		if (scalar == 0)
		{
			throw std::runtime_error("Cannot divide by zero!");
		}
		value_ /= scalar;
		return *this;
	}

	double Money::toDouble() const
	{
		return static_cast<double>(value_) / static_cast<double>(SCALE);
	}

	const Currency& Money::currency() const
	{
		return currency_;
	}

	std::string Money::toString(bool bWithSymbol) const
	{
		return std::format("{}{:.{}f}", bWithSymbol ? currency_.symbol_ : "", toDouble(), DECIMAL_PLACES);
	}

	std::string Money::toCommaSeparatedString(bool bWithSymbol) const
	{
		std::string dollarString = toString(false);
		
		std::string centString;
		// Remove and cache the last three characters (cents and decimal)
		for (int64_t i = 0; i < (DECIMAL_PLACES + 1); ++i)
		{
			centString.push_back(dollarString[dollarString.size() - 1]);
			dollarString.pop_back();
		}

		std::string output;
		int64_t count = 0;
		// Starting from the back every 3 character add a comma
		for (int64_t i = dollarString.size() - 1; i >= 0; --i)
		{
			++count;
			output.push_back(dollarString[i]);
			if (count == 3) 
			{
				output.push_back(',');
				count = 0;
			}
		}

		// Reverse the output string and remove extra comma.
		reverse(output.begin(), output.end());
		if (output.size() % 4 == 0) 
		{
			output.erase(output.begin());
		}

		// Re-add the cents and decimal characters
		for (int64_t i = centString.size() - 1; i >= 0; --i)
		{
			output.push_back(centString[i]);
		}

		if (bWithSymbol)
		{
			return std::format("{}{}", currency_.symbol_, output);
		}
		else
		{
			return output;
		}
	}
}