#include <iostream>
#include "hashmap.h"

int main()
{
	HashMap<std::string, int, StringHash> hmap;

	hmap.insert("ECE231", 5);

	std::cout << hmap["ECE231"] << std::endl;

	return 0;
}

