#pragma once
#include "Regex.h"
class Transition
{
public:
	Transition(int startState, Regex expr, int endState);

	int getStartState();
	int getFinalState();
	Regex getLabel();
	void setLabel(Regex label);
	
	void printTransition();

private:
	std::pair<int, Regex> m_transition;
	int m_endState;
};

