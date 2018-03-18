#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <fstream>
#include <initializer_list>



std::istream &validate(std::istream& is, std::string &str, std::ostream& os);
void messages(unsigned);
void calculatorLoop(std::istream &is, std::string &str, std::ostream &os = std::cout);
void createFile(const std::string &str);
void createFileStructure(const std::initializer_list<const std::string> &list);
void defineReadme();
void initializeFiles();

#endif