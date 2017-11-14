#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <unistd.h>

int iterations = 100;
int max_wrong = 1000;
int wrong_counter = 0;

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
//	timestamp = 1508315890;
	std::cout << "timestamp: " << timestamp << std::endl;
	srand (timestamp);

	// data of hebammen:
	std::vector<hebamme> hebammen (1);
	//	
	// Herzlich Wilkommen zum Dienstplan-Programm v1.0
	// (c) Thorben B. Muehleder, 2017	
	//
	// Bitte beachten Sie, dass Wochentage im gesamten Programm
	// als Zahl angegeben werden muessen.
	// 
	// Montag     = 0	
	// Dienstag   = 1	
	// Mittwoch   = 2	
	// Donnerstag = 3	
	// Freitag    = 4	
	// Samstag    = 5	
	// Sonntag    = 6	
	//
	// Navigieren Sie mit den Pfeiltasten (nicht mit der Maus)
	// und passen Sie die Daten auf den aktuellen Monat an:
	//
	// Wieviele Tage hat der Monat?
	days = 22;
	//
	// Welcher Wochentag ist der erste des Monats? (Zahl)
	wochentag_vom_ersten = 2;
	//
	// Um die Daten zu speichern und den Diensplan zu generieren
	// drücken Sie Ctrl x, dann y, dann Enter.
	//
	// Sollten Probleme auftreten bitte den timestamp des
	// falschen Dienstplans notieren.

	hebammen.back().name ="Jenifer Melzer";
	hebammen.back().freiwuensche_tag = {3,4,15,16,17};
	hebammen.back().freiwuensche_nacht = {14,15,16,17};
	hebammen.back().freiwuensche_wochentag_tag = {2};
	hebammen.back().freiwuensche_wochentag_nacht = {1,2};
	hebammen.back().max_dienste = 14;

	hebammen.resize(hebammen.size()+1);

	hebammen.back().name = "Anne Hartmann";
	hebammen.back().freiwuensche_tag = {14};
	hebammen.back().freiwuensche_nacht = {14};
	hebammen.back().freiwuensche_wochentag_tag = {0};
	hebammen.back().freiwuensche_wochentag_nacht = {6,0};
	hebammen.back().max_dienste = 14;

//	hebammen.resize(hebammen.size()+1);
//
//	hebammen.back().name = "Simone Krug";
//	hebammen.back().freiwuensche_tag = {};
//	hebammen.back().freiwuensche_nacht = {};
//	hebammen.back().freiwuensche_wochentag_tag = {2};
//	hebammen.back().freiwuensche_wochentag_nacht = {1,2};
//	hebammen.back().max_dienste = 14;
//
	hebammen.resize(hebammen.size()+1);

	hebammen.back().name = "Katharina Lange";
	hebammen.back().freiwuensche_tag = {2,16,17,22};
	hebammen.back().freiwuensche_nacht = {1,2,16,22};
	hebammen.back().freiwuensche_wochentag_tag = {3};
	hebammen.back().freiwuensche_wochentag_nacht = {2,3};
	hebammen.back().max_dienste = 14;

	hebammen.resize(hebammen.size()+1);

	hebammen.back().name = "Luica Bertram";
	hebammen.back().freiwuensche_tag = {9,10,11,12,13,14,15,16,17,18,19,20,21,22};
	hebammen.back().freiwuensche_nacht = {8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
	hebammen.back().freiwuensche_wochentag_tag = {1};
	hebammen.back().freiwuensche_wochentag_nacht = {0,1};
	hebammen.back().max_dienste = 14;

//	hebammen.resize(hebammen.size()+1);
//
//	hebammen.back().name = "Lisa Gessner";
//	hebammen.back().freiwuensche_tag = {};
//	hebammen.back().freiwuensche_nacht = {};
//	hebammen.back().freiwuensche_wochentag_tag = {3};
//	hebammen.back().freiwuensche_wochentag_nacht = {2,3};
//	hebammen.back().max_dienste = 14;

	hebammen.resize(hebammen.size()+1);

	hebammen.back().name = "Shirin Ansari";
	hebammen.back().freiwuensche_tag = {9,10,11,12};
	hebammen.back().freiwuensche_nacht = {9,10,11};
	hebammen.back().freiwuensche_wochentag_tag = {4};
	hebammen.back().freiwuensche_wochentag_nacht = {3,4};
	hebammen.back().max_dienste = 7;

	std::cout << std::endl << "Dienstplan wird erstellt, bitte warten..."; 

	int shifts = days * 2; //hardcoded to two shifts
std::vector<int> rota(shifts);
//used to choose best rota:
std::vector<int> best_rota(shifts);
double best_stddev = shifts;

	//transfer userfriendly freiwuensche data to rota_exceptions:
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
			next_push_back += 2 * hebammen.at(heb).freiwuensche_wochentag_tag.at(fr) ; 
			next_push_back -= 2 * wochentag_vom_ersten; 
			while (next_push_back < shifts){
				hebammen.at(heb).rota_exceptions.push_back(next_push_back);
				next_push_back+=14; }
		}

		for (int fr = 0; fr < hebammen.at(heb).freiwuensche_wochentag_nacht.size(); fr++){
			next_push_back = -14;
			next_push_back += 2 * hebammen.at(heb).freiwuensche_wochentag_nacht.at(fr) ; 
			next_push_back -= 2 * wochentag_vom_ersten; 
			next_push_back += 1;
			while (next_push_back < shifts){
				hebammen.at(heb).rota_exceptions.push_back(next_push_back);
				next_push_back+=14;
			}
		}

	}

	std::cout << std::endl;

	//generate rota:
	for(int step = 0; step < iterations ; step++){

		ALLNEW:for(int j = 0; j<rota.size();j++){
			int rnd = 0;
		//	rnd = rand() % hebammen.size(); 	
		//	NEWRANDOM:rnd++;	
		//	rnd = rnd % hebammen.size(); 	

			NEWRANDOM:rnd = rand() % hebammen.size(); 	
	
			//criteria:
			//not day and night after one another:
	
				if(j>0){
					if(rota.at(j-1) == rnd){
						wrong_counter++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
							wrong_counter = 0;
							goto ALLNEW;
						}
					}
				}
	
			//no more than three same shifts after one another
	
	//			if(j>6){
	//				if(rnd == rota.at(j-2) && rnd == rota.at(j-4) && rnd == rota.at(j-6)){
	//					wrong_counter++;
	//					if(wrong_counter < max_wrong){
	//						goto NEWRANDOM;
	//					}else{
	//						wrong_counter = 0;
	//						goto ALLNEW;
	//					}
	//				}
	//			}

			//no more than 3 shifts in four days
				if(j>6){
					int cc = 0;
					int check_for;
					if(j == 6){
						check_for = 6;
					}else{
						check_for = 7;
					}
					for (int jj = j - check_for; jj < j; jj++){
						if(rnd == rota.at(jj)){
							cc++;
						}
					}
					if(cc > 2){
						wrong_counter++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
							wrong_counter = 0;
							goto ALLNEW;
						}
					}
				}

			// no more than 2 times night after one another
			 	if(j % 2 == 1){
					int counter = 0;
					for(int jj = j-1; jj >= 0; jj--){
						if(rota.at(jj) == rnd){
							if(jj % 2 == 1){
								counter++;
							//	std::cout << jj << " " << std::flush;
							//	usleep(100000);
							}else{
								break;
							}
						}
						if(counter > 1){
							wrong_counter++;
							if(wrong_counter < max_wrong){
								goto NEWRANDOM;
							}else{
								wrong_counter = 0;
								goto ALLNEW;
							}
						}
					}
				}
			//check for freiwuensche
				for (int fr = 0; fr < hebammen.at(rnd).rota_exceptions.size(); fr++){
					if(hebammen.at(rnd).rota_exceptions.at(fr) == j){
						wrong_counter++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
							wrong_counter = 0;
							goto ALLNEW;
						}
					}
				}				
	
			rota.at(j) = rnd;
		}
	
		//count dienste:
		for(int j = 0; j < hebammen.size(); j++){
			hebammen.at(j).dienste = 0;
			hebammen.at(j).nachtdienste = 0;
		}
		for(int j = 0; j < hebammen.size(); j++){
			for(int i = 0; i < rota.size(); i++){
				if(rota.at(i) == j){
					hebammen.at(j).dienste++;
					if(i % 2 == 1){
						hebammen.at(j).nachtdienste++;
					}
				}
			}
		}
		//check for max_dienste and nachtdienste
		for(int j = 0; j < hebammen.size(); j++){
			if(hebammen.at(j).max_dienste > -1){
				if(hebammen.at(j).max_dienste < hebammen.at(j).dienste){
					goto ALLNEW;
				}
			}
			if(hebammen.at(j).nachtdienste > (hebammen.at(j).dienste + 1) / 2){
				goto ALLNEW;
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
	
		//choose best rota
		if (stddev < best_stddev){
			best_rota = rota;
			best_stddev = stddev;
		}

		//progressbar
		if(step % (iterations / 10) == 0){
			std::cout << step * 100 / iterations << "% ... " << std::flush; 
		}
		if(step == iterations - 1){
			std::cout << "100%" << std::endl;
		}
	}

	//count dienste for best rota:
	for(int j = 0; j < hebammen.size(); j++){
		hebammen.at(j).dienste = 0;
		hebammen.at(j).nachtdienste = 0;
	}
	for(int j = 0; j < hebammen.size(); j++){
		for(int i = 0; i < best_rota.size(); i++){
			if(best_rota.at(i) == j){
				hebammen.at(j).dienste++;
				if(i % 2 == 1){
					hebammen.at(j).nachtdienste++;
				}
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
//	std::cout << hebammen.at(0).nachtdienste << std::endl;
	return 0;
}
