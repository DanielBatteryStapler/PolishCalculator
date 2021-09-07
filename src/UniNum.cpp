#include "UniNum.h"

UniNum::UniNum(){
	//do nothing
}

UniNum::UniNum(Fraction num){
	numSet.insert(num);//thats it
}

std::string UniNum::toString()const{
	std::string output;
	if(numSet.size() == 0){
		output = "EmptySet";
	}
	else if(numSet.size() == 1){
		output = numSet.begin()->toString();
	}
	else{
		output += '{';
		for(auto i = numSet.begin(); i != numSet.end(); i++){
			auto y = i;
			if(++y != numSet.end()){
				output += i->toString() + ", ";
			}
			else{
				output += i->toString() + '}';
			}
		}
		
	}
	return output;
}

UniNum UniNum::getDecimal(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.getDecimal());
	});
	return output;
}

UniNum UniNum::sqrt(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.sqrt());
		output.numSet.insert(a.sqrt() * Fraction(-1));
	});
	return output;
}

UniNum UniNum::sin(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.sin());
	});
	return output;
}

UniNum UniNum::cos(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.cos());
	});
	return output;
}

UniNum UniNum::tan(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.tan());
	});
	return output;
}

UniNum UniNum::asin(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.asin());
	});
	return output;
}

UniNum UniNum::acos(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.acos());
	});
	return output;
}

UniNum UniNum::atan(){
	UniNum output;
	forEach([&output](Fraction a){
		output.numSet.insert(a.atan());
	});
	return output;
}

void UniNum::operator=(const UniNum& num){
	this->numSet = num.numSet;
}

UniNum UniNum::operator+(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a + b);
		});
	});
	return output;
}

UniNum UniNum::operator-(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a - b);
		});
	});
	return output;
}

UniNum UniNum::operator*(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a * b);
		});
	});
	return output;
}

UniNum UniNum::operator/(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a / b);
		});
	});
	return output;
}

UniNum UniNum::operator%(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a % b);
		});
	});
	return output;
}

UniNum UniNum::pow(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a.pow(b));
		});
	});
	return output;
}

UniNum UniNum::log(const UniNum& num){
	UniNum output;
	forEach([&output, &num](Fraction a){
		num.forEach([&output, &a](Fraction b){
			output.numSet.insert(a.log(b));
		});
	});
	return output;
}

UniNum UniNum::combine(const UniNum& num){
	UniNum output;
	output.numSet.insert(numSet.begin(), numSet.end());
	output.numSet.insert(num.numSet.begin(), num.numSet.end());
	return output;
}

std::ostream& UniNum::operator<<(std::ostream& s){
	s << toString();
	return s;
}

void UniNum::forEach(std::function<void(Fraction)> callback) const{
	for(auto i = numSet.begin(); i != numSet.end(); i++){
		callback(*i);
	}
}