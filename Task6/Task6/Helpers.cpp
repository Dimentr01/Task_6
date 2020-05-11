#include "Helpers.h"

// Функция проверяет принадлежность символа value строке str
bool CharBelongsToString(const char& value, const char* str)
{
	while (*str) // пока не \0
	{
		if (value == *str++)
			return true;
	}
	return false;
}

// Функция проверяет value на числовые операнды
bool IsDigitOperand(const char& value)
{
	if ((value == '0') || (value == '1'))
		return true;
	return false;
}

// Функция проверяет value на операторы
bool IsOperator(const char& value)
{
	if (CharBelongsToString(value, AllOperators))
		return true;
	return false;
}

// Функция проверяет value на арифметические
bool IsArithmOperatorsOperator(const char& value)
{
	if (CharBelongsToString(value, ArithmOperators))
		return true;
	return false;
}

// Фукнкция возвращает приоритет операций
int Priority(const char& value)
{
	switch (value)
	{
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

// Проверяет цифра ли символ
bool IsDigit(const char& value)
{
	if (value >= '0' && value <= '9')
		return true;
	return false;
}


// Перевод цифры char в цифру int
int CharToInt(const char& value)
{
	if (IsDigit(value))
		return value - '0';
	else return -1;
}

// Переводит цифру int в цифру char
char IntToChar(const int& value)
{
	if (value >= 0 && value <= 9)
		return char(value) + '0';
	return '-';
}

// Проверка на возможность вычисления выражение (есть или нет буквенные переменные)
bool CanEvaluateValue(const std::string& inputValue)
{
	bool wereDigitOperands = false;
	for (auto& symbol : inputValue)
	{

		if (symbol == '*' ||
			symbol == '+' ||
			symbol == '!' ||
			symbol == '(' ||
			symbol == ')')
			continue;
		if (CharBelongsToString(symbol, NonDigitOperands))
		{
			return false;
		}
		if (CharBelongsToString(symbol, DigitOperands))
			wereDigitOperands = true;
	}
	return wereDigitOperands;
}

// Функция вычисляет значение операции
double CalcOperation(const double& left, const double& right, const char& op)
{
	switch (op)
	{
	case '*':
		return left * right;
	case '/':
		if (right == 0)
			throw "Division by zero!";
		return left / right;
	case '+':
		return left + right;
	case '-':
		return left - right;
	default:
		return 0;
	}
}