#include "UserInterface.h"
#include "StringManip.h"
#include "SingleOp.h"
#include "OperatorData.h"
#include <cctype>
#include <stdexcept>
#include "FullOp.h"

extern const std::initializer_list<const std::string> fileNames;
extern const std::string inputFileString, outputFileString, readmeFileString;

std::istream &validate(std::istream& is, std::string &str, std::ostream& os)
{
	getline(is, str);
	convertParenth(str);
	removeSpaces(str);
	convertSqrt(str);
	removeOtherChars(str);
	toLowerCase(str);
	try
	{
		if (is.eof())
			throw std::exception("End of File");
		if (str == "exit")
		{
			throw std::exception("Exiting...");
		}
		if (str.empty())
			throw std::invalid_argument("No visible input");
		if (onlyOperators(str))
			throw std::invalid_argument("Must have numbers");
		if (startsOrEndsInOperator(str))
			throw std::invalid_argument("Can't start or end with an operator");
		if (numbParenthL(str) != numbParenthR(str))
			throw std::invalid_argument("Must have matching number of parentheses");
		for (const auto &i : str)
			if (!(isdigit(i) || isOperator(i) || isParenth(i) || i == '.'))
				throw std::invalid_argument("Invalid Input");
	}
	catch (std::invalid_argument err)
	{
		os << err.what() << std::endl << "Please enter another input: " << std::flush;	//Originally intended as cerr
		validate(is, str, os);
	}
	catch (std::exception err)
	{
		os << err.what() << std::endl;	//Originally intended as cerr
		is.setstate(std::ios::failbit);
	}

	

	if (is.good())
	{
		addParenthesesSqrt(str);
		addLeadingMult(str);
		addLeadingForSqrt(str);
	}
	
	return is;
}

void messages(unsigned input)
{
	switch (input)
	{
	case 0:
		std::cout << "Type 'Exit' to exit this calculator program.\nRead readme.txt for more information." << std::endl;
	}
}

void calculatorLoop(std::istream &is, std::string &input, std::ostream &os)
{
	while (validate(is, input, os))
	{
		if (isInt(input) && !hasDiv(input) && !hasExpOrSqrt(input))
		{
			FullOp equation(input);
			os << input << " = " << equation.execute() << std::endl;
		}
		else
		{
			FullOpDouble equation(input);
			resetSqrtString(input);
			os << input << " = " << equation.execute() << std::endl;
		}
	}
}
void createFile(const std::string &str)
{
	std::fstream file(str);
	if (!file.is_open())
	{
		file.clear();
		file.open(str, std::ios::out);
	}
}
void createFileStructure(const std::initializer_list<const std::string> &list)
{
	for (const auto &i : list)
		createFile(i);
}
void defineReadme()
{
	std::ofstream readMe(readmeFileString);
	readMe
		<< "Author: Stefan Mada\n"
		<< "Last Build Date : " << __DATE__ << std::endl << std::endl
		<< "This is a simple calculator program.\n"
		<< "This calculator allows addition, subtraction, multiplication, division, and exponents.\n"
		<< "You can ask for square root by typing sqrt.\n"
		<< "This program follows the standard order of operations.You can (and should) use parentheses.\n" << std::endl
		<< "This program also will perform math on the " << inputFileString << " file, and output results to" << outputFileString << std::endl
		<< "Commands are separated by line." << std::flush;
}
void initializeFiles()
{
	createFileStructure(fileNames);
	defineReadme();
}