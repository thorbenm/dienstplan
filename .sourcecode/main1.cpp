//TODO: an issue with counting nachtdienste
// issue with dienste counting

#include <iostream>
#include <string>
//#include <random>
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

int days = 31; // days of the month
int wochentag_vom_ersten = 0; // weekday of first day in month; 0=mo,1=tue;...
int shifts = days * 2; //hardcoded to two shifts

std::vector<int> rota(shifts);
//used to choose best rota:
std::vector<int> best_rota(shifts);
double best_stddev = shifts;


int main(){

	//used for random:
	long timestamp = time(NULL);
//	timestamp = 1507384137;
	std::cout << "timestamp: " << timestamp << std::endl;
	srand (timestamp);

//	std::cout << std::endl << std::endl << std::endl;
//	std::cout << "Herzlich Willkommen zum Programm zur Erstellung des Dienstplans" << std::endl;
//	std::cout << "(c) Thorben B. Muehleder, 2017" << std::endl << std::endl;
//
//	std::cout << "Haben sie bereits die Datei info.txt auf den aktuellen Monat angepasst? (y = ja)" << std::endl;
//	std::string input;
//	std::cin >> input;
//	std::cout << std::endl;
//	if(input != "y" && input != "Y"){std::cerr << "Dann tun sie dies und starten dienstplan.sh neu" << std::endl; exit(0);}
//
//	std::cout << "Wieviele Tage hat der Monat?" << std::endl; 
//	std::cin >> days ; 
//	if(days < 28 || days > 31){std::cerr << "Keine gültige Eingabe" << std::endl; exit(0);}
//
//	std::cout << std::endl << "Welcher Wochentag ist der Monatserste?" << std::endl; 
//	std::cout << "(Mo = 0, Di = 1, Mi = 2, Do = 3, Fr = 4, Sa = 5, So = 6)" << std::endl;
//	std::cin >> wochentag_vom_ersten;
//	if(wochentag_vom_ersten < 0 || wochentag_vom_ersten > 6){std::cerr << "Keine gültige Eingabe" << std::endl; exit(0);}
//	std::cout << std::endl;


	// data of hebammen:
	std::vector<hebamme> hebammen (1);
