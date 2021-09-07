#pragma once

#include <string>
#include <iostream>
#include <set>
#include <functional>

#include "Fraction.h"

class UniNum{
public:
	UniNum();
	UniNum(Fraction num);
	
	std::string toString() const;
	
	UniNum getDecimal();
	UniNum sqrt();
	UniNum sin();
	UniNum cos();
	UniNum tan();
	UniNum asin();
	UniNum acos();
	UniNum atan();
	
	void operator=(const UniNum& num);
	
	UniNum operator+(const UniNum& num);
	UniNum operator-(const UniNum& num);
	UniNum operator*(const UniNum& num);
	UniNum operator/(const UniNum& num);
	UniNum operator%(const UniNum& num);
	UniNum pow(const UniNum& num);
	UniNum log(const UniNum& num);
	
	UniNum combine(const UniNum& num);
	
	std::ostream& operator<<(std::ostream& s);
	
private:
	void forEach(std::function<void(Fraction)> callback) const;
	std::set<Fraction> numSet;
};

