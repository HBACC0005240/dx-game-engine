#include <iostream>
#include <unordered_map>

typedef std::unordered_map<int, int> INTMAP;
typedef std::pair<int, INTMAP> IPAIR;

int _1main() {

	INTMAP intmap;
	IPAIR int1 = IPAIR(1,12244);

	intmap.insert({ {1,123},{2,123456} });
	return 0;
}