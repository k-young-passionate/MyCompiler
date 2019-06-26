#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "functions.hpp"
#include "functionStructure.h"
using namespace std;

#define ISNUM(value) (value >= '0' && value<= '9')
#define ISCHAR(value) ((value >= 'a' && value <= 'z')||(value >='A' && value <= 'Z'))
#define ONLYWORD(value) (value != "WHILE" && value != "IF" && value != "ELSE" && value != "THEN")
#define IGNORE(value) if(value == '%') break;
#define POP(num) for(int i=0; i<num; i++) { s.pop(); }

vector<struct FUNC> func;
vector<struct PROG> prog;
vector<struct BLOCK> block;
vector<struct SLIST> slist;
vector<struct STAT> stat;
vector<struct STAT_IF> stat_if;
vector<struct STAT_WHILE> stat_while;
vector<struct STAT_ASSIGN> stat_assign;
vector<struct COND> cond;
vector<struct EXPR> expr;
vector<struct FACT> fact;
vector<struct WORD> word;
vector<struct NUM> num;

int convertLang(string oname);

int parser(char* filename){
	string fname = filename;
	string oname = filename;
	string line;
	string a,b,c,d;
	string funcname;
	
	fname += ".lex";
	oname += ".code";

	ifstream inFile(fname);

	bool isFinished;
	int state = 0;
	stack<string> s;

	struct FUNC tmp_func;
	struct PROG tmp_prog;
	struct BLOCK tmp_block;
	struct SLIST tmp_slist;
	struct STAT tmp_stat;
	struct STAT_IF tmp_stat_if;
	struct STAT_WHILE tmp_stat_while;
	struct STAT_ASSIGN tmp_stat_assign;
	struct COND tmp_cond;
	struct EXPR tmp_expr;
	struct FACT tmp_fact;

	int func_index = 0;
	int prog_index = 0;
	int block_index =0;
	int slist_index = 0;
	int stat_index = 0;
	int stat_if_index = 0;
	int stat_while_index=0;
	int stat_assign_index = 0;
	int cond_index = 0;
	int expr_index = 0;
	int fact_index = 0;


	while(getline(inFile, line)){
		isFinished = false;
		if(!s.empty()){
			cout << s.top() << endl;
		} 

		cout << line << endl;
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
				POP(1);
				tmp_func.root = &prog[atoi(s.top().c_str())];
				POP(2);
				func.push_back(tmp_func);
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
					tmp_block.be = ENUM_BLOCK;
					tmp_block.sl = NULL;
				} else {
					goto ERROR;
				}
				break;
			case 5: 
				POP(1);
				tmp_prog.block = &block[atoi(s.top().c_str())];
				POP(6);
				tmp_prog.word = new char[s.top().length()];
				strcpy(tmp_prog.word, s.top().c_str());
				prog.push_back(tmp_prog);
				POP(1);
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
					tmp_slist.se = ENUM_STAT;
					POP(1);
					tmp_slist.sl = &slist[atoi(s.top().c_str())];
					POP(1);
					a = s.top();
					slist.push_back(tmp_slist);
					s.push(to_string(slist.size() - 1));
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
					POP(3);
					tmp_block.sl = &slist[atoi(s.top().c_str())]; 
					POP(3);
					a = s.top();
					block.push_back(tmp_block);
					s.push(to_string(block.size()-1));
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
					POP(1);
					tmp_slist.se = ENUM_SLIST;
					tmp_slist.sl = &slist[atoi(s.top().c_str())];
					POP(2);
					tmp_slist.s = &stat[atoi(s.top().c_str())];
					POP(1);
					slist.push_back(tmp_slist);
					a = s.top();
					s.push(to_string(slist.size()-1));
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
					POP(1);
					tmp_expr.ee = ENUM_FACT; 
					tmp_expr.f = &fact[atoi(s.top().c_str())];
					POP(1);
					expr.push_back(tmp_expr);
					a = s.top();
					s.push(to_string(expr.size()-1));
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
					POP(1);
					tmp_fact.fe = ENUM_NUM;
					tmp_fact.num = atoi(s.top().c_str());
					POP(1);
					fact.push_back(tmp_fact);
					a = s.top();
					s.push(to_string(fact.size() - 1));
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
					POP(1);
					tmp_fact.fe = ENUM_WORD;
					tmp_fact.word = new char[s.top().length()];
					strcpy(tmp_fact.word, (s.top().c_str()));
					POP(1);
					fact.push_back(tmp_fact);
					a = s.top();
					s.push(to_string(fact.size() - 1));
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
					POP(1);
					tmp_stat_assign.expr = &expr[atoi(s.top().c_str())];
					POP(4);
					tmp_stat_assign.word = new char[s.top().length()];
					strcpy(tmp_stat_assign.word, s.top().c_str());
					POP(3);
					stat_assign.push_back(tmp_stat_assign);
					a = s.top();
					s.push(to_string(stat_assign.size()-1));
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
					POP(1);
					tmp_cond.e2 = &expr[atoi(s.top().c_str())];
					POP(4);
					tmp_cond.c = '>';
					tmp_cond.e1 = &expr[atoi(s.top().c_str())];
					POP(1);
					cond.push_back(tmp_cond);
					a = s.top();
					s.push(to_string(cond.size() - 1));
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
					POP(1);
					tmp_cond.e2 = &expr[atoi(s.top().c_str())];
					POP(4);
					tmp_cond.c = '<';
					tmp_cond.e1 = &expr[atoi(s.top().c_str())];
					POP(1);
					cond.push_back(tmp_cond);
					a = s.top();
					s.push(to_string(cond.size() - 1));
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
					POP(1);
					tmp_expr.f = &fact[atoi(s.top().c_str())];
					POP(4);
					tmp_expr.ee = ENUM_ADDITION;
					tmp_expr.expr = &expr[atoi(s.top().c_str())];
					POP(1);
					expr.push_back(tmp_expr);
					a = s.top();
					s.push(to_string(expr.size()-1));
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
					POP(1);
					tmp_stat_while.block = &block[atoi(s.top().c_str())];
					POP(4);
					tmp_stat_while.cond = &cond[atoi(s.top().c_str())];
					POP(5);
					stat_while.push_back(tmp_stat_while);
					a = s.top();
					s.push(to_string(stat_while.size() - 1));
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
					POP(1);
					tmp_stat_if.elseblock = &block[atoi(s.top().c_str())];
					POP(4);
					tmp_stat_if.ifblock = &block[atoi(s.top().c_str())];
					POP(6);
					tmp_stat_if.cond = &cond[atoi(s.top().c_str())];
					POP(5);
					stat_if.push_back(tmp_stat_if);
					a = s.top();
					s.push(to_string(stat_if.size() - 1));
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
	convertLang(oname);
	return 0;

	ERROR:
		cout << "COMPILE ERROR" << endl;
		inFile.close();
		exit(1);
}


int convertLang(string oname){

	ofstream outFile(oname);
	stack<void*> s;
	for(int i=func.size()-1;i>=0;i++){
//		outFile << "BEGIN " << (func[i].root)->word;

//		outFile << "END " << (func[i].root)->word;
	}

	outFile.close();
	return 0;	
}
