#ifndef OPERATORDATA_H
#define OPERATORDATA_H

#include <string>

unsigned numbParenthL(const std::string&); //Declared above so they can be used in OpData
unsigned numbParenthR(const std::string&);
unsigned numbOperators(const std::string&);

struct OpData //Stores data on number of parentheses and operators in a string
{
	OpData() = default;
	OpData(std::string str) : parenthL(::numbParenthL(str)), parenthR(::numbParenthR(str)), oper(::numbOperators(str)) {}

	unsigned numbOperators() { return oper; }
	unsigned numbParenthL() { return parenthL; }
	unsigned numbParenthR() { return parenthR; }
	bool hasOp()
	{
		if (parenthL > 0 || parenthR > 0 || oper > 0)
			return 1;
		else
			return 0;
	}
	bool hasParenth()
	{
		if (parenthL > 0 && parenthR > 0)
			return 1;
		else
			return 0;
	}

private:
	unsigned parenthL = 0, parenthR = 0,  oper = 0;
};




#endif
