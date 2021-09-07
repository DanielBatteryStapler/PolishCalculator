#include "Operator.h"

bool useNCursesPrint = false;

bool isSingle(OperatorType type){
	switch(type){
	case OperatorType::Union:
	case OperatorType::Add:
	case OperatorType::Subtract:
	case OperatorType::Multiply:
	case OperatorType::Divide:
	case OperatorType::Modulo:
	case OperatorType::Power:
	case OperatorType::Log:
		return false;
	case OperatorType::Decimal:
	case OperatorType::Negative:
	case OperatorType::Sqrt:
	case OperatorType::Sine:
	case OperatorType::Cosine:
	case OperatorType::Tangent:
	case OperatorType::Insine:
	case OperatorType::Incosine:
	case OperatorType::Intangent:
		return true;
	case OperatorType::Undefined:
		throw std::invalid_argument("Attempted to call isSingle on a OperatorType::Undefined");
	}
	throw std::invalid_argument("Attempted to call isSingle on an invalid OperatorType");
}

Operator::Operator():type(OperatorType::Undefined),number(0),first(nullptr),second(nullptr),variable(0){}

Operator::~Operator(){
	if(first != nullptr){
		delete first;
	}
	if(second != nullptr){
		delete second;
	}
}

NumberType Operator::getValue(){
	
	if(type == OperatorType::Undefined){
		throw std::invalid_argument("Operator invalid, is undefined");
	}
	
	if(type == OperatorType::Const){
		return number;
	}
	
	if(type == OperatorType::Variable){
		return number;
	}
	
	if(first == nullptr || (second == nullptr && !isSingle(type))){
		throw std::invalid_argument("Operator invalid, contains invalid nullptrs in non-const type");
	}
	
	switch(type){
	case OperatorType::Decimal:
		return first->getValue().getDecimal();
		break;
	case OperatorType::Negative:
		return UniNum(Fraction(-1)) * first->getValue();
		break;
	case OperatorType::Union:
		return first->getValue().combine(second->getValue());
	case OperatorType::Add:
		return first->getValue() + second->getValue();
		break;
	case OperatorType::Subtract:
		return first->getValue() - second->getValue();
		break;
	case OperatorType::Multiply:
		return first->getValue() * second->getValue();
		break;
	case OperatorType::Divide:
		return first->getValue() / second->getValue();
		break;
	case OperatorType::Modulo:
		return first->getValue() % second->getValue();
		break;
	case OperatorType::Power:
		return first->getValue().pow(second->getValue());
		break;
	case OperatorType::Sqrt:
		return first->getValue().sqrt();
		break;
	case OperatorType::Sine:
		return first->getValue().sin();
		break;
	case OperatorType::Cosine:
		return first->getValue().cos();
		break;
	case OperatorType::Tangent:
		return first->getValue().tan();
		break;
	case OperatorType::Insine:
		return first->getValue().asin();
		break;
	case OperatorType::Incosine:
		return first->getValue().acos();
		break;
	case OperatorType::Intangent:
		return first->getValue().atan();
		break;
	case OperatorType::Log:
		return first->getValue().log(second->getValue());
		break;
	}
}

void Operator::setVariable(char var, NumberType num){
	if(type == OperatorType::Variable && variable == var){
		number = num;
	}
	else{
		if(first != nullptr){
			first->setVariable(var, num);
			if(second != nullptr){
				second->setVariable(var, num);
			}
		}
	}
}

void Operator::printTree(int tabs){
	for(int i = 0 ; i < tabs; i++){
		nPrint("  ");
	}
	switch(type){
	case OperatorType::Undefined:
		throw std::invalid_argument("Operator invalid, is undefined");
		break;
	case OperatorType::Const:
		nPrint(number.toString() + "\n");
		return;
		break;
	case OperatorType::Variable:
		nPrint(std::string(1, variable) + "->" + number.toString() + "\n");
		return;
		break;
	case OperatorType::Decimal:
		nPrint("dec\n");
		break;
	case OperatorType::Negative:
		nPrint("neg\n");
		break;
	case OperatorType::Union:
		nPrint("uni\n");
		break;
	case OperatorType::Add:
		nPrint("add\n");
		break;
	case OperatorType::Subtract:
		nPrint("sub\n");
		break;
	case OperatorType::Multiply:
		nPrint("mul\n");
		break;
	case OperatorType::Divide:
		nPrint("div\n");
		break;
	case OperatorType::Modulo:
		nPrint("mod\n");
		break;
	case OperatorType::Power:
		nPrint("pow\n");
		break;
	case OperatorType::Sqrt:
		nPrint("sqr\n");
		break;
	case OperatorType::Sine:
		nPrint("sin\n");
		break;
	case OperatorType::Cosine:
		nPrint("cos\n");
		break;
	case OperatorType::Tangent:
		nPrint("tan\n");
		break;
	case OperatorType::Insine:
		nPrint("isn\n");
		break;
	case OperatorType::Incosine:
		nPrint("ics\n");
		break;
	case OperatorType::Intangent:
		nPrint("itn\n");
		break;
	case OperatorType::Log:
		nPrint("log\n");
		break;
	}
	if(first == nullptr){
		for(int i = 0 ; i < tabs + 1; i++){
		nPrint("  ");
		}
		nPrint("nullptr\n");
	}
	else{
		first->printTree(tabs + 1);
	}
	
	if(!isSingle(type)){
		if(second == nullptr){
			for(int i = 0 ; i < tabs + 1; i++){
				nPrint("  ");
			}
			nPrint("nullptr\n");
		}
		else{
			second->printTree(tabs + 1);
		}
	}
}

Operator* Operator::createExpressionTree(std::string input){
	std::vector<Segment> syntaxVector;
	
	std::string temp;
	
	Segment newSeg;
	
	for(std::size_t i = 0; i < input.size(); i++){
		
		switch(input[i]){
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
			temp += input[i];
			continue;
		}
		
		if(temp.size() != 0){
			newSeg.type = OperatorType::Const;
			bool worked = true;
			try{
				newSeg.number = Fraction(temp);
			}
			catch(std::invalid_argument& e){
				worked = false;
				nPrint("Invalid Number!\n");
			}
			if(worked){
				syntaxVector.push_back(newSeg);
			}
			temp.clear();
		}
		
		switch(input[i]){
		case ' ':
		case ',':
			break;
		default://assume it is a variable
			newSeg.type = OperatorType::Variable;
			newSeg.variable = input[i];
			syntaxVector.push_back(newSeg);
			break;
		case 'd':
			newSeg.type = OperatorType::Decimal;
			syntaxVector.push_back(newSeg);
			break;
		case '_':
			newSeg.type = OperatorType::Negative;
			syntaxVector.push_back(newSeg);
			break;
		case 'u':
			newSeg.type = OperatorType::Union;
			syntaxVector.push_back(newSeg);
			break;
		case '+':
			newSeg.type = OperatorType::Add;
			syntaxVector.push_back(newSeg);
			break;
		case '-':
			newSeg.type = OperatorType::Subtract;
			syntaxVector.push_back(newSeg);
			break;
		case '*':
			newSeg.type = OperatorType::Multiply;
			syntaxVector.push_back(newSeg);
			break;
		case '/':
			newSeg.type = OperatorType::Divide;
			syntaxVector.push_back(newSeg);
			break;
		case '%':
			newSeg.type = OperatorType::Modulo;
			syntaxVector.push_back(newSeg);
			break;
		case '^':
			newSeg.type = OperatorType::Power;
			syntaxVector.push_back(newSeg);
			break;
		case 'r':
			newSeg.type = OperatorType::Sqrt;
			syntaxVector.push_back(newSeg);
			break;
		case 's':
			newSeg.type = OperatorType::Sine;
			syntaxVector.push_back(newSeg);
			break;
		case 'c':
			newSeg.type = OperatorType::Cosine;
			syntaxVector.push_back(newSeg);
			break;
		case 't':
			newSeg.type = OperatorType::Tangent;
			syntaxVector.push_back(newSeg);
			break;
		case 'S':
			newSeg.type = OperatorType::Insine;
			syntaxVector.push_back(newSeg);
			break;
		case 'C':
			newSeg.type = OperatorType::Incosine;
			syntaxVector.push_back(newSeg);
			break;
		case 'T':
			newSeg.type = OperatorType::Intangent;
			syntaxVector.push_back(newSeg);
			break;
		case 'l':
			newSeg.type = OperatorType::Log;
			syntaxVector.push_back(newSeg);
			break;
		}
	}
	
	if(temp.size() != 0){
		newSeg.type = OperatorType::Const;
		bool worked = true;
		try{
			newSeg.number = Fraction(temp);
		}
		catch(std::invalid_argument& e){
			worked = false;
			nPrint("Invalid Number!\n");
		}
		if(worked){
			syntaxVector.push_back(newSeg);
		}
		temp = "";
	}
	
	std::stack<Operator*> syntaxStack;
	
	Operator* baseOp = nullptr;
	
	for(auto i = syntaxVector.begin(); i != syntaxVector.end(); i++){
		Operator* newOp = new Operator;
		newOp->type = i->type;
		
		if(newOp->type == OperatorType::Const){
			newOp->number = i->number;
		}
		else if(newOp->type == OperatorType::Variable){
			newOp->variable = i->variable;
		}
		
		if(syntaxStack.size() == 0){
			if(baseOp == nullptr){
				baseOp = newOp;
			}
			else{
				delete newOp;
				nPrint("Unused Element!\n");
				continue;
			}
		}
		else{
			if(syntaxStack.top()->first == nullptr){
				syntaxStack.top()->first = newOp;
			}
			else if(syntaxStack.top()->second == nullptr){
				syntaxStack.top()->second = newOp;
			}
		}
		
		if(newOp->type == OperatorType::Const || newOp->type == OperatorType::Variable){
			while(syntaxStack.size() != 0 && (syntaxStack.top()->second != nullptr || isSingle(syntaxStack.top()->type))){
				syntaxStack.pop();
			}
		}
		else{
			syntaxStack.push(newOp);
		}
	}
	
	return baseOp;
}
