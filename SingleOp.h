#ifndef SINGLEOP_H
#define SINGLEOP_H

#include <string>
#include <cctype>
#include <initializer_list>
#include <vector>
#include "StringManip.h"

std::vector<int> numbersInOp(const std::string&);
std::vector<char> operatorsInOp(const std::string&);
bool hasMultDiv(const std::vector<char> &op);
int executeSingleOp(std::vector<int> numb, char op);
void performSingleOpOnVector(std::vector<int> &numb, std::vector<char> &op, const int &i);
int execute(std::vector<int>, std::vector<char>);

struct SingleOp //Holds a single operation of data. aka 5 + 5, or 20/2+5, or 3*4+2/6 Will be defined from parentheses ()
{
	SingleOp(const std::string &str) : numbers(numbersInOp(str)), op(operatorsInOp(str)) {}

	int execute() { return ::execute(numbers, op); };
private:
	std::vector<int> numbers;
	std::vector<char> op;
};


std::vector<double> numbersInOpDouble(const std::string &str);
bool hasExp(const std::vector<char> &op);
bool hasSqrt(const std::vector<char> &op);
double executeSingleOp(std::vector<double> numb, char op);
void performSingleOpOnVector(std::vector<double> &numb, std::vector<char> &op, const int &i);
double execute(std::vector<double>, std::vector<char>);

struct SingleOpDouble
{
	SingleOpDouble(const std::string &str) : numbers(numbersInOpDouble(str)), op(operatorsInOp(str)) {}

	double execute() { return ::execute(numbers, op); }
private:
	std::vector<double> numbers;
	std::vector<char> op;
};

#endif