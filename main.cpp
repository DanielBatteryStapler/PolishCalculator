#include <string>
#include <iostream>
#include <ncurses.h>
#include <vector>

#include "Operator.h"
#include "ProcessInput.h"

int main(int argc, char** argv){
	std::cout << std::fixed;
	if(argc > 1){
		std::string input = argv[1];
		for(int i = 2; i < argc; i++){
			input += " " + std::string(argv[i]);
		}
		Operator* calc = Operator::createExpressionTree(input);
		if(calc == nullptr){
			std::cout << "\n";
			std::cout << "nullptr\n";
			std::cout << "\n = Error\n";
		}
		else{
			calc->setVariable('e', (long double)2.71828);
			calc->setVariable('p', (long double)3.14159);
			
			calc->printTree();
			std::cout << "\n";
			try{
				std::cout << " = " << calc->getValue().toString() << "\n";
			}
			catch(std::exception& e){
				std::cout << " = Error\n";
			}
		}
		delete calc;
		return 0;
	}
	
	useNCursesPrint = true;
	
	setConstants();
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	scrollok(stdscr,true);
	
	waddch(stdscr, '>');
	wrefresh(stdscr);
	
	bool keepGoing = true;
	std::vector<std::string> input;
	input.push_back(std::string());//push back the first one
	int inputIndex = 0;
	int inputX = 0;
	int y, x;
	
	while(keepGoing){
		int ch = wgetch(stdscr);
		switch(ch){
		case KEY_UP:
			inputX = 0;
			inputIndex--;
			if(inputIndex < 0){
				inputIndex = 0;
			}
			getyx(stdscr, y, x);
			wmove(stdscr, y, 0);
			clrtoeol();
			wmove(stdscr, y, 0);
			waddch(stdscr, '>');
			waddstr(stdscr, input[inputIndex].c_str());
			inputX = input[inputIndex].size();
			break;
		case KEY_DOWN:
			inputX = 0;
			inputIndex++;
			if(inputIndex == input.size()){
				inputIndex = input.size() - 1;
			}
			getyx(stdscr, y, x);
			wmove(stdscr, y, 0);
			clrtoeol();
			wmove(stdscr, y, 0);
			waddch(stdscr, '>');
			waddstr(stdscr, input[inputIndex].c_str());
			inputX = input[inputIndex].size();
			break;
		case KEY_LEFT:
			inputX--;
			if(inputX < 0){
				inputX = 0;
			}
			getyx(stdscr, y, x);
			wmove(stdscr, y, inputX + 1);
			break;
		case KEY_RIGHT:
			inputX++;
			if(inputX > input[inputIndex].size()){
				inputX--;
			}
			getyx(stdscr, y, x);
			wmove(stdscr, y, inputX + 1);
			break;
		case KEY_ENTER:
		case '\r':
		case '\n':
			if(inputIndex + 1 < input.size()){
				input[input.size() - 1] = input[inputIndex];
				inputIndex = input.size() - 1;
			}
			getyx(stdscr, y, x);
			wmove(stdscr, y, input[inputIndex].size() + 1);
			waddch(stdscr, '\n');
			wrefresh(stdscr);
			processInput(input[inputIndex]);
			wrefresh(stdscr);
			getyx(stdscr, y, x);
			wmove(stdscr, y, 0);
			waddch(stdscr, '>');
			wrefresh(stdscr);
			inputX = 0;
			inputIndex++;
			input.push_back(std::string());
			break;
		case KEY_BACKSPACE:
			if(inputIndex + 1 < input.size()){
				input[input.size() - 1] = input[inputIndex];
				inputIndex = input.size() - 1;
			}
			if(inputX != 0){
				inputX--;
				input[inputIndex].erase(inputX, 1);
				getyx(stdscr, y, x);
				wmove(stdscr, y, 0);
				clrtoeol();
				wmove(stdscr, y, 0);
				waddch(stdscr, '>');
				waddstr(stdscr, input[inputIndex].c_str());
				wmove(stdscr, y, inputX + 1);
			}
			break;
		case 'a':case 'A':
		case 'b':case 'B':
		case 'c':case 'C':
		case 'd':case 'D':
		case 'e':case 'E':
		case 'f':case 'F':
		case 'g':case 'G':
		case 'h':case 'H':
		case 'i':case 'I':
		case 'j':case 'J':
		case 'k':case 'K':
		case 'l':case 'L':
		case 'm':case 'M':
		case 'n':case 'N':
		case 'o':case 'O':
		case 'p':case 'P':
		case 'q':case 'Q':
		case 'r':case 'R':
		case 's':case 'S':
		case 't':case 'T':
		case 'u':case 'U':
		case 'v':case 'V':
		case 'w':case 'W':
		case 'x':case 'X':
		case 'y':case 'Y':
		case 'z':case 'Z':
		case '0':case '5':
		case '1':case '6':
		case '2':case '7':
		case '3':case '8':
		case '4':case '9':
		
		case '%':case '+':
		case '-':case '/':
		case '_':case '*':
		case '=':case '.':
		case '^':
		
		case ' ':case ',':
			if(ch == 'Q'){
				keepGoing = false;
				break;
			}
			if(inputIndex + 1 < input.size()){
				input[input.size() - 1] = input[inputIndex];
				inputIndex = input.size() - 1;
			}
			input[inputIndex].insert(input[inputIndex].begin() + inputX, ch);
			inputX++;
			getyx(stdscr, y, x);
			wmove(stdscr, y, 0);
			clrtoeol();
			wmove(stdscr, y, 0);
			waddch(stdscr, '>');
			waddstr(stdscr, input[inputIndex].c_str());
			wmove(stdscr, y, inputX + 1);
			break;
		}
	}
	
	endwin();
	
	return 0;
}