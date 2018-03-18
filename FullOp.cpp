#include "FullOp.h"
#include "SingleOp.h"


unsigned firstRParenth(const std::string &str)
{
	unsigned cnt = 0;
	for (const auto &i : str)
	{
		if (i == ')')
			return cnt;
		else
			++cnt;
	}
	return 0;
}
unsigned matchingLParenth(const std::string &str)
{
	unsigned cnt = firstRParenth(str);
	for (; cnt >= 0 && str[cnt] != '('; --cnt);
	return cnt;
}

int execute(std::string str, OpData oper)	//Takes a string, and performs a full operation on it. Recurses. Stops when no operators left.
{
	if (!oper.hasOp() || (str[0] == '-' && oper.numbOperators() == 1))
		return stoi(str);
	std::string oneOpInit;
	if (oper.hasParenth())
		oneOpInit.assign(str, matchingLParenth(str) + 1, firstRParenth(str) - matchingLParenth(str) - 1);
	else
		oneOpInit = str;

	SingleOp oneOp(oneOpInit);
	if (oper.hasParenth())
	{
		str.insert(firstRParenth(str) + 1, std::to_string(oneOp.execute()));
		str.erase(str.begin() + matchingLParenth(str), str.begin() + firstRParenth(str) + 1);
	}
	else
		str = std::to_string(oneOp.execute());

	OpData operNext(str);
	
	return execute(str, operNext);
}
int FullOp::execute()
{
	return ::execute(equation, operatorData);
}

double executeDouble(std::string str, OpData oper)
{
	if (!oper.hasOp() || (str[0] == '-' && oper.numbOperators() == 1))
		return stod(str);
	std::string oneOpInit;
	if (oper.hasParenth())
		oneOpInit.assign(str, matchingLParenth(str) + 1, firstRParenth(str) - matchingLParenth(str) - 1);
	else
		oneOpInit = str;

	SingleOpDouble oneOp(oneOpInit);
	if (oper.hasParenth())
	{
		str.insert(firstRParenth(str) + 1, std::to_string(oneOp.execute()));
		str.erase(str.begin() + matchingLParenth(str), str.begin() + firstRParenth(str) + 1);
	}
	else
		str = std::to_string(oneOp.execute());

	OpData operNext(str);

	return executeDouble(str, operNext);
}
double FullOpDouble::execute()
{
	return ::executeDouble(equation, operatorData);
}