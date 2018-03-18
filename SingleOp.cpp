#include "SingleOp.h"
#include <iostream>
#include <cmath>

std::vector<int> numbersInOp(const std::string &str) //Takes string input of a single operation, anything in parentheses, and outputs a vector of all numbers in string, seperated by non numerics
{
	std::vector<int> output;
	std::string temp = str;
	while (!temp.empty())
	{
		int val = stringToInt(temp);
		output.push_back(val);
		if (temp.begin() + std::to_string(val).length() == temp.end())
		{
			std::string temp2(temp.begin() + std::to_string(val).length(), temp.end()); 
			temp = temp2;
		}
		else
		{
			std::string temp2(temp.begin() + std::to_string(val).length() + 1, temp.end()); // +1 to get past operator
			temp = temp2;
		}
	}

	return output;
}
std::vector<char> operatorsInOp(const std::string &str)	//Takes a string, outputs a vector of all operators in it
{
	std::vector<char> output;
	for (const auto &i : str)
		if (isOperator(i))
			output.push_back(i);
	return output;
}
int executeSingleOp(std::vector<int> numb, char op)	//Takes vector of 2 numbers, performs operation
{
	switch (op)
	{
	case '*':
		return (numb[0] * numb[1]);
	case '/':
		return (numb[0] / numb[1]);
	case '+':
		return (numb[0] + numb[1]);
	case '-':
		return (numb[0] - numb[1]);
	}
}
bool hasMultDiv(const std::vector<char> &op)
{
	for (const auto &i : op)
		if (i == '*' || i == '/')
			return 1;
	return 0;
}
bool hasExp(const std::vector<char> &op)
{
	for (const auto &i : op)
		if (i == '^')
			return 1;
	return 0;
}
bool hasSqrt(const std::vector<char> &op)
{
	for (const auto &i : op)
		if (i == '$')
			return 1;
	return 0;
}
//Takes a vector of numbers, a vector of operators, and a position, and performs an operation at that position. Replaces values in original vector, and deletes operator
void performSingleOpOnVector(std::vector<int> &numb, std::vector<char> &op, const int &i)
{
	std::vector<int> tempNumbs = { numb[i], numb[i + 1] };
	numb.insert(numb.begin() + i, executeSingleOp(tempNumbs, op[i]));
	numb.erase(numb.begin() + i + 1, numb.begin() + i + 3);
	op.erase(op.begin() + i);
}
int execute(std::vector<int> numb, std::vector<char> op)	//Turns any set of numbers and operators without parentheses into a final value
{
	if (op.empty())
		return numb[0];
	for (int i = 0; i != op.size(); ++i)
	{
		if (hasMultDiv(op)) 
		{
			if (op[i] == '*' || op[i] == '/')
			{
				performSingleOpOnVector(numb, op, i);
				break;
			}
		}
		else
		{
			if (op[i] == '+' || op[i] == '-')
			{
				performSingleOpOnVector(numb, op, i);
				break;
			}
		}
	}
	return execute(numb, op);	//Recurses to find next operator
}

std::vector<double> numbersInOpDouble(const std::string &str) //Takes string input of a single operation, anything in parentheses, and outputs a vector of numbers
{
	std::vector<double> output;
	std::string temp = str;
	while (!temp.empty())
	{
		double val = stringToDouble(temp);
		output.push_back(val);
		if (temp.begin() + firstDoubleString(temp).length() == temp.end())
		{
			std::string temp2(temp.begin() + firstDoubleString(temp).length(), temp.end());
			temp = temp2;
		}
		else
		{
			std::string temp2(temp.begin() + firstDoubleString(temp).length() + 1, temp.end()); // +1 to get past operator
			temp = temp2;
		}
	}

	return output;
}

double executeSingleOp(std::vector<double> numb, char op)
{
	switch (op)
	{
	case '^':
		return pow(numb[0], numb[1]);
	case '$':
		return sqrt(numb[1]);
	case '*':
		return (numb[0] * numb[1]);
	case '/':
		return (numb[0] / numb[1]);
	case '+':
		return (numb[0] + numb[1]);
	case '-':
		return (numb[0] - numb[1]);
	}
}
//Takes a vector of numbers, a vector of operators, and a position, and performs an operation at that position. Replaces values in original vector, and deletes operator
void performSingleOpOnVector(std::vector<double> &numb, std::vector<char> &op, const int &i)
{
	std::vector<double> tempNumbs = { numb[i], numb[i + 1] };
	numb.insert(numb.begin() + i, executeSingleOp(tempNumbs, op[i]));
	numb.erase(numb.begin() + i + 1, numb.begin() + i + 3);
	op.erase(op.begin() + i);
}

double execute(std::vector<double> numb, std::vector<char> op)	//Turns any set of numbers and operators without parentheses into a final value
{
	if (op.empty())
		return numb[0];
	for (int i = 0; i != op.size(); ++i)
	{
		if (hasSqrt(op))
		{
			if (op[i] == '$')
			{
				performSingleOpOnVector(numb, op, i);
				break;
			}
		}
		else if (hasExp(op))
		{
			if (op[i] == '^')
			{
				performSingleOpOnVector(numb, op, i);
				break;
			}
		}
		else if (hasMultDiv(op))
		{
			if (op[i] == '*' || op[i] == '/')
			{
				performSingleOpOnVector(numb, op, i);
				break;
			}
		}
		else
		{
			if (op[i] == '+' || op[i] == '-')
			{
				performSingleOpOnVector(numb, op, i);
				break;
			}
		}
	}
	return execute(numb, op);	//Recurses to find next operator
}