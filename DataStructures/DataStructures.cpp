#include <iostream>

#include "map.h"

int main()
{
	Map map;
	
	std::string key = "name";

	map.add(key, "TBKJ");
	std::cout << "key = " << key << ", Value = " << map.get(key) << ", Map size = " << map.size() << std::endl;

	map.add(key, "TECHPROG");
	std::cout << "key = " << key << ", Value = " << map.get(key) << ", Map size = " << map.size() << std::endl;

	map.remove("TECHPROG");
	std::cout << "key = " << key << ", Value = " << map.get(key) << ", Map size = " << map.size() << std::endl;

	map.remove(key);
	try {
		std::cout << "key = " << key << ", Value = " << map.get(key) << ", Map size = " << map.size() << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	if (map.contains(key)) {
		std::cout << "key = " << key << ", Value = " << map.get(key) << ", Map size = " << map.size() << std::endl;
	}
	else {
		std::cout << "No value associated to key = " << key << ", Map size = " << map.size() << std::endl;
	}
}
