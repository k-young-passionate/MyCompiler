#include <fstream>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define ISNUM(value) (value >= '0' && value<= '9')
#define ISCHAR(value) ((value >= 'a' && value <= 'z')||(value >='A' && value <= 'Z'))

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
		isFinished = false;
		line = "";
		switch(state){
			case 0:
				s.push("$");
				s.push("0");
				if(ISCHAR(line.at(0)) && line != "IF" && line != "WHILE"){
					s.push(line);
					s.push("2");
					state = 2;
				} else {
					goto ERROR;
				}
				break;
			case 1:
				// nothing input
				isFinished = true;
				break;
			case 2:
				if(line.at(0) == '('){
					s.push(line);
					state = 3;
				} else {
					goto ERROR;
				}
				break;
			case 3:
				if(line.at(0) == ')') {
					s.push(line);
					state = 4;
				} else {
					goto ERROR;
				}
				break;
			case 4:
				if(ISCHAR){

				}
				break;
			case 5: 

				break;
			case 6:

				break;
			case 7:
				
				break;
			case 8:

				break;
			case 9:

				break;
			case 10:

				break;
			case 11:

				break;
			case 12:

				break;
			case 13:

				break;
			case 14:

				break;
			case 15:

				break;
			case 16:

				break;
			case 17:

				break;
			case 18:

				break;
			case 19:

				break;
			case 20:

				break;
			case 21:

				break;
			case 22:

				break;
			case 23:

				break;
			case 24:

				break;
			case 25:

				break;
			case 26:

				break;
			case 27:

				break;
			case 28:

				break;
			case 29:

				break;
			case 30:

				break;
			case 31:

				break;
			case 32:

				break;
			case 33:
				
				break;
			case 34:

				break;
			default:
				break;
		}
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
