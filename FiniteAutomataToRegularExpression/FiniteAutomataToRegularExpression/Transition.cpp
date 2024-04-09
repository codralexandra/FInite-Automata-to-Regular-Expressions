#include "Transition.h"

Transition::Transition(int startState, Regex expr, int endState) : m_transition(startState, expr), m_endState(endState)
{ }

int Transition::getStartState()
{
	return m_transition.first;
}

int Transition::getFinalState()
{
	return m_endState;
}

Regex Transition::getLabel()
{
	return m_transition.second;
}

void Transition::setLabel(Regex label)
{
	m_transition.second = label;
}

void Transition::printTransition()
{
	std::cout << "(" << m_transition.first << ", " << m_transition.second.getExpression() << ")->" << m_endState << "\n";
}
