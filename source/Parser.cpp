#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include "functionStructure.h"
using namespace std;

#define ISNUM(value) (value >= '0' && value<= '9')
#define ISCHAR(value) ((value >= 'a' && value <= 'z')||(value >='A' && value <= 'Z'))
#define ONLYWORD(value) (value != "WHILE" && value != "IF" && value != "ELSE" && value != "THEN")
#define IGNORE(value) if(value == '%') break;
#define POP(num) for(int i=0; i<num; i++) { s.pop(); }

int main(int argc, char *argv[]){
	string fname = argv[1];
	string oname = argv[1];
	string line;
	string a,b,c,d;
	bool isFinished;
	int state = 0;
	stack<string> s;
	fname += ".lex";
	oname += ".parse";
	ifstream inFile(fname);
	ofstream outFile(oname);
	
	pointer->root->word = "hi";
	while(getline(inFile, line)){
		isFinished = false;
		REDUCE:
		switch(state){
			case 0:
				IGNORE(line.at(0));
				s.push("$");
				s.push("0");
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("2");
					state = 2;
				} else {
					goto ERROR;
				}
				break;
			case 1:
				POP(3);
				if(s.top() == "$"){
					state = 0;
					isFinished = true;
				}
				break;
			case 2:
				IGNORE(line.at(0));
				if(line.at(0) == '('){
					s.push(line);
					s.push("2");
					state = 3;
				} else {
					goto ERROR;
				}
				break;
			case 3:
				IGNORE(line.at(0));
				if(line.at(0) == ')') {
					s.push(line);
					s.push("4");
					state = 4;
				} else {
					goto ERROR;
				}
				break;
			case 4:
				IGNORE(line.at(0));
				if(line.at(0) == '{'){
					s.push(line);
					s.push("6");
					state = 6;
				} else {
					goto ERROR;
				}
				break;
			case 5: 
				POP(8);
				s.push("prog");
				s.push("1");
				state = 1;
				goto REDUCE;
				break;
			case 6:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("11");
					state = 11;
				} else if(line == "IF") {
					s.push(line);
					s.push("9");
					state = 9;
				} else if(line == "WHILE"){
					s.push(line);
					s.push("10");
					state = 10;
				} else {
					goto ERROR;
				}
				break;
			case 7:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("11");
					state = 11;
				} else if(line.at(0) == '}'){
					s.push(line);
					s.push("12");
					state = 12;
				} else if(line == "IF") {
					s.push(line);
					s.push("9");
					state = 9;
				} else if(line == "WHILE"){
					s.push(line);
					s.push("10");
					state = 10;
				} else {
					goto ERROR;
				}
				break;
			case 8:
				if((ISCHAR(line.at(0)) && ONLYWORD(line)) || line.at(0) == '}' || line == "IF" || line == "WHILE"){
					POP(2);
					a = s.top();
					s.push("slist");
					if(atoi(a.c_str()) == 6){
						s.push("7");
						state = 7;
						goto REDUCE;
					} else {
						goto ERROR;
					}
				} else {
					goto ERROR;
				}
				break;
			case 9:
				IGNORE(line.at(0));
				if(line.at(0) == '('){
					s.push(line);
					s.push("14");
					state = 14;
				} else {
					goto ERROR;
				}
				break;
			case 10:
				IGNORE(line.at(0));
				if(line.at(0) == '('){
					s.push(line);
					s.push("15");
					state = 15;
				} else {
					goto ERROR;
				}
				break;
			case 11:
				IGNORE(line.at(0));
				if(line.at(0) == '='){
					s.push(line);
					s.push("16");
					state = 16;
				} else {
					goto ERROR;
				}
				break;
			case 12:
				if((ISCHAR(line.at(0)) && ONLYWORD(line))||line.at(0) == '}' || line == "IF" || line == "ELSE" || line =="WHILE" || line.at(0) == '%'){
					POP(6);
					a = s.top();
					s.push("block");
					switch(atoi(a.c_str())){
						case 4:
							s.push("5");
							state = 5;
							break;
						case 28:
							s.push("34");
							state = 34;
							break;
						case 30:
							s.push("35");
							state = 35;
							break;
						case 36:
							s.push("37");
							state = 37;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 13:
				if((ISCHAR(line.at(0)) && ONLYWORD(line)) || line.at(0) == '}' || line == "IF" || line =="WHILE"){
					POP(4);
					a = s.top();
					s.push("slist");
					switch(atoi(a.c_str())){
						case 6:
							s.push("7");
							state = 7;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 14:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("21");
					state = 21;
				} else if (ISNUM(line.at(0))){
					s.push(line);
					s.push("20");
					state = 20;
				} else {
					goto ERROR;
				} 
				break;
			case 15:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("21");
					state = 21;
				} else if (ISNUM(line.at(0))){
					s.push(line);
					s.push("20");
					state = 20;
				} else {
					goto ERROR;
				} 
				break;
			case 16:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("21");
					state = 21;
				} else if (ISNUM(line.at(0))){
					s.push(line);
					s.push("20");
					state = 20;
				} else {
					goto ERROR;
				} 
				break;
			case 17:
				IGNORE(line.at(0));
				if(line.at(0) == ')'){
					s.push(line);
					s.push("24");
					state = 24;
				} else {
					goto ERROR;
				}
				break;
			case 18:
				IGNORE(line.at(0));
				if(line.at(0) == '>'){
					s.push(line);
					s.push("25");
					state = 25;
				} else if (line.at(0) == '<') {
					s.push(line);
					s.push("26");
					state = 26;
				} else if (line.at(0) == '+'){
					s.push(line);
					s.push("27");
					state = 27;
				} else {
					goto ERROR;
				}
				break;
			case 19:
				if(line.at(0) == ')' || line.at(0) == ';' || line.at(0) =='>' || line.at(0) == '<' || line.at(0) == '+'){
					POP(2);
					a = s.top();
					s.push("expr");
					switch(atoi(a.c_str())){
						case 14:
						case 15:
							s.push("18");
							state = 18;
							break;
						case 16:
							s.push("23");
							state = 23;
							break;
						case 25:
							s.push("31");
							state = 31;
							break;
						case 26:
							s.push("32");
							state = 32;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 20:
				if(line.at(0) == ')' || line.at(0) == ';' || line.at(0) =='>' || line.at(0) == '<' || line.at(0) == '+'){
					POP(2);
					a = s.top();
					s.push("fact");
					switch(atoi(a.c_str())){
						case 14:
						case 15:
						case 16:
						case 25:
						case 26:
							s.push("19");
							state = 19;
							break;
						case 27:
							s.push("33");
							state = 33;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 21:
				if(line.at(0) == ')' || line.at(0) == ';' || line.at(0) =='>' || line.at(0) == '<' || line.at(0) == '+'){
					POP(2);
					a = s.top();
					s.push("fact");
					switch(atoi(a.c_str())){
						case 14:
						case 15:
						case 16:
						case 25:
						case 26:
							s.push("19");
							state = 19;
							break;
						case 27:
							s.push("33");
							state = 33;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 22:
				IGNORE(line.at(0));
				if(line.at(0) == ')'){
					s.push(line);
					s.push("28");
					state = 28;
				} else {
					goto ERROR;
				}
				break;
			case 23:
				IGNORE(line.at(0));
				if(line.at(0) == ';'){
					s.push(line);
					s.push("29");
					state = 29;
				} else if(line.at(0) == '+'){
					s.push(line);
					s.push("27");
					state = 27;
				} else {
					goto ERROR;
				}
				break;
			case 24:
				IGNORE(line.at(0));
				if(line == "THEN"){
					s.push(line);
					s.push("30");
					state = 30;
				} else {
					goto ERROR;
				}
				break;
			case 25:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("21");
					state = 21;
				} else if(ISNUM(line.at(0))){
					s.push(line);
					s.push("20");
					state = 20;
				} else {
					goto ERROR;
				}
				break;
			case 26:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("21");
					state = 21;
				} else if(ISNUM(line.at(0))){
					s.push(line);
					s.push("20");
					state = 20;
				} else {
					goto ERROR;
				}
				break;
			case 27:
				IGNORE(line.at(0));
				if(ISCHAR(line.at(0)) && ONLYWORD(line)){
					s.push(line);
					s.push("21");
					state = 21;
				} else if(ISNUM(line.at(0))){
					s.push(line);
					s.push("20");
					state = 20;
				} else {
					goto ERROR;
				}
				break;
			case 28:
				IGNORE(line.at(0));
				if(line.at(0) == '{'){
					s.push(line);
					s.push("6");
					state = 6;
				} else {
					goto ERROR;
				}
				break;
			case 29:
				if((ISCHAR(line.at(0))&&ONLYWORD(line)) || line.at(0) == '}' || line == "IF" || line == "WHILE"){
					POP(8);
					a = s.top();
					s.push("stat");
					switch(atoi(a.c_str())){
						case 6:
							s.push("8");
							state = 8;
							break;
						case 7:
							s.push("13");
							state = 13;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 30:
				IGNORE(line.at(0));
				if(line.at(0) == '{'){
					s.push(line);
					s.push("6");
					state = 6;
				} else {
					goto ERROR;
				}
				break;
			case 31:
				IGNORE(line.at(0));
				if(line.at(0) == '+'){
					s.push(line);
					s.push("27");
					state = 27;
				} else if (line.at(0) == ')') {
					POP(6);
					a = s.top();
					s.push("cond");
					switch(atoi(a.c_str())){
						case 14:
							s.push("17");
							state = 17;
							break;
						case 15:
							s.push("22");
							state = 22;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 32:
				IGNORE(line.at(0));
				if(line.at(0) == '+'){
					s.push(line);
					s.push("27");
					state = 27;
				} else if (line.at(0) == ')') {
					POP(6);
					a = s.top();
					s.push("cond");
					switch(atoi(a.c_str())){
						case 14:
							s.push("17");
							state = 17;
							break;
						case 15:
							s.push("22");
							state = 22;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 33:
				if(line.at(0) == ')' || line.at(0) == ';' || line.at(0) =='>' || line.at(0) == '<' || line.at(0) == '+'){
					POP(6);
					a = s.top();
					s.push("expr");
					switch(atoi(a.c_str())){
						case 14:
						case 15:
							s.push("18");
							state = 18;
							break;
						case 16:
							s.push("23");
							state = 23;
							break;
						case 25:
							s.push("31");
							state = 31;
							break;
						case 26:
							s.push("32");
							state = 32;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}	
				break;
			case 34:
				if((ISCHAR(line.at(0))&&ONLYWORD(line)) || line.at(0) == '}' || line == "IF" || line == "WHILE"){
					POP(10);
					a = s.top();
					s.push("stat");
					switch(atoi(a.c_str())){
						case 6:
							s.push("8");
							state = 8;
							break;
						case 7:
							s.push("13");
							state = 13;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}
				break;
			case 35:
				IGNORE(line.at(0));
				if(line == "ELSE"){
					s.push(line);
					s.push("36");
					state = 36;
				} else {
					goto ERROR;
				}
				break;
			case 36:
				IGNORE(line.at(0));
				if(line.at(0) == '{'){
					s.push(line);
					s.push("6");
					state = 6;
				} else {
					goto ERROR;
				}
				break;
			case 37:
				if((ISCHAR(line.at(0))&&ONLYWORD(line)) || line.at(0) == '}' || line == "IF" || line == "WHILE"){
					POP(16);
					a = s.top();
					s.push("stat");
					switch(atoi(a.c_str())){
						case 6:
							s.push("8");
							state = 8;
							break;
						case 7:
							s.push("13");
							state = 13;
							break;
						default:
							goto ERROR;
					}
					goto REDUCE;
				} else {
					goto ERROR;
				}

				break;
			default:
				break;
		}

		line = "";
	}

	if(!isFinished){
		cout << "Unexpected Termination." << endl;
		goto ERROR;
	}

	cout << "Parsing has been successfully completed." << endl;

	inFile.close();
	outFile.close();
	return 0;

	ERROR:
		cout << "COMPILE ERROR" << endl;
		inFile.close();
		outFile.close();
		exit(1);
}
