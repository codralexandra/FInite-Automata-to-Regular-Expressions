#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include "Transition.h"

class FiniteAutomata
{
public:
	bool verifyAutomata();
	void printAutomata();
	FiniteAutomata readAutomata(std::string fileName);
	std::string getRegularExpression();
private:
	std::vector<int> m_Q;
	std::vector<char> m_Sum;
	std::vector<Transition> m_Delta;
	uint16_t m_q0;
	std::vector<int> m_F;

private: //helper functions for the regular expression algorithm
	void removeMultipleTransitions();
};

