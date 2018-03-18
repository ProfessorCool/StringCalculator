#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <initializer_list>
#include "StringManip.h"
#include "OperatorData.h"
#include "SingleOp.h"
#include "FullOp.h"
#include "UserInterface.h"

using std::cin; using std::cout; using std::cerr; using std::endl; using std::string; using std::vector; using std::ifstream; using std::ofstream;

extern const std::initializer_list<const std::string> fileNames{ "input.txt", "output.txt", "readme.txt" };	
//First must be input file, second must be output file, third must be readme file
extern const string inputFileString(*fileNames.begin()), outputFileString(*(fileNames.begin() + 1)), readmeFileString(*(fileNames.begin()+2));
//Defines strings from above initializer list, which is used to create files

int main()
{
	initializeFiles();	//Checks for existence of all files, and creates them if they don't exist

	string input; 
	ifstream inputFile(inputFileString);
	ofstream outputFile(outputFileString);
	
	calculatorLoop(inputFile, input, outputFile);	//Performs calculations for files

	messages(0);	//Simple message

	calculatorLoop(cin, input);	//Performs calculations on user input

	return EXIT_SUCCESS;
}