#include "Fraction.h"

Fraction::Fraction():
numerator(0),
denominator(1),
isFraction(true){
}

Fraction::Fraction(const std::string str):
numerator(0),
denominator(1),
isFraction(true){
	std::string integer;
	std::size_t pos = str.find('.');
	if(pos == std::string::npos){
		*this = Fraction(std::stoll(str));
	}
	else{
		if(pos != 0){
			integer = str.substr(0, pos);
		}
		else{
			integer = '0';//kinda janky to set a string to zero, and then convert it to a number, but it gets the point across
			//if there is no number before the decimal point, the integer part is 0
		}
		std::string rest = str.substr(pos + 1, (str.size() - pos) - 1);
		
		*this = Fraction(std::stoll(integer)) + Fraction(std::stoll(rest), std::pow(10, rest.size()));
	}
}

Fraction::Fraction(const long long num):
numerator(num),
denominator(1),
isFraction(true){
}

Fraction::Fraction(const int num):
numerator(num),
denominator(1),
isFraction(true){
}

Fraction::Fraction(const long long num, const long long den):
numerator(num),
denominator(den),
isFraction(true){
	reduce();
}

Fraction::Fraction(const long double num):
decimal(num),
isFraction(false){
}

void Fraction::reduce(){
	if(isFraction){
		if(denominator == 0){
			numerator = 0;
			return;
		}
		
		if (numerator == 0){
			denominator = 1;
		}
		else{
			long long gcf = findGcf(numerator, denominator);
			numerator /= gcf;
			denominator /= gcf;
		}

		if (denominator < 0){
			denominator = -denominator;
			numerator = -numerator;
		}
	}
	else{
		if(!std::isfinite(decimal)){
			isFraction = true;
			numerator = 0;
			denominator = 0;
		}
	}
}

void Fraction::toDecimal(){
	if(isFraction){
		decimal = ((long double)numerator)/((long double)denominator);
		isFraction = false;
	}
}

long double Fraction::getDecimal() const{
	if(isFraction){
		return ((long double)numerator)/((long double)denominator);
	}
	else{
		return decimal;
	}
}

long long Fraction::getNumerator() const{
	if(!isFraction){
		throw std::invalid_argument("Cannot get numerator of a decimal");
	}
	return numerator;
}

long long Fraction::getDenominator() const{
	if(!isFraction){
		throw std::invalid_argument("Cannot get denominator of a decimal");
	}
	return denominator;
}

std::string Fraction::toString() const{
	
	static auto format = [](std::string numWithCommas){
		int insertPosition = numWithCommas.length() - 3;
		while (insertPosition > 0) {
			numWithCommas.insert(insertPosition, ",");
			insertPosition-=3;
		}
		return numWithCommas;
	};
	
	std::string output;
	if(isFraction){
		if(denominator == 1){
			output = format(std::to_string(numerator));
		}
		else if(denominator == 0){
			output = "nan";
		}
		else{
			output = format(std::to_string(numerator)) + '/' + format(std::to_string(denominator));
		}
	}
	else{
		if(!std::isfinite(decimal)){
			output = "DECERR";
		}
		else{
			output = std::to_string(decimal);
		}
	}
	return output;
}

Fraction Fraction::pow(const Fraction& num){
	Fraction output;
	if(isFraction && num.isFraction && num.getDenominator() == 1){
		output = Fraction(1);
		for(long long i = 0; i < std::abs(num.getNumerator()); i++){
			output = output * *this;
		}
		if(num.getNumerator() < 0){
			output = Fraction(1) / output;
		}
	}
	else{
		output = std::pow(getDecimal(), num.getDecimal());
	}
	output.reduce();
	return output;
}

Fraction Fraction::sqrt(){
	Fraction output;
	
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else if(isFraction && getDenominator() == 1){
		long double num = std::sqrt(numerator);
		if(num == std::floor(num)){
			output.numerator = num;
			output.denominator = 1;
		}
		else{
			output = num;
		}
	}
	else{
		output = std::sqrt(getDecimal());
	}
	
	output.reduce();
	return output;
}

Fraction Fraction::sin(){
	Fraction output;
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else{
		output = std::sin(getDecimal() * 3.141592653589793 / 180.0);
	}
	output.reduce();
	return output;
}

Fraction Fraction::cos(){
	Fraction output;
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else{
		output = std::cos(getDecimal() * 3.141592653589793 / 180.0);
	}
	output.reduce();
	return output;
}

Fraction Fraction::tan(){
	Fraction output;
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else{
		output = std::tan(getDecimal() * 3.141592653589793 / 180.0);
	}
	output.reduce();
	return output;
}

Fraction Fraction::asin(){
	Fraction output;
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else{
		output = std::asin(getDecimal()) * 180.0 / 3.141592653589793;
	}
	output.reduce();
	return output;
}

Fraction Fraction::acos(){
	Fraction output;
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else{
		output = std::acos(getDecimal())  * 180.0 / 3.141592653589793;
	}
	output.reduce();
	return output;
}

Fraction Fraction::atan(){
	Fraction output;
	if(denominator == 0){
		output = Fraction(0, 0);
	}
	else{
		output = std::atan(getDecimal())  * 180.0 / 3.141592653589793;
	}
	output.reduce();
	return output;
}

Fraction Fraction::log(const Fraction& num){
	Fraction output;
	
	if(denominator == 0 || num.denominator == 0){
		output = Fraction(0, 0);
	}
	else if(isFraction && getDenominator() == 1 && num.isFraction && num.denominator == 1){
		long double outNum = std::log(num.numerator) / std::log(numerator);
		if(outNum == std::floor(outNum)){
			output.numerator = outNum;
			output.denominator = 1;
		}
		else{
			output = outNum;
		}
	}
	else{
		output = std::log(num.getDecimal()) / std::log(getDecimal());
	}
	
	output.reduce();
	return output;
}

Fraction Fraction::operator+(const Fraction& num){
	if(isFraction && num.isFraction){
		if(this->denominator == 0 || num.denominator == 0){
			return Fraction(0, 0);
		}
		
		if (this->numerator == 0){
			return num;
		}
		else if (num.numerator == 0){
			return *this;
		}
		
		long multiplea = 1;
		long multipleb = 1;

		while (this->denominator * multiplea != num.denominator * multipleb){
			if (this->denominator * multiplea > num.denominator * multipleb){
				multipleb++;
			}
			else{
				multiplea++;
			}
		}

		Fraction c;
		c.numerator = (this->numerator * multiplea) + (num.numerator * multipleb);
		c.denominator = this->denominator * multiplea;

		c.reduce();

		return c;
	}
	else{
		Fraction c = getDecimal() + num.getDecimal();
		c.reduce();
		return c;
	}
}

Fraction Fraction::operator-(const Fraction& num){
	if(isFraction && num.isFraction){
		if(this->denominator == 0 || num.denominator == 0){
			return Fraction(0, 0);
		}
		
		long multiplea = 1;
		long multipleb = 1;

		if (this->numerator == 0){
			Fraction c(-num.numerator, num.denominator);
			return c;
		}
		if (num.numerator == 0){
			return *this;
		}

		while (this->denominator * multiplea != num.denominator * multipleb){
			if (this->denominator * multiplea > num.denominator * multipleb){
				multipleb++;
			}
			else{
				multiplea++;
			}
		}

		Fraction c;
		c.numerator = (this->numerator * multiplea) - (num.numerator * multipleb);
		c.denominator = this->denominator * multiplea;

		c.reduce();

		return c;
	}
	else{
		Fraction c = getDecimal() - num.getDecimal();
		c.reduce();
		return c;
	}
}

Fraction Fraction::operator*(const Fraction& num){
	if(isFraction && num.isFraction){
		if(this->denominator == 0 || num.denominator == 0){
			return Fraction(0, 0);
		}
		
		Fraction c;
		c.numerator = this->numerator * num.numerator;
		c.denominator = this->denominator * num.denominator;

		c.reduce();

		return c;
	}
	else{
		Fraction c = getDecimal() * num.getDecimal();
		c.reduce();
		return c;
	}
}

Fraction Fraction::operator/(const Fraction& num){
	if(isFraction && num.isFraction){
		if(this->denominator == 0 || num.denominator == 0){
			return Fraction(0, 0);
		}
		
		Fraction c;
		c.numerator = this->numerator * num.denominator;
		c.denominator = this->denominator * num.numerator;

		c.reduce();

		return c;
	}
	else{
		Fraction c = getDecimal() / num.getDecimal();
		c.reduce();
		return c;
	}
}

Fraction Fraction::operator%(const Fraction& num){
	if(isFraction && num.isFraction){
		if(denominator == 0 || num.denominator == 0){
			return Fraction(0, 0);
		}
		if(num.numerator == 0){
			return Fraction(0, 0);
		}
		if(numerator == 0){
			return Fraction(0, 1);
		}
		
		Fraction a = *this;
		if(a.numerator < 0){
			a = a * -1;
		}
		
		Fraction b = num;
		if(b.numerator < 0){
			b = b * -1;
		}
		
		while(a >= b){
			a = a - b;
		}
		
		if((numerator < 0) != (num.numerator < 0)){
			a = a * -1;
		}
		
		return a;
	}
	else{
		Fraction c = std::fmod(getDecimal(), num.getDecimal());
		c.reduce();
		return c;
	}
}

void Fraction::operator=(const Fraction& num){
	if(num.isFraction){
		numerator = num.numerator;
		denominator = num.denominator;
		isFraction = true;
	}
	else{
		decimal = num.decimal;
		isFraction = false;
	}
}

void Fraction::operator=(const long long& num){
	this->numerator = num;
	this->denominator = 1;
	isFraction = true;
}

void Fraction::operator=(const long double& num){
	isFraction = false;
	decimal = num;
}

bool Fraction::operator==(const Fraction& num){
	if(isFraction && num.isFraction){
		return this->numerator == num.numerator && this->denominator == num.denominator;
	}
	else{
		return getDecimal() == num.getDecimal();
	}
}

bool Fraction::operator!=(const Fraction& num){
	return !(*this == num);
}

bool Fraction::operator<(const Fraction& num) const{
	if(isFraction && num.isFraction){
		if(denominator == 0 || num.denominator == 0){
			return false;
		}
		
		long multiplea = 1;
		long multipleb = 1;

		while (denominator * multiplea != num.denominator * multipleb){
			if (denominator * multiplea > num.denominator * multipleb){
				multipleb++;
			}
			else{
				multiplea++;
			}
		}
		
		return numerator * multiplea < num.numerator * multipleb;
	}
	else{
		if(getDecimal() == num.getDecimal()){
			if(isFraction){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return getDecimal() < num.getDecimal();
		}
	}
}

bool Fraction::operator>(const Fraction& num){
	return !(*this <= num);
}

bool Fraction::operator<=(const Fraction& num){
	return *this < num || *this == num;
}

bool Fraction::operator>=(const Fraction& num){
	return *this > num || *this == num;
}

std::ostream& Fraction::operator<<(std::ostream& s){
	s << toString();
	return s;
}