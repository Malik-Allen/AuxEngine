// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_MONEY_H
#define AUX_MONEY_H

#include <string>

namespace AuxEngine
{
	struct Currency
	{
		std::string code_;
		int numericCode_ = 0;
		std::string name_;
		std::string symbol_;

		bool operator==(const Currency& other) const;
	};

	class Money
	{
		// unscaled value of money (cents)
		int64_t value_;
		// currency codes for this monetery value
		Currency currency_;

	public:
		explicit Money(const int64_t cents, const Currency& currency);
		Money(const Money& other);
		Money(Money&& other) noexcept;
		Money& operator=(const Money& other);
		Money& operator=(Money&& other) noexcept;
		bool operator==(const Money& other) const;
		bool operator>(const Money& other) const;
		bool operator>=(const Money& other) const;
		bool operator<(const Money& other) const;
		bool operator<=(const Money& other) const;

		Money operator-() const;
		Money operator+(const Money& other) const;
		Money operator+=(const Money& other);
		Money operator-(const Money& other) const;
		Money operator-=(const Money& other);
		Money operator*(const int64_t scalar) const;
		static friend Money operator*(const int64_t scalar, const Money& m);
		Money operator*=(const int64_t scalar);
		Money operator/(const int64_t scalar) const;
		Money operator/=(const int64_t scalar);

		inline bool isZero() const { return value_ == 0; }
		inline bool isNegative() const { return value_ < 0; }

		double toDouble() const;
		const Currency& currency() const;

		std::string toString() const;
		std::string toCommaSeparatedString() const;
	};
}

#endif