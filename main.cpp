#include <iostream>
#include <string>
//#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

struct hebamme{
	std::string name;
};

int days = 30;
int shifts = days * 2; //hardcoded to two shifts

std::vector<int> rota(shifts);

int rnd = 0;

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
//	srand (0);
//	std::cout << rand() % hebammen.size() << std::endl;
//	std::cout << hebammen.size() << " " << hebammen.at(2).name << std::endl;
	for(int j = 0; j<rota.size();j++){
		rnd = rand() % hebammen.size(); 	
		rota.at(j) = rnd;
	}
	for(int j = 0; j<rota.size();j++){
		std::cout << rota.at(j) << " ";
	}
	std::cout << std::endl;
	return 0;
}
