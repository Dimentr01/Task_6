#include "RPN.h"
#include "Helpers.h"
#include "Stack.hpp"


double ParseNumber(const std::string& stringNumber)
{
	double number = atof(stringNumber.c_str());
	return number;
}

// Функция создает обратную польскую запись по алгоритму сортировочной станции Дейкстры
std::string CreateRNP(const std::string& inputString)
{
	if (inputString.empty())
		return inputString;

	if (inputString[inputString.length() - 1] != '=')
		throw "Error! There isn`t \"=\" sign";
		
	std::string resultString;
	auto stackChar = new Stack<char>;
	stackChar = nullptr;
	std::string number;

	char last_elem = 'z';
	for (auto& symbol : inputString)
	{
		// - в начале строки
		if (symbol == '-' && last_elem == 'z')
			number += symbol;
		// - после скобки
		else if (symbol == '-' && last_elem == '(')
			number += symbol;
		// - после e
		else if(symbol == '-' && last_elem == 'e')
			number += symbol;
		else if(symbol =='+' && last_elem == 'e')
			number += symbol;
		else if (CharBelongsToString(symbol, AllOperands))
		{
			if (symbol == ',')
				number += '.';
			else
			{
				number += symbol;
			}
			// resultString += symbol;
		}
		else if (IsOperator(symbol))
		{
			// было число
			if (!number.empty())
			{
				resultString += number + " ";
				number.clear();
			}
			
			if (symbol == '(')
			{
				StackPush(&stackChar, symbol);
			}
			else if (symbol == ')')
			{
				while (true)
				{
					if (StackIsEmpty(stackChar))
						throw "Error! There isn`t the ( in the stack";

					const auto tempElem = StackTop(stackChar);
					StackPop(&stackChar);
					if (tempElem == '(')
						break;
					
					resultString += tempElem;
					resultString += " ";
				}
			}
			else if (CharBelongsToString(symbol, ArithmOperators))
			{
				while (true)
				{
					if (StackIsEmpty(stackChar))
						break;
					const auto tempElem = StackTop(stackChar);
					if (Priority(tempElem) >= Priority(symbol))
					{
						resultString += tempElem;
						resultString += " ";
						StackPop(&stackChar);
					}
					else break;
				}
				StackPush(&stackChar, symbol);
			}
		}
		last_elem = symbol;
	}

	// было число
	if (!number.empty())
	{
		resultString += number;
		if (!StackIsEmpty(stackChar))
			resultString += " ";
		number.clear();
	}

	while (!StackIsEmpty(stackChar))
	{
		const auto tempElem = StackTop(stackChar);
		StackPop(&stackChar);
		if (CharBelongsToString(tempElem, AllOperands))
			throw "Error! There are operands in the stack";
		if (tempElem == '(' || tempElem == ')')
			throw "Error! There are parenthesis in the stack";
		
		resultString += tempElem;
		resultString += " ";
	}

	// удаляем правый пробел
	size_t lastSpace = resultString.find_last_not_of(' ');
	return resultString.substr(0, lastSpace + 1);
}

// Функция вычисляет значение выражения по обратной польской нотации
double CalcRNP(const std::string& inputRNP)
{
	auto stackX = new Stack<double>;
	stackX = nullptr;

	if (inputRNP.empty())
		return 0;
	
	size_t spaceCurrent = 0;
	size_t spaceNext = inputRNP.find_first_of(' ');
	while(spaceNext != std::string::npos)
	{
		auto substr = inputRNP.substr(spaceCurrent, spaceNext - spaceCurrent);
		// возможно оператор
		if (substr.length() == 1)
		{
			if (IsArithmOperatorsOperator(substr[0]))
			{
				auto right = StackTop(stackX);
				StackPop(&stackX);
				auto left = StackTop(stackX);
				StackPop(&stackX);

				StackPush(&stackX, CalcOperation(left, right, substr[0]));
			}
			// эх. не оператор
			else
			{
				double number = ParseNumber(substr);
				StackPush(&stackX, number);
			}
		}
		else
		{
			double number = ParseNumber(substr);
			StackPush(&stackX, number);
		}
		
		
		spaceCurrent = spaceNext + 1;
		spaceNext = inputRNP.find_first_of(' ', spaceCurrent);
	}
	// последний символ должен быть оператор
	auto substr = inputRNP.substr(spaceCurrent, spaceNext - spaceCurrent);
	if (!IsArithmOperatorsOperator(substr[0]))
		throw "Error in RPN";
	
	auto right = StackTop(stackX);
	StackPop(&stackX);
	auto left = StackTop(stackX);
	StackPop(&stackX);

	return CalcOperation(left, right, substr[0]);
}
