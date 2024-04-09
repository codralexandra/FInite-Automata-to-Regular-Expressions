#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <unordered_map>
#include <random>
#include "Transition.h"
#include <algorithm>

class FiniteAutomata
{
public:
	//bool verifyAutomata();
	void printAutomata();
	FiniteAutomata readAutomata(std::string fileName);
	std::string getRegularExpression();
private:
	std::vector<int> m_Q;
	std::vector<char> m_Sum;
	std::vector<Transition> m_Delta;
	uint16_t m_q0;
	std::vector<int> m_F;

public: //helper functions for the regular expression algorithm (make private after testing)
	void mergeTransitions();
	void uniformAutomata();
	void stateElimination();
	std::vector<std::pair<int,int>> getKStates(int k);
	void addTransition(Transition transition);
};

