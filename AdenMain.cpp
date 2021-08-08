#include "AdenMain.h"

#include <iostream>

int main(int argc, char** argv)
{
	AdenJSONDocument doc;

	AdenJSONParseResult result = doc.LoadFromFile("test.json");
	std::cout << result.description << std::endl;
	while (true)
	{
		std::cout << doc.Print() << std::endl;
	}

	return 0;
}