#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <string.h>
#include "tmp.h"

#define USELESS while(true){ inFile.get(buffer); if(!(buffer==' '||buffer=='\t')) break; }
#define ISNUM(value) if(value >= '0' && value <= '9')
#define ISCHAR(value) if((value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z'))

using namespace std;

struct SYM{
	TYPE_E type;
	char * name;
};

int getblock(){
	return 0;
}

int main(int argc, char *argv[]){
	string fname = argv[1];
	string lname = argv[1];
	fname += ".symbol";
	lname += ".lex";
	ifstream inFile(argv[1]);
	ofstream outFile(fname);
	ofstream lexFile(lname);
	char buffer, past;
	past = 0;
	int index = 0;
	string tmp = "";
	vector<char*> symbols;
	while(inFile.get(buffer)){
//		cout << buffer;
		if(buffer != ' ' && buffer != '\t'){
			switch(buffer){
				case '\n':
					if(past == '\n')
						goto HERE;
					break;
				case '}':
					if(past == '{')
						lexFile << endl;
				case ';':
				case '(':
				case ')':
				case '{':
				case '=':
				case '+':
				case '<':
				case '>':
					if(past != '\n'){
						lexFile << endl;
						past = '\n';
					}
					break;
				default:
					if(past != 0 && past != '\n'){
						ISNUM(buffer){
							ISNUM(past){

							} else {
								lexFile << endl;
								past = '\n';
							}
						} else {
							ISCHAR(buffer){
								ISCHAR(past){

								} else {
									if(past == ')'){
										lexFile << endl;
									}
									lexFile << endl;
									past = '\n';
								}
							}
						}
					}
					break;
			}
						lexFile << buffer;
			HERE:
				past = buffer;
		}
		
	}
	lexFile.close();
	inFile.close();
	ifstream linFile(lname);
	outFile << "INDEX\t\tTYPE\t\tname\n";
	while(linFile.get(buffer)){
		if(buffer == '\n')
			continue;
		if((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <='Z')){
			tmp += buffer;
		} else {
			if(tmp == "WHILE") {
				outFile << index++ << "\t\t\tWHILE\t\t" << tmp << endl;
			} else if (tmp == "IF") {
				outFile << index++ << "\t\t\tIF  \t\t" << tmp << endl;
			} else {
				if( buffer == '(') {
					while(linFile.get(buffer)){
						if(buffer != '\n'){
							break;
						}
					}
					if(buffer == ')')
						outFile << index++ << "\t\t\tFUNC\t\t" << tmp << endl;
				} else if (buffer == '=') {
					outFile << index++ << "\t\t\tVAR \t\t" << tmp << endl;
				}
				tmp = "";
			}
		}
	}

	inFile.close();
	outFile.close();
	return 0;

	ERROR:
		cout << SYNTAXERROR;
		inFile.close();
		outFile.close();
		exit(1);
}
