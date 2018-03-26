#include "StringManip.h"
#include <string>
#include <cctype>
#include <iostream>

extern const std::initializer_list<const std::string> mathConstants;
extern const std::vector<std::string> importantStr;
extern const std::string pi;
extern const std::string e;

bool hasMathConstants(const std::string &str)
{
	for (const auto &constant : mathConstants)
	{
		size_t lengthC = constant.length();
		if (!(str.length() >= lengthC))
			continue;
		for (size_t i = lengthC - 1; i != str.length(); ++i)
		{
			std::string temp = str.substr(i - lengthC + 1, lengthC);
			if (temp == constant)
			{
				return 1;
			}
		}
	}
	return 0;
}
void removeOtherChars(std::string &str) //Removes all spaces in a string
{
	std::string temp;
	if (!hasMathConstants(str) || str == "exit")
	{
		for (const auto &c : str)
		{
			if (isalnum(c) || c == '(' || c == ')' || isOperator(c) || c == '.')
				temp += c;
		}
	}
	else
	{
		unsigned cnt = 0;
		for (std::string::iterator i = str.begin(); i != str.end(); ++i, ++cnt)
		{
			if (isdigit(*i) || *i == '(' || *i == ')' || isOperator(*i) || *i == '.')
			{
				temp += *i;
				continue;
			}
			for (const auto &compareVal : importantStr)
			{
				size_t lengthC = compareVal.length();
				if (str.length() < lengthC || cnt + lengthC > str.length())
					continue;
				std::string temp2(i, i + lengthC);
				if (temp2 == compareVal)
				{
					temp += temp2;
					cnt += (lengthC - 1);
					i += (lengthC - 1);
					break;
				}

			}
		}
		std::cout << temp << std::endl;
	}
	str = temp;
}

void convertParenth(std::string &str) //Converts diff types of parentheses to ( and )
{
	std::string temp;
	for (auto &c : str)
	{
		switch (c)
		{
		case '{':
			c = '(';
			break;
		case '[':
			c = '(';
			break;
		case '}':
			c = ')';
			break;
		case ']':
			c = ')';
			break;
		}
	}
}

int stringToInt(const std::string &str)	//Starts at 0 and goes to first non numerical
{
	std::string::size_type pos = 1;
	for (const auto &i : str)
		if (isdigit(i))
			++pos;
	return std::stoi(str, &pos);
}

void toLowerCase(std::string& str)
{
	for (auto &i : str)
		i = tolower(i);
}

void removeAmpersands(std::string &str)
{
	std::string temp;
	for (auto &i : str)
		if (i != '&')
			temp += i;
	str = temp;
}

bool onlyOperators(const std::string& str)
{
	bool val = 1;
	for (const auto &i : str)
		if (!isOperator(i))
			val = 0;
	return val;
}
void addLeadingMult(std::string &str)	// Adds leading multiplication symbol fo parentheses IE 3(2) = 3*2 or (3)(2) = (3)*(2)
{
	for (auto first = str.begin(), second = str.begin()+1; second != str.end(); ++first, ++second)
	{
		if (isdigit(*first) && (*second == '(') || (*first == ')' && *second == '('))
		{
			second = str.insert(second, '*');	//Another iterator error that is basically the same as in resetSqrt
			first = second - 1;					//You need to redefine the iterators to keep their validity
		}
	}
}
void removeParentheses(std::string &str)
{
	std::string temp;
	for (const auto &i : str)
		if (!isParenth(i))
			temp += i;
	str = temp;
}
bool startsOrEndsInOperator(const std::string &str)
{
	std::string temp = str;
	removeParentheses(temp);
	std::string::const_iterator begin = temp.begin(), end = temp.end();
	if (isOperator(*begin) || isOperator(*--end))
		if(!(*begin == '$'))
			return 1;
	return 0;
}
bool isInt(const std::string &str)
{
	for (const auto &i : str)
		if (i == '.')
			return 0;
	return 1;
}

double stringToDouble(const std::string &str)	//Starts at 0 and goes to first non numerical
{
	std::string::size_type pos = 1;
	for (const auto &i : str)
		if (isdigit(i) || i == '.')
			++pos;
	return std::stod(str, &pos);
}
std::string firstDoubleString(const std::string &str)	//Starts at 0, and outputs a string until a non-numeric, exluding '.' ; Itended to find a double from 0 to first non-numeric
{
	std::string temp;
	for (int i = 0; isdigit(str[i]) || str[i] == '.'; ++i, temp += str[i]);
	return temp;
}
bool hasDiv(const std::string &str)
{
	for (const auto &i : str)
		if (i == '/')
			return 1;
	return 0;
}
void convertSqrt(std::string &str)	//Recursive function that finds all instances of "sqrt" in a string, replacing it with $ operator
{
	std::string match = "sqrt";
	if (!(str.length() > 4))
		return;
	for (int i = 3; i != str.length(); ++i)
	{
		std::string temp = str.substr(i - 3, 4);
		if (temp == match)
		{
			str.replace(i - 3, 4, "$");
			convertSqrt(str);
			break;
		}
	}

}
void removeSpaces(std::string &str)
{
	std::string temp;
	for (auto i : str)
		if (!isspace(i))
			temp += i;
	str = temp;
}
bool hasExpOrSqrt(const std::string &str)
{
	for (const auto &i : str)
		if (i == '^' || i == '$')
			return 1;
	return 0;
}
void addLeadingForSqrt(std::string &str)	//Adds leading multipliers for sqrts, IE 3$2 = 3*1$2, $4 = 1$2, 4+$2 = 4+1$2, $$$3 = 1$1$1$3. Necessary due to how math is done
{
	unsigned cnt = 1;
	for (auto first = str.begin(), second = str.begin() + 1; second != str.end(); ++first, ++second, ++cnt)
	{
		if (isdigit(*first) && (*second == '$') && *first != '1')
		{
			str.insert(cnt, "*1");
			first += 2, second += 2, cnt += 2;
		}
		else if (*first == '$' && first == str.begin())
		{
			str.insert(first, '1');
			++first, ++second, ++cnt;
		}
		else if ((isOperator(*first) || isParenth(*first)) && (*second == '$'))
		{
			str.insert(cnt, "1");
			++first, ++second, ++cnt;
		}
		if (*first == '$' && *second == '$')
		{
			str.insert(second, '1');
		}
	}
}
void resetSqrtString(std::string &str)	//When outputing to user, turns $ symbol back into sqrt string
{
	size_t cnt = 1;
	for (auto first = str.begin(), second = str.begin() + 1; second != str.end(); ++first, ++second, ++cnt)
	{
		if (*first == '1' && *second == '$')
		{
			first = str.erase(first, second + 1);
			second = first + 1;

			str.insert(cnt-1, "sqrt");
			cnt += 2;
			first = str.begin() + cnt - 1, second = str.begin() + cnt;
		//	first += 2;
		//	second += 2;
		//	cnt += 2;
		//	Above was original code, but it was fucking invalidating the iterators
		//	(only after I added something else mind you, so I was looking for the error in the wrong place)
		//	So I redefine them to make them valid throughout >:(
		}
	}
}
std::string::const_iterator posAfterFirstNumber(const std::string &str, std::string::iterator iter)
{
	for (auto iter2 = iter + 1; iter2 != str.end() && (!isdigit(*iter) || isdigit(*iter2)); ++iter, ++iter2);
	return ++iter;
}
void addParenthesesSqrt(std::string &str)
{
	for(auto i1 = str.begin(); (i1+1) != str.end(); ++i1)
		if (*i1 == '$' && *(i1+1) == '$')
		{
			str.insert(posAfterFirstNumber(str, (i1+1)), ')');
			i1 = str.insert((i1+1), '(');
		}
}
void replaceStrWithStr(std::string &str, const std::string &replaced, const std::string &replacer)
{
	const size_t lengthR = replaced.length();
	if (!(str.length() >= lengthR))
		return;
	for (size_t i = lengthR-1; i != str.length(); ++i)
	{
		std::string temp = str.substr(i - lengthR + 1, lengthR);
		if (temp == replaced)
		{
			str.replace(i - lengthR + 1, lengthR, replacer);
			replaceStrWithStr(str, replaced, replacer);
			break;
		}
	}
}
void convertMathConstansts(std::string &str)
{
	replaceStrWithStr(str, "e", e);
	replaceStrWithStr(str, "pi", pi);
}
void addParenthesesMathConstants(std::string &str)
{
	std::string temp;
	unsigned cnt = 0;
	for (std::string::iterator i = str.begin(); i != str.end(); ++i, ++cnt)
	{
		if (isdigit(*i) || *i == '(' || *i == ')' || isOperator(*i) || *i == '.')
		{
			temp += *i;
			continue;
		}
		for (const auto &compareVal : mathConstants)
		{
			size_t lengthC = compareVal.length();
			if (str.length() < lengthC || cnt + lengthC > str.length())
				continue;
			std::string temp2(i, i + lengthC);
			if (temp2 == compareVal)
			{
				if (i != str.begin() && i + lengthC != str.end() && *(i - 1) == '(' && *(i + lengthC) == ')')
				{
					temp += temp2;
					cnt += (lengthC - 1);
					i += (lengthC - 1);
				}
				else
				{
					temp += "(" + temp2 + ")";
					cnt += (lengthC - 1);
					i += (lengthC - 1);
				}
				break;
			}

		}
	}
	str = temp;
}