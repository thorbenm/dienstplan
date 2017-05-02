#include <iostream>

struct hebamme{
	std::string name;
	char kuerzel;
		hebamme(std::string name1, char kuerzel1){
		name = name1;
		kuerzel = kuerzel1;
		}
};

hebamme heb1("heb1", '1');

int main(){
	std::cout << "hello world";
	return 0;
}
