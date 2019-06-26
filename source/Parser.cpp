#include <fstream>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define ISNUM(value) (value >= '0' && value<= '9')
#define ISCHAR(value) ((value >= 'a' && value <= 'z')||(value >='A' && value <= 'Z'))
#define ONLYWORD(value) (value != "WHILE" && value != "IF" && value != "ELSE" && value != "THEN")

int main(int argc, char *argv[]){
	string fname = argv[1];
	string oname = argv[1];
	string line;
	bool isFinished;
	int state = 0;
	stack<string> s;
	fname += ".lex";
	oname += ".parse";
	ifstream inFile(fname);
	ofstream outFile(oname);
	
	while(getline(inFile, line)){
		if(!s.empty())
		isFinished = false;
		switch(state){
			case 0:
				s.push("$");
				s.push("0");
				if(ISCHAR(line.at(1)) && ONLYWORD(line)){
					s.push(line);
					s.push("2");
					state = 2;
				} else {
					goto ERROR;
				}
				break;
			case 1:
				if(s.top() == "$"){
					isFinished = true;
				}
				break;
			case 2:
				if(line.at(0) == '('){
					s.push(line);
					s.push("2");
					state = 3;
				} else {
					goto ERROR;
				}
				break;
			case 3:
				if(line.at(0) == ')') {
					s.push(line);
					s.push("4");
					state = 4;
				} else {
					goto ERROR;
				}
				break;
			case 4:
				if(line.at(0) == '{'){
					s.push(line);
					s.push("6");
					state = 6;
				}
				break;
			case 5: 
				
				break;
			case 6:
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

				break;
			case 9:
				if(line.at(0) == '('){
					s.push(line);
					s.push("14");
					state = 14;
				} else {
					goto ERROR;
				}
				break;
			case 10:
				if(line.at(0) == '('){
					s.push(line);
					s.push("15");
					state = 15;
				} else {
					goto ERROR;
				}
				break;
			case 11:
				if(line.at(0) == '='){
					s.push(line);
					s.push("16");
					state = 16;
				} else {
					goto ERROR;
				}
				break;
			case 12:
				break;
			case 13:
				
				break;
			case 14:
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
				if(line.at(0) == ')'){
					s.push(line);
					s.push("24");
					state = 24;
				} else {
					goto ERROR;
				}
				break;
			case 18:
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
				if(line.at(0) == '}'){
					s.push(line);
					s.push("28");
					state = 28;
				} else {
					goto ERROR;
				}
				break;
			case 23:
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
				if(line == "THEN"){
					s.push(line);
					s.push("30");
					state = 30;
				} else {
					goto ERROR;
				}
				break;
			case 25:
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
				if(line.at(0) == '{'){
					s.push(line);
					s.push("6");
					state = 6;
				} else {
					goto ERROR;
				}
				break;
			case 31:
				if(line.at(0) == '+'){
					s.push(line);
					s.push("27");
					state = 27;
				} else {
					goto ERROR;
				}
				break;
			case 32:
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
				if(line == "ELSE"){
					s.push(line);
					s.push("36");
					state = 36;
				} else {
					goto ERROR;
				}
				break;
			case 36:
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
