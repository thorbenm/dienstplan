
	std::cout << std::endl << "Dienstplan wird erstellt, bitte warten..."; 

	int shifts = days * 2; //hardcoded to two shifts
std::vector<int> rota(shifts);
std::vector<int> wrong_counter_all(shifts);
//used to choose best rota:
//std::vector<int> best_rota(shifts);
//double best_stddev = shifts;

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
	
	//adjust max_dienste:
	for (int j = 0 ; j < hebammen.size() ; j++){
		hebammen.at(j).max_dienste--;
	}
	int sum_dienste = 0;
	for (int j = 0 ; j < hebammen.size() ; j++){
		sum_dienste+=hebammen.at(j).max_dienste;
	}
	while(sum_dienste > shifts){
		//max_max_dienste:
		int max_max_dienste = 0;
		for (int j = 0 ; j < hebammen.size() ; j++){
			if(max_max_dienste < hebammen.at(j).max_dienste){
				max_max_dienste = hebammen.at(j).max_dienste;
			}
		}
		//subtract:
		for (int j = 0 ; j < hebammen.size() ; j++){
			if (max_max_dienste == hebammen.at(j).max_dienste){
				hebammen.at(j).max_dienste--;
			}
		}
		//recalculate sum:
		sum_dienste = 0;
		for (int j = 0 ; j < hebammen.size() ; j++){
			sum_dienste+=hebammen.at(j).max_dienste;
		}
	}
	// add again:
	for (int j = 0 ; j < hebammen.size() ; j++){
		hebammen.at(j).max_dienste++;
	}








		ALLNEW: wrong_counter = 0;
		for(int j = 0; j < hebammen.size() ; j ++){
			hebammen.at(j).dienste = 0;
			hebammen.at(j).nachtdienste = 0;
		}
			for(int j = 0; j<rota.size();j++){
			int rnd = 0;
//			rnd = rand() % hebammen.size(); 	
//			NEWRANDOM:rnd++;	
//			rnd = rnd % hebammen.size(); 	
//			
//			weighted random:
			NEWRANDOM:
			int sum_of_weights = 0;
			int num_of_weights = hebammen.size();
			std::vector<int> weights(num_of_weights);
			for( int jj = 0; jj < num_of_weights; jj++){
				sum_of_weights += hebammen.at(jj).max_dienste;
				weights.at(jj) = hebammen.at(jj).max_dienste;
			}
			int weighted_rnd = rand() % sum_of_weights; 	
			for(int jj=0; jj<num_of_weights; jj++) {
				if(weighted_rnd < weights.at(jj)){
					rnd = jj;
					break;
				}
			 	weighted_rnd -= weights.at(jj);
			}
//			NEWRANDOM:rnd = rand() % hebammen.size(); 	
			for(int jj = 0; jj < wrong_counter_all.size() ; jj++){
				if (wrong_counter_all.at(jj) > 1000000){
					std::cerr << "Es konnte niemand fuer den ";
					if(j % 2 == 1){
						std::cerr << "Nacht";
					}else{
						std::cerr << "Tag";
					}
					std::cerr << "dienst am " << (j+2) / 2 << ". gefunden werden!" << std::endl;
					std::cerr << "Bitte passen Sie die Daten an!" << std::endl;
					exit(0);
				}
			}
	
			//criteria:
			//not day and night after one another:
	
				if(j>0){
					if(rota.at(j-1) == rnd){
						wrong_counter++;
						wrong_counter_all.at(j)++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
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
	//		//new try, which spreads it better
//				if(j>10){
//					int cc = 0;
//					int check_for= 10;
					for (int jj = j - check_for; jj < j; jj++){
						if(rnd == rota.at(jj)){
							cc++;
						}
					}
					if(cc > 2){
						wrong_counter++;
						wrong_counter_all.at(j)++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
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
							wrong_counter_all.at(j)++;
							if(wrong_counter < max_wrong){
								goto NEWRANDOM;
							}else{
								goto ALLNEW;
							}
						}
					}
				}
			//check for freiwuensche
				for (int fr = 0; fr < hebammen.at(rnd).rota_exceptions.size(); fr++){
					if(hebammen.at(rnd).rota_exceptions.at(fr) == j){
						wrong_counter++;
						wrong_counter_all.at(j)++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
							goto ALLNEW;
						}
					}
				}				
			// exceeded number ob max dienste:
				if(hebammen.at(rnd).dienste + 1 > hebammen.at(rnd).max_dienste){			
						wrong_counter++;
						wrong_counter_all.at(j)++;
						if(wrong_counter < max_wrong){
							goto NEWRANDOM;
						}else{
							goto ALLNEW;
						}
					}
			// nachtschicht:
				if(j % 2 == 1){
					if( (double) hebammen.at(rnd).nachtdienste + 1.0  > ( (double) hebammen.at(rnd).max_dienste + 1.0 ) / 2.0){			
							wrong_counter++;
							wrong_counter_all.at(j)++;
							if(wrong_counter < max_wrong){
								goto NEWRANDOM;
							}else{
								goto ALLNEW;
							}
						}
					}

			//all correct:
			rota.at(j) = rnd;
			// count dienste:
			hebammen.at(rnd).dienste++;
			if(j % 2 == 1){
				hebammen.at(rnd).nachtdienste++;
			}
		}
	
		//count dienste:
//		for(int j = 0; j < hebammen.size(); j++){
//			for(int i = 0; i < rota.size(); i++){
//				if(rota.at(i) == j){
//					hebammen.at(j).dienste++;
//					if(i % 2 == 1){
//						hebammen.at(j).nachtdienste++;
//					}
//				}
//			}
//		}
//		//check for max_dienste and nachtdienste
//		for(int j = 0; j < hebammen.size(); j++){
//			if(hebammen.at(j).max_dienste > -1){
//				if(hebammen.at(j).max_dienste < hebammen.at(j).dienste){
//					//std::cerr << "all new at dineste count" << std::endl;
//					goto ALLNEW;
//				}
//			}
//			if(hebammen.at(j).nachtdienste > (hebammen.at(j).dienste + 1) / 2 + strictness){
//				//std::cerr << "all new at nachtdienste" << std::endl;
//				goto ALLNEW;
//			}
//		}
	
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
//		if (stddev < best_stddev){
//			best_rota = rota;
//			best_stddev = stddev;
//		}

//		//progressbar
//		if(step % (iterations / 10) == 0){
//			std::cout << step * 100 / iterations << "% ... " << std::flush; 
//		}
//		if(step == iterations - 1){
//			std::cout << "100%" << std::endl;
//		}
//	}

//	//count dienste for rota:
//	for(int j = 0; j < hebammen.size(); j++){
//		hebammen.at(j).dienste = 0;
//		hebammen.at(j).nachtdienste = 0;
//	}
//	for(int j = 0; j < hebammen.size(); j++){
//		for(int i = 0; i < rota.size(); i++){
//			if(rota.at(i) == j){
//				hebammen.at(j).dienste++;
//				if(i % 2 == 1){
//					hebammen.at(j).nachtdienste++;
//				}
//			}
//		}
//	}

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
		if(j % 7 == 6 - wochentag_vom_ersten){
			std::cout << "|";
		}
	}
	std::cout << std::endl;

	//spacer:
	for(int j = 0; j < max_length + 2 + 1 + 10 + 3*days + 4;j++){ 
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
			if(rota.at(j) == i){
				std::cout << "T";
			}else if(rota.at(j+1) == i){
				std::cout << "N";
			}else{
				std::cout << " ";
			}
			if(j % 14 == 12 - 2*wochentag_vom_ersten){
				std::cout << "|";
			}
		}
		//spacer:
		std::cout << std::endl;
		if(i<hebammen.size()-1){
			for(int j = 0; j < max_length + 2 + 1 + 10 + 3*days + 4;j++){ 
				std::cout<< "-";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
//	std::cout << hebammen.at(0).nachtdienste << std::endl;
	return 0;
}
