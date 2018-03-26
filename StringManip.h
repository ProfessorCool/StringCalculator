#ifndef STRINGMANIP_H
#define STRINGMANIP_H

#include <string>
#include <vector>


bool hasMathConstants(const std::string &str);
void removeOtherChars(std::string&); 
void convertParenth(std::string &);

inline bool isOperator(const char &i)
{
	if (i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == '$')
		return 1;
	return 0;
}
inline bool isParenth(const char &i)
{
	if (i == '(' || i == ')')
		return 1;
	return 0;
}

int stringToInt(const std::string &str);
void toLowerCase(std::string&);
void removeAmpersands(std::string&);
bool onlyOperators(const std::string&);
void addLeadingMult(std::string&);
void removeParentheses(std::string&);
bool startsOrEndsInOperator(const std::string&);
bool isInt(const std::string&);
double stringToDouble(const std::string &str);
std::string firstDoubleString(const std::string&);
bool hasDiv(const std::string &str);
void convertSqrt(std::string &str);
void removeSpaces(std::string &str);
bool hasExpOrSqrt(const std::string &str);
void addLeadingForSqrt(std::string &str);
void resetSqrtString(std::string &str);
std::string::const_iterator posAfterFirstNumber(const std::string &str, std::string::iterator iter);
void addParenthesesSqrt(std::string &str);
void replaceStrWithStr(std::string &str, const std::string &replaced, const std::string &replacer);
void convertMathConstansts(std::string &str);
void addParenthesesMathConstants(std::string &str);
#endif