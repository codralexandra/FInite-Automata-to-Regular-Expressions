#include "Transition.h"

Transition::Transition(int startState, Regex expr, int endState) : m_transition(startState, expr), m_endState(endState)
{ }

void Transition::printTransition()
{
	std::cout << "(" << m_transition.first << ", " << m_transition.second.getExpression() << ")->" << m_endState << "\n";
}
