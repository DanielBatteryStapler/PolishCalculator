#pragma once

#include <string>
#include <map>

#include "Operator.h"

static std::map<char, NumberType> values;

static void setConstants(){
	Fraction temp = (long double)2.71828;
	values['e'] = temp;
	temp = (long double)3.14159;
	values['p'] = temp;
}

static void processInput(std::string input){
	char newVar = 0;
	
	trimString(input);//just trim it
	
	if(input[0] == '='){
		int i = 1;
		for(bool keepGoing = true; keepGoing && i < input.size(); i++){
			switch(input[i]){
			default://assume variable
				newVar = input[i];
				keepGoing = false;
				break;
			case ' ':
			case ',':
				//do nothing
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			case '.':
			case '_':
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^':
			case 'r':
			case 's':
			case 'c':
			case 't':
			case 'S':
			case 'C':
			case 'T':
			case 'l':
			case 'u':
			case 'd':
				//if the variable is not a valid character
				nPrint("Invalid variable name\n");
				return;//exit this function
			}
		}
		input.erase(0, i);//erase the variable stuff from the input
	}
	
	Operator* calc = Operator::createExpressionTree(input);
	if(calc == nullptr){
		nPrint("nullptr\n\n = Error\n");
	}
	else{
		//set the variables
		for(auto i = values.begin(); i != values.end(); i++){
			calc->setVariable(i->first, i->second);
		}
		calc->printTree();
		
		try{
			NumberType output = calc->getValue();
			if(newVar != 0){
				nPrint(std::string("\n") + newVar + " = " + output.toString() + "\n");
				values[newVar] = output;
			}
			else{
				nPrint("\n = " + output.toString() + "\n");
			}
		}
		catch(std::exception& e){
			nPrint(" = Error\n");
		}
	}
	delete calc;
}