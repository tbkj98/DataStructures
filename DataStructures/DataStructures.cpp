#include <iostream>

#include "map.h"
#include "string.h"

void test_map();
void test_string();

int main()
{
	test_string();
}

void test_string() {
	tbkj::string str = "abcdefgh";
	std::cout << str << std::endl;

	tbkj::string str1("ABCDEFGH");
	std::cout << str1 << std::endl;

	auto str2 = str + " " + str1;
	std::cout << str2 << std::endl;

	if (str == str1) {
		std::cout << "Equal" << std::endl;
	}
	else {
		std::cout << "Not equal" << std::endl;
	}
}


void test_map() {
	tbkj::Map map;

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
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	if (map.contains(key)) {
		std::cout << "key = " << key << ", Value = " << map.get(key) << ", Map size = " << map.size() << std::endl;
	}
	else {
		std::cout << "No value associated to key = " << key << ", Map size = " << map.size() << std::endl;
	}
}