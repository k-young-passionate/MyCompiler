#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <string.h>

#define ISNUM(value) if(value >= '0' && value <= '9')
#define ISCHAR(value) if((value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z'))

using namespace std;


int main(int argc, char *argv[]){
	string fname = argv[1];
	string lname = argv[1];
	fname += ".symbol";
	lname += ".lex";
	ifstream inFile(argv[1]);
	ofstream outFile(fname);
	ofstream lexFile(lname);
	char buffer, past, pastchar;
	bool closeflag = false;
	bool funcendflag = false;
	int pcount = 0;
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
					if(pastchar == '{'){
						lexFile << '%';
						past = '%';
					}
					pcount--;
					if(pcount == 0){
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
						closeflag = false;
					}
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
	if(past == '\n')
		lexFile << "%";
	else
		lexFile << endl << "%";
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

}
