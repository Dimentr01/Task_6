#pragma once
#include <string>

static const char* AllOperands = "0123456789,.e";

static const char* DigitOperands = "01";

static const char* NonDigitOperands = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char IllegalValue = '-';

static const char* ArithmOperators = "+-*/";

static const char* AllOperators = "+-*/()";

// Функция проверяет принадлежность символа value строке str
bool CharBelongsToString(const char& value, const char* str);

// Функция проверяет value на числовые операнды
bool IsDigitOperand(const char& value);

// Функция проверяет value на операторы
bool IsOperator(const char& value);

// Функция проверяет value на арифметические
bool IsArithmOperatorsOperator(const char& value);

// Фукнкция возвращает приоритет операций
int Priority(const char& value);

// Проверяет цифра ли символ
bool IsDigit(const char& value);

// Перевод цифры char в цифру int
int CharToInt(const char& value);

// Переводит цифру int в цифру char
char IntToChar(const int& value);

// Проверка на возможность вычисления выражение (есть или нет буквенные переменные)
bool CanEvaluateValue(const std::string& inputValue);

// Функция вычисляет значение операции
double CalcOperation(const double& left, const double& right, const char& op);
