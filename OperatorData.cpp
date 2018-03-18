#include <string>
#include "OperatorData.h"

unsigned numbParenthL(const std::string &str) //Returns number of left ( parentheses
{
	unsigned cnt = 0;
	for (const auto &i : str)
		if (i == '(')
			++cnt;
	return cnt;
}
unsigned numbParenthR(const std::string &str) //Returns number of right ) parentheses
{
	unsigned cnt = 0;
	for (const auto &i : str)
		if (i == ')')
			++cnt;
	return cnt;
}
unsigned numbOperators(const std::string &str) //Returns number of arithmetic operators
{
	unsigned cnt = 0;
	for (const auto &i : str)
		if (i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == '$')
			++cnt;
	return cnt;
}