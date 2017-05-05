#include <iostream>
#include <string>
//#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

struct hebamme{
	std::string name;
	int dienste;
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
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "sechs";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "sieben";

	long timestamp = time(NULL);
	std::cout << "timestamp = " << timestamp << std::endl;
	srand (timestamp);


	for(int j = 0; j<rota.size();j++){
		NEWRANDOM:rnd = rand() % hebammen.size(); 	

		//criteria:
		//not day and night after one another:

			if(j>1){
				if(rota.at(j-1) == rnd){
					goto NEWRANDOM;
				}else{;}
			}else{;}

		//no more than three shifts after one another

			if(j>6){
				if(rnd == rota.at(j-2) && rnd == rota.at(j-4) && rnd == rota.at(j-6)){
					goto NEWRANDOM;
				}else{;}
			}else{;}

		rota.at(j) = rnd;
	}

	//count dienste:
	for(int j = 0; j < hebammen.size(); j++){
		hebammen.at(j).dienste = 0;
	}



	//output:
	std::cout << std::endl << std::endl;
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
		if(j<9){
			std::cout << " ";
		}
		std::cout << " "  << j+1;
	}
	std::cout << std::endl;

	//spacer:
	for(int j = 0; j < max_length + 2 + 1 + 3*days;j++){ 
		std::cout<< "=";
	}
	std::cout << std::endl;

	//rows
	for(int i = 0; i < hebammen.size(); i++){
		std::cout << hebammen.at(i).name;
		for(int j = 0; j < max_length - hebammen.at(i).name.length() + 2; j++){
			std::cout << " ";
		}
		std::cout << "|";
		for(int j = 0 ;j < 2 * days; j+=2){
			std::cout << "  ";	
			if(rota.at(j) == i){
				std::cout << "T";
			}else if(rota.at(j+1) == i){
				std::cout << "N";
			}else{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
	return 0;
}
