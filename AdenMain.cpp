#include "AdenMain.h"

#include <iostream>

int main(int argc, char** argv)
{
	AdenJSONDocument doc;

	//while (true)
	{
		AdenJSONParseResult result = doc.LoadFromString("[\"1\", \"2\", \"a\", \"{}\"]");
		std::cout << result.description << std::endl;
		//std::cout << doc.Print() << std::endl;
		doc.ArrayForEach([](int idx, AdenJSONNode& node) {
			std::cout << node.SetStringValue("name") << std::endl;
			return true;
			});
		std::cout << "====================================" << std::endl;
		doc.ArrayForEach([](int idx, AdenJSONNode& node) {
			std::cout << node.GetStringValue() << std::endl;
			return true;
			});
	}

	return 0;
}