#pragma once
#include <string>
#include <iostream>

class Regex
{
public:
	Regex(std::string expr);
	void printRegex();
	std::string getExpression();

	Regex KleeneStar();
	Regex Concatenate(Regex expression2);
	Regex Union(Regex expression2);

	Regex removeLambdas();

private:
	std::string regularExpression;
};

