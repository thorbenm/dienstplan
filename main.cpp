#include <iostream>
#include <string>
//#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int noh = 3;

struct hebamme{
	std::string name;
	char kuerzel;
} heb[noh];


int main(){
	srand (time(NULL));
	heb[0].name = "null";	
	heb[0].kuerzel = '0';
	heb[1].name = "eins";	
	heb[1].kuerzel = '1';
	heb[2].name = "zwei";	
	heb[2].kuerzel = '2';
	std::cout << rand() % noh << std::endl;
	return 0;
}
