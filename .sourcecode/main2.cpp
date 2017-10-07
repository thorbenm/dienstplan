
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
			next_push_back += 2 * hebammen.at(heb).freiwuensche_wochentag_nacht.at(fr) ; 
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