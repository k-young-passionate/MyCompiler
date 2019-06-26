#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <string.h>
#include "functions.hpp"

#define ISNUM(value) if(value >= '0' && value <= '9')
#define ISCHAR(value) if((value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z'))

using namespace std;


int scanner(char* filename){
	string fname = filename;
	string lname = filename;
	string funcname;
	string tmp = "";

	fname += ".symbol";
	lname += ".lex";

	ifstream inFile(filename);
	ofstream outFile(fname);
	ofstream lexFile(lname);

	char buffer, past, pastchar;
	
	bool closeflag = false;
	bool funcendflag = false;

	int pcount = 0;
	int whilecount = 0;
	int ifcount = 0;
	int index = 0;
	
	stack<string> s;
	stack<int> si;

	past = 0;
	while(inFile.get(buffer)){
//		cout << buffer;
		if(buffer != ' ' && buffer != '\t'){
			switch(buffer){
				case '\n':
					if(past == '\n')
						goto HERE;
					break;
				case '}':
//					if(pastchar == '{'){
//						lexFile << '%';
//						past = '%';
//					}
					if(--pcount == 0){
						funcendflag = true;
					}
					closeflag = true;
				case ';':
				case '(':
				case '=':
				case '+':
				case '<':
				case '>':
				case '{':
					if(!closeflag && buffer == '{'){
						pcount++;
					}
					closeflag = false;
				case ')':
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
									lexFile << endl;
									past = '\n';
								}
							}
						}
					}
					break;
			}
						lexFile << buffer;
						if(funcendflag){
							lexFile << endl << "%";
							funcendflag = false;
						}
			HERE:
				if(buffer != '\n'){
					pastchar = buffer;
				}
				past = buffer;
		}
		
	}
//	if(past == '\n')
//		lexFile << "%";
//	else
//		lexFile << endl << "%";
	lexFile.close();
	inFile.close();

	cout << ".lex file has been generated." << endl;

	ifstream linFile(lname);
	outFile << "INDEX\t\tTYPE\t\tNAME\t\tSCOPE\n";
	while(linFile.get(buffer)){
		if(buffer == '\n')
			continue;
		if((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <='Z')){
			tmp += buffer;
		} else {
			if(tmp == "WHILE") {
				si.push(whilecount++);
				s.push("WHILE");
			} else if (tmp == "IF") {
				
			} else if (tmp == "THEN"){
				
				si.push(ifcount++);
				s.push("IFTHEN");
			
			} else if (tmp == "ELSE"){
				
				si.push(ifcount);
				s.push("IFELSE");

			} else {
				if( buffer == '(') {
					while(linFile.get(buffer)){
						if(buffer != '\n'){
							break;
						}
					}
					if(buffer == ')'){
						funcname = tmp;
						outFile << "----------------------------------------------------------------" << endl;
						outFile << index++ << "\t\tFUNC\t\t" << tmp << "\t\t" <<  funcname << endl;
						while(!s.empty()){
							s.pop();
						}
						while(!si.empty()){
							si.pop();
						}
						s.push(tmp);
						whilecount = 0;
						ifcount = 0;
					}
				} else if (buffer == '=') {
					if(s.top() == "WHILE" || s.top() == "IF" || s.top() =="IFTHEN" || s.top() == "IFELSE")
						outFile << index++ << "\t\tVAR \t\t" << tmp << "\t\t" << funcname <<  "-" << s.top() << "-" <<  si.top() << endl;
					else
						outFile << index++ << "\t\tVAR \t\t" << tmp << "\t\t" << s.top() << endl;
				} else if (buffer == '}'){
					if(!s.empty())
						s.pop();
					if(!si.empty()){
						si.pop();
					}
				}
			}
				tmp = "";
		}
	}

	cout << "Symbol Table has been generated." << endl;

	inFile.close();
	outFile.close();
	return 0;

}
