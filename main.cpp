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
		for(;;){
			rnd = rand() % hebammen.size(); 	
			if(j>1){
				if(rota.at(j-1) == rnd){;}
				else{break;}
			}
			else{break;}
		}
		rota.at(j) = rnd;
	}
	std::cout << std::endl;
	//output:
	std::cout << std::endl;
	std::cout << std::endl;
	int max_length = 0;
		for(int j = 0; j < hebammen.size(); j++){
			if(max_length < hebammen.at(j).name.length()){
				max_length = hebammen.at(j).name.length();
			}
		}

	//header:
	for(int j = 0; j < max_length + 2; j++){
		std::cout << " ";
	}
	std::cout << "|";
	for(int j = 0; j < days ; j++){
		if(j<10){
			std::cout << " ";
		}
		std::cout << " "  << j+1;
	}
	std::cout << std::endl;

	//spacer:
	for(int j = 0; j < max_length + 2 + 1 + 3*days ;j++){
		std::cout<< "=";
	}
	std::cout << std::endl;
	return 0;
}
