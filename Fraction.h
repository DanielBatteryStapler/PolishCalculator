#pragma once

#include <string>
#include <iostream>
#include <ctgmath>

class Fraction{
public:
	Fraction();
	Fraction(const std::string str);
	Fraction(const long long num);
	Fraction(const int num);
	Fraction(const long long num, const long long den);
	Fraction(const long double num);
	
	bool isFraction;
	
	void reduce();
	void toDecimal();
	long double getDecimal() const;
	long long getNumerator() const;
	long long getDenominator() const;
	
	std::string toString() const;
	
	Fraction pow(const Fraction& num);
	Fraction sqrt();
	Fraction sin();
	Fraction cos();
	Fraction tan();
	Fraction asin();
	Fraction acos();
	Fraction atan();
	Fraction log(const Fraction& num);
	
	Fraction operator+(const Fraction& num);
	Fraction operator-(const Fraction& num);
	Fraction operator*(const Fraction& num);
	Fraction operator/(const Fraction& num);
	Fraction operator%(const Fraction& num);

	bool operator==(const Fraction& fraction);
	bool operator!=(const Fraction& fraction);
	
	bool operator<(const Fraction& num) const;
	bool operator>(const Fraction& num);
	bool operator<=(const Fraction& num);
	bool operator>=(const Fraction& num);
	
	void operator=(const Fraction& num);
	void operator=(const long long& num);
	void operator=(const long double& num);
	
	std::ostream& operator<<(std::ostream& s);
	
private:
	long long numerator;
	long long denominator;
	long double decimal;
};

static long long findGcf(long long a, long long b){
	return a%b == 0 ? b : findGcf(b, a%b);
}
