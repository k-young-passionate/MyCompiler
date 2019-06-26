#include <fstream>
#include <string>
#include "functions.hpp"

using namespace std;

int main(int argc, char *argv[]){
	scanner(argv[1]);
	parser(argv[1]);
	return 0;
}
