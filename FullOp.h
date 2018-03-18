#ifndef FULLOP_H
#define FULLOP_H

#include <string>
#include "OperatorData.h"

unsigned firstRParenth(const std::string&);
unsigned matchingLParenth(const std::string&s);

struct FullOp
{
	FullOp(const std::string &str) : equation(str), operatorData(str) {}

	int execute();
private:
	OpData operatorData;
	std::string equation;
};



struct FullOpDouble
{
	FullOpDouble(const std::string &str) : equation(str), operatorData(str) {}

	double execute();
private:
	OpData operatorData;
	std::string equation;
};

#endif
