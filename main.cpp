#include <iostream>
#include <string>
//#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>

int iterations = 100000;

struct hebamme{
	std::string name;
	int dienste;
	std::vector<int> freiwuensche_tag;
	std::vector<int> freiwuensche_nacht;
	std::vector<int> freiwuensche_wochentag_tag;
	std::vector<int> freiwuensche_wochentag_nacht;
	std::vector<int> rota_exceptions;
};

int days = 31;
int wochentag_vom_ersten = 0;
int shifts = days * 2; //hardcoded to two shifts

std::vector<int> rota(shifts);
std::vector<int> best_rota(shifts);
double best_stddev = shifts;


int main(){

	std::cout << std::endl;

	std::vector<hebamme> hebammen (1);
	hebammen.back().name = "null";
	hebammen.back().freiwuensche_wochentag_tag.push_back(1);
	hebammen.back().freiwuensche_wochentag_nacht.push_back(1);
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "eins";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "zwei";
	hebammen.back().freiwuensche_tag.push_back(9);
	hebammen.back().freiwuensche_nacht.push_back(9);
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "drei";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "vier";
	hebammen.resize(hebammen.size()+1);
	hebammen.back().name = "fuenf";

	long timestamp = time(NULL);
	std::cout << "timestamp       = " << timestamp << std::endl;
	srand (timestamp);

	for(int heb = 0; heb < hebammen.size() ; heb++){
	int next_push_back = 0;
	
		for (int fr = 0; fr < hebammen.at(heb).freiwuensche_tag.size(); fr++){
			next_push_back = hebammen.at(heb).freiwuensche_tag.at(fr)*2 - 2;
			hebammen.at(heb).rota_exceptions.push_back(next_push_back);
		}
	
		for (int fr = 0; fr < hebammen.at(heb).freiwuensche_nacht.size(); fr++){
			next_push_back = hebammen.at(heb).freiwuensche_nacht.at(fr)*2 - 1;
			hebammen.at(heb).rota_exceptions.push_back(next_push_back);
		}

		for (int fr = 0; fr < hebammen.at(heb).freiwuensche_wochentag_tag.size(); fr++){
			next_push_back = -14;
			while (next_push_back < shifts){
				next_push_back += 2 * hebammen.at(heb).freiwuensche_wochentag_nacht.at(fr) ; 
				next_push_back -= 2*wochentag_vom_ersten; 
				hebammen.at(heb).rota_exceptions.push_back(next_push_back);
				next_push_back+=14;
			}
		}

		for (int fr = 0; fr < hebammen.at(heb).freiwuensche_wochentag_nacht.size(); fr++){
			next_push_back = -13;
			while (next_push_back < shifts){
				next_push_back += 2 * hebammen.at(heb).freiwuensche_wochentag_nacht.at(fr) ; 
				next_push_back -= 2*wochentag_vom_ersten; 
				hebammen.at(heb).rota_exceptions.push_back(next_push_back);
				next_push_back+=14;
			}
		}

	}
	for(int debug = 0 ; debug < hebammen.at(0).rota_exceptions.size(); debug++){
	std::cout << hebammen.at(0).rota_exceptions.at(debug) << " ";
	}
	std::cout << std::endl;

	for(int step = 0; step < iterations ; step++){

		for(int j = 0; j<rota.size();j++){
			int rnd = 0;
			NEWRANDOM:rnd = rand() % hebammen.size(); 	
	
			//criteria:
			//not day and night after one another:
	
				if(j>0){
					if(rota.at(j-1) == rnd){
						goto NEWRANDOM;
					}
				}
	
			//no more than three shifts after one another
	
				if(j>6){
					if(rnd == rota.at(j-2) && rnd == rota.at(j-4) && rnd == rota.at(j-6)){
						goto NEWRANDOM;
					}
				}

			//check for freiwuensche
				for (int fr = 0; fr < hebammen.at(rnd).rota_exceptions.size(); fr++){
					if(hebammen.at(rnd).rota_exceptions.at(fr) == j){
						goto NEWRANDOM;
					}
				}				
	
			rota.at(j) = rnd;
		}
	
		//count dienste:
		for(int j = 0; j < hebammen.size(); j++){
			hebammen.at(j).dienste = 0;
		}
		for(int j = 0; j < hebammen.size(); j++){
			for(int i = 0; i < rota.size(); i++){
				if(rota.at(i) == j){
					hebammen.at(j).dienste++;
				}
			}
		}
	
		//average_dienste:
		double average_dienste = 0;
		for(int j = 0; j < hebammen.size(); j++){
			average_dienste += (double) hebammen.at(j).dienste;
		}
		average_dienste /= (double) hebammen.size();
		//stddev:
		double stddev = 0;
		for(int j = 0; j < hebammen.size(); j++){
			stddev += pow((average_dienste - (double) hebammen.at(j).dienste),2.0);
		}
		stddev /= (double) hebammen.size() - 1.0;
		stddev = sqrt(stddev);
	
		if (stddev < best_stddev){
			best_rota = rota;
			best_stddev = stddev;
		}

		//progressbar
//		if(i % (iterations / 10) == 0){
//			std::cout << i * 100 / iterations << "% ... "; 
//		}
	}

	//count dienste best:
	for(int j = 0; j < hebammen.size(); j++){
		hebammen.at(j).dienste = 0;
	}
	for(int j = 0; j < hebammen.size(); j++){
		for(int i = 0; i < best_rota.size(); i++){
			if(best_rota.at(i) == j){
				hebammen.at(j).dienste++;
			}
		}
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
	std::cout << "| Dienste |";
	for(int j = 0; j < days ; j++){
		if(j<9){
			std::cout << " ";
		}
		std::cout << " "  << j+1;
	}
	std::cout << std::endl;

	//spacer:
	for(int j = 0; j < max_length + 2 + 1 + 10 + 3*days;j++){ 
		std::cout<< "=";
	}
	std::cout << std::endl;

	//rows
	for(int i = 0; i < hebammen.size(); i++){
		std::cout << hebammen.at(i).name;
		for(int j = 0; j < max_length - hebammen.at(i).name.length() + 2; j++){
			std::cout << " ";
		}
		std::cout << "|      ";
		if(hebammen.at(i).dienste < 10){
			std::cout << " ";
		}
		std::cout << hebammen.at(i).dienste;
		std::cout << " |";
		for(int j = 0 ;j < 2 * days; j+=2){
			std::cout << "  ";	
			if(best_rota.at(j) == i){
				std::cout << "T";
			}else if(best_rota.at(j+1) == i){
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
