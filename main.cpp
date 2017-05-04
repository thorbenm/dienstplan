#include <iostream>
#include <string>
//#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

const int noh = 3;

struct hebamme{
	std::string name;
};


int main(){

	std::vector<hebamme> hebammen (1);
	hebammen.back().name = "null";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "eins";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "zwei";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "drei";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "vier";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "fuenf";

	srand (time(NULL));
	std::cout << rand() % hebammen.size() << std::endl;
	std::cout << hebammen.size() << " " << hebammen.at(2).name << std::endl;
	return 0;
}
