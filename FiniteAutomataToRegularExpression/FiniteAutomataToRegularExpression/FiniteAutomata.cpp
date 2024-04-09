#include "FiniteAutomata.h"

//bool FiniteAutomata::verifyAutomata()
//{
//	//m_sizeQ, m_Sum, m_Delta & m_F not empty
//	if (m_Q.size() == 0 || m_Sum.size() == 0 || m_Delta.size() == 0 || m_F.size() == 0)
//	{
//		return false;
//	}
//	//m_q0 is in m_Q
//	auto it = std::find(m_Q.begin(), m_Q.end(), m_q0);
//	if (it == m_Q.end())
//	{
//		return false;
//	}
//	//all m_F symbols are in m_Q
//	for (int i = 0; i < m_F.size(); i++)
//		if (std::find(m_Q.begin(), m_Q.end(), m_F[i]) == m_Q.end())
//		{
//			return false;
//		}
//	//all m_Delta symbols are in m_Q,m_Sum
//	for (int i = 0; i < m_Delta.size(); i++)
//		if (std::find(m_Q.begin(), m_Q.end(), std::get<0>(m_Delta[i])) == m_Q.end()
//			|| std::find(m_Sum.begin(), m_Sum.end(), std::get<1>(m_Delta[i])[0]) == m_Sum.end() //modificat din char in string[0]
//			|| std::find(m_Q.begin(), m_Q.end(), std::get<2>(m_Delta[i])) == m_Q.end())
//		{
//			return false;
//		}
//
//	return true;
//}

void FiniteAutomata::printAutomata()
{
	std::cout << "Automata states:\n";
	for (int i = 0; i < m_Q.size(); i++)
		std::cout << m_Q[i] << " ";
	std::cout << std::endl;

	std::cout << "Automata start state:" << m_q0 << std::endl;

	std::cout << "Automata accepted alphabet:\n";
	for (int i = 0; i < m_Sum.size(); i++)
		std::cout << m_Sum[i] << " ";
	std::cout << std::endl;

	std::cout << "Automata transitions:\n";
	for (int i = 0; i < m_Delta.size(); i++)
		m_Delta[i].printTransition();

	std::cout << "Automata final states:\n";
	for (int i = 0; i < m_F.size(); i++)
		std::cout << m_F[i] << ' ';
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
	automata.m_Q = Q;

	file >> size;
	automata.m_q0 = size;

	//read accepted alphabet
	file >> size;
	std::vector<char> Sum;
	for (int i = 0; i < size; i++)
	{
		char symbol;
		file >> symbol;
		Sum.push_back(symbol);
	}
	automata.m_Sum = Sum;

	//read final states
	file >> size;
	std::vector<int> F;
	for (int i = 0; i < size; i++)
	{
		int finalState = 0;
		file >> finalState;
		F.push_back(finalState);
	}
	automata.m_F = F;

	//read transitions
	file >> size;
	std::vector<Transition> Delta;
	for (int i = 0; i < size; i++)
	{
		int startState = 0;
		std::string transitionLabel;
		int endState = 0;
		file >> startState >> transitionLabel >> endState;
		Transition transition(startState, transitionLabel, endState);
		Delta.push_back(transition);
	}
	automata.m_Delta = Delta;

	return automata;
}

std::string FiniteAutomata::getRegularExpression()
{
	std::string regularExpression;

	//1. Merge transitions from the same 2 states
	mergeTransitions();

	//2. Make the automata uniform
	uniformAutomata();

	//3. State elimination algorithm
	stateElimination();

	//4. Get regular expression from the remaining transition label
	regularExpression = m_Delta[0].getLabel().getExpression();

	return regularExpression;
}

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& pair) const {
		auto hash1 = std::hash<T1>{}(pair.first);
		auto hash2 = std::hash<T2>{}(pair.second);
		return hash1 ^ hash2;
	}
};

void FiniteAutomata::mergeTransitions()
{
	std::unordered_map<std::pair<int, int>, std::vector<std::string>, pair_hash> mergedTransitions;

	for (Transition& transition : m_Delta)
	{
		int startState = transition.getStartState();
		int endState = transition.getFinalState();
		std::string regex = transition.getLabel().getExpression();

		auto key = std::make_pair(startState, endState);
		auto it = mergedTransitions.find(key);

		if (it != mergedTransitions.end())
		{
			it->second.push_back(regex);
		}
		else
		{
			mergedTransitions[key] = { regex };
		}
	}

	m_Delta.clear();

	for (const auto& pair : mergedTransitions)
	{
		int startState = pair.first.first;
		int endState = pair.first.second;

		std::string mergedRegex;
		for (const auto& regex : pair.second)
		{
			if (!mergedRegex.empty())
				mergedRegex += "|";
			mergedRegex += regex;
		}
		if(std::find(mergedRegex.begin(),mergedRegex.end(),'|')!=mergedRegex.end())
			mergedRegex = "(" + mergedRegex + ")";

		Transition mergedTransition(startState, Regex(mergedRegex), endState);
		m_Delta.push_back(mergedTransition);
	}
}

void FiniteAutomata::uniformAutomata()
{
	int newStartState = 0;
	int newFinalState = m_Q.size() + 1;

	m_Q.push_back(newStartState);
	m_Q.push_back(newFinalState);

	m_Delta.push_back(Transition(newStartState, Regex("~"), m_q0));
	m_q0 = newStartState;

	for (int i = 0; i < m_F.size(); i++)
	{
		m_Delta.push_back(Transition(m_F[i], Regex("~"), newFinalState));
	}
	m_F.clear();
	m_F.push_back(newFinalState);
	std::sort(m_Q.begin(), m_Q.end());
}

void FiniteAutomata::stateElimination()
{
	std::unordered_map<std::pair<int, int>, std::vector<std::string>, pair_hash> transitions;
	for (Transition& transition : m_Delta)
	{
		int startState = transition.getStartState();
		int endState = transition.getFinalState();
		std::string regex = transition.getLabel().getExpression();

		auto key = std::make_pair(startState, endState);

		transitions[key] = { regex };
	}

	while (m_Q.size() != 2)
	{
		//chose a random transition that is not the start sate or the end state
		int size = m_Q.size();

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<std::size_t> dist(1, size - 2);
		std::size_t randomIndex = dist(gen);
		int k = m_Q[randomIndex];


		std::pair<int, int> key = std::make_pair(k, k);

		//retrieve the value associated with the key
		std::vector<std::string> kkLabel = transitions[key];

		Regex kk;
		if (kkLabel.size() != 0)
			kk.setExpression(kkLabel[0]);

		//create kk_label*
		if (kk.getExpression().size() != 0)
			kk = kk.KleeneStar();

		//for all pairs of (p,q) states for wich there is a direct path through state k (p->k->q)
		std::vector<std::pair<int, int>> validStates = getKStates(k);

		//for each pair (p,q) create a new transition between them based on the following formula:
		//new_pq_label = pq_label + concat(pk_label,kk_label*,kq_label)

		for (std::pair<int, int> pair : validStates)
		{
			int p = pair.first;
			int q = pair.second;

			std::vector<std::string > pqLabel = transitions[std::make_pair(p, q)];
			std::vector<std::string > pkLabel = transitions[std::make_pair(p, k)]; //nu vede update urile facute jos
			std::vector<std::string > kqLabel = transitions[std::make_pair(k, q)];

			Regex pq;
			Regex pk;
			Regex kq;

			if (pqLabel.size() != 0)
				pq.setExpression(pqLabel[0]);

			if (pkLabel.size() != 0)
				pk.setExpression(pkLabel[0]);

			if (kqLabel.size() != 0)
				kq.setExpression(kqLabel[0]);

			Regex newLabel = kk;

			if (kq.getExpression().size() != 0)
				newLabel = newLabel.Concatenate(kq);
			if (pk.getExpression().size() != 0)
			{
				pk = pk.Concatenate(newLabel);
				newLabel = pk;
			}
			if (pq.getExpression().size() != 0)
			{
				pq = pq.Union(newLabel);
				newLabel = pq;
			}

			addTransition(Transition(p, newLabel, q));
		}

		//remove the k state and all transitions that start or end with it

		std::vector<Transition> newDelta;

		for (int i = 0; i < m_Delta.size(); i++)
		{
			if (m_Delta[i].getStartState() == k || m_Delta[i].getFinalState() == k)
				continue;
			else newDelta.push_back(m_Delta[i]);
		}
		m_Delta = newDelta;

		std::unordered_map<std::pair<int, int>, std::vector<std::string>, pair_hash> tempTransitions;

		for (Transition& transition : m_Delta)
		{
			int startState = transition.getStartState();
			int endState = transition.getFinalState();
			std::string regex = transition.getLabel().getExpression();

			auto key = std::make_pair(startState, endState);

			tempTransitions[key] = { regex };
		}
		transitions = tempTransitions;
		auto it = std::find(m_Q.begin(), m_Q.end(), k);
		m_Q.erase(it);
	}
}

std::vector<std::pair<int,int>> FiniteAutomata::getKStates(int k)
{
	std::vector<std::pair<int,int>> kStates;

	for (Transition t1 : m_Delta)
	{
		for (Transition t2 : m_Delta)
		{
			if ((t1.getFinalState() == k && t1.getStartState() != k) && (t2.getStartState() == k && t2.getFinalState() != k))
				kStates.push_back(std::make_pair(t1.getStartState(), t2.getFinalState()));
		}
	}

	return kStates;
}

void FiniteAutomata::addTransition(Transition transition)
{
	//check if transition already exists, if so, only modify the label
	//if not, add it to m_Delta
	bool exists = false;
	for (auto& t : m_Delta)
	{
		if (t.getStartState() == transition.getStartState() && t.getFinalState() == transition.getFinalState())
		{
			t.setLabel(transition.getLabel());
			exists = true;
			break;
		}
	}
	if (!exists)
		m_Delta.push_back(transition);
}