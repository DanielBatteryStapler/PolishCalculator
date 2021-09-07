#pragma once

#include "StringTrimmer.h"

#include <stack>
#include <vector>
#include <ctgmath>
#include <string>
#include <stdexcept>
#include <iostream>
#include <ncurses.h>

#include "UniNum.h"

extern bool useNCursesPrint;

static void nPrint(std::string s){
	if(useNCursesPrint){
		waddstr(stdscr, s.c_str());
	}
	else{
		std::cout << s;
	}
}

enum OperatorType{Undefined, Const, Variable, Decimal, Union, Negative, Add, Subtract, Multiply, Divide, Modulo, Power, Sqrt, Sine, Cosine, Tangent, Insine, Incosine, Intangent, Log};

using NumberType = UniNum;

struct Segment{
	Segment():number(0),type(OperatorType::Undefined){}
	OperatorType type;
	NumberType number;
	char variable;
};

bool isSingle(OperatorType type);

class Operator{
public:
	Operator();
	~Operator();
	
	NumberType getValue();
	void setVariable(char var, NumberType num);
	void printTree(int tabs = 0);
	
	OperatorType type;
	NumberType number;
	Operator* first;
	Operator* second;
	char variable;
	
	static Operator* createExpressionTree(std::string input);
};