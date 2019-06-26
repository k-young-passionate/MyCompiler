#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
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
	
	while(getline(inFile, line)){
		isFinished = false;
		if(!s.empty()){
			cout << s.top() << endl;
		}
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
				if((ISCHAR(line.at(0)) && ONLYWORD(line)) || line.at(0) == "}" || line == "IF" || line == "WHILE"){
					POP(2);
					a = s.top();
					s.push("slist");
					if(atoi(a) == 7){
						s.push("7");
						state = 7;
						goto REDUCE;
					} else {
						goto ERROR;
					}
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
				if((ISCHAR(line.at(0)) && ONLYWORD(line))||line.at(0) == '}' && line == "IF" && line == "ELSE" && line =="WHILE" && line.at(0) == '%'){
					s.pop();
					s.pop();
					s.pop();
					s.pop();
					s.pop();
					s.pop();
				} else {
					goto ERROR;
				}
				break;
			case 13:
				
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
				IGNORE(line.at(0));
				if(line.at(0) == ';'){
					s.push(line);
					s.push("17");
					state = 17;
				} else {
					goto ERROR;
				}
				break;
			case 20:
				break;
			case 21:
				break;
			case 22:
				IGNORE(line.at(0));
				if(line.at(0) == '}'){
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
				} else {
					goto ERROR;
				}
				break;
			case 33:
				
				break;
			case 34:

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

	inFile.close();
	outFile.close();
	return 0;

	ERROR:
		cout << "COMPILE ERROR" << endl;
		inFile.close();
		outFile.close();
		exit(1);
}
