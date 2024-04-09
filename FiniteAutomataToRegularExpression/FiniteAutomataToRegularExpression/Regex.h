#pragma once
#include <string>
#include <iostream>

#include <algorithm>
#include <regex>

class Regex
{
public:
	Regex(std::string expr);
	Regex();
	void printRegex();
	std::string getExpression();

	void setExpression(std::string expr);

	Regex KleeneStar();
	Regex Concatenate(Regex expression2);
	Regex Union(Regex expression2);

	Regex removeLambdas();

	bool checkWord(std::string word);

private:
	std::string regularExpression;
};

