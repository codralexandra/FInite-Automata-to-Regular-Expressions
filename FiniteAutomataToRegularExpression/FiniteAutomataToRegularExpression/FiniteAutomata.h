#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class FiniteAutomata
{
public:
	bool verifyAutomata();
	void printAutomata();
	FiniteAutomata readAutomata(std::string fileName);
private:
	std::vector<int> m_Q;
	std::vector<char> m_Sum;
	std::vector<std::tuple<int, std::string, int>> m_Delta;
	uint16_t m_q0;
	std::vector<int> m_F;
};

