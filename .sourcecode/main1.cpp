//TODO: an issue with counting nachtdienste
// issue with dienste counting

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <unistd.h>

int iterations = 1000;

struct hebamme{
	std::string name;
	int dienste;
	int nachtdienste;
	int max_dienste;
	std::vector<int> freiwuensche_tag;
	std::vector<int> freiwuensche_nacht;
	std::vector<int> freiwuensche_wochentag_tag;
	std::vector<int> freiwuensche_wochentag_nacht;
	std::vector<int> rota_exceptions;
};

int days; // = 30; // days of the month
int wochentag_vom_ersten; // = 0; // weekday of first day in month; 0=mo,1=tue;...



int main(){

	//used for random:
	long timestamp = time(NULL);
//	timestamp = 1507384137;
	std::cout << "timestamp: " << timestamp << std::endl;
	srand (timestamp);

	// data of hebammen:
	std::vector<hebamme> hebammen (1);