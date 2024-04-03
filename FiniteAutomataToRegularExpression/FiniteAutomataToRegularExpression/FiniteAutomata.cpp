#include "FiniteAutomata.h"

bool FiniteAutomata::verifyAutomata()
{
	//m_sizeQ, m_Sum, m_Delta & m_F not empty
	if (m_Q.size() == 0 || m_Sum.size() == 0 || m_Delta.size() == 0 || m_F.size() == 0)
	{
		return false;
	}
	//m_q0 is in m_Q
	auto it = std::find(m_Q.begin(), m_Q.end(), m_q0);
	if (it == m_Q.end())
	{
		return false;
	}
	//all m_F symbols are in m_Q
	for (int i = 0; i < m_F.size(); i++)
		if (std::find(m_Q.begin(), m_Q.end(), m_F[i]) == m_Q.end())
		{
			return false;
		}
	//all m_Delta symbols are in m_Q,m_Sum
	for (int i = 0; i < m_Delta.size(); i++)
		if (std::find(m_Q.begin(), m_Q.end(), std::get<0>(m_Delta[i])) == m_Q.end()
			|| std::find(m_Sum.begin(), m_Sum.end(), std::get<1>(m_Delta[i])[0]) == m_Sum.end() //modificat din char in string[0]
			|| std::find(m_Q.begin(), m_Q.end(), std::get<2>(m_Delta[i])) == m_Q.end())
		{
			return false;
		}

	return true;
}

void FiniteAutomata::printAutomata()
{
	std::cout << "Automata states:\n";
	for (int i = 0; i < m_Q.size(); i++)
		std::cout << "q" << m_Q[i] << " ";
	std::cout << std::endl;

	std::cout << "Automata accepted alphabet:\n";
	for (int i = 0; i < m_Sum.size(); i++)
		std::cout << m_Sum[i] << " ";
	std::cout << std::endl;

	std::cout << "Automata transitions:\n";
	for (int i = 0; i < m_Delta.size(); i++)
		std::cout << "(q" << std::get<0>(m_Delta[i]) << ',' << std::get<1>(m_Delta[i]) << ")=q" << std::get<2>(m_Delta[i]) << std::endl;

	std::cout << "Automata final states:\n";
	for (int i = 0; i < m_F.size(); i++)
		std::cout << 'q' << m_F[i] << ' ';
	std::cout << std::endl;
}

FiniteAutomata FiniteAutomata::readAutomata(std::string fileName)
{
	FiniteAutomata automata;
	std::ifstream file(fileName);
	
	//read states
	int size = 0;
	file >> size;
	std::vector<int> Q;
	for (int i = 0; i < size; i++)
	{
		int state = 0;
		file >> state;
		Q.push_back(state);
	}

	//

	return automata;
}
