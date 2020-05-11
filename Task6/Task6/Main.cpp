#include <iostream>
#include <fstream>
#include "RPN.h"

std::string LoadValueFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::string value;
	if (!file)
	{
		std::cout << "Can`t open file " << fileName << std::endl;
		return value;
	}

	while (file)
	{
		std::getline(file, value);
	}

	file.close();

	if (value.empty())
	{
		std::cout << "String is empty" << std::endl;
	}
	return value;
}

void TestRNP(std::string test, bool needShowTree = false)
{
	try
	{
		auto rnp = CreateRNP(test);
		std::cout << "RNP:" << std::endl << rnp << std::endl;
		
		auto res = CalcRNP(rnp);
		std::cout << "Result: " << res << std::endl;
	}
	catch (const char* msg)
	{
		std::cout << "Error has occured: " << msg << std::endl;
	}
}

int main()
{
	std::string test1 = "2+2-5-7=";
	std::string test2 = "2+2*5-7=";
	std::string test3 = "22+42*55-7777=";
	std::string test4 = "22,55+42*55-7777=";
	std::string test5 = "-2+2-5-7=";
	std::string test6 = "-2+2-(-5-7)=";
	std::string test7 = "-2e-3+4=";
	std::string test8 = "5/(4-2)=";
	std::string test9 = "0.0000275e+07/2500000e-05=";

	std::string test = LoadValueFromFile("input.txt");
	std::cout << "Read: " << std::endl;
	std::cout << test << std::endl;

	TestRNP(test);
}
