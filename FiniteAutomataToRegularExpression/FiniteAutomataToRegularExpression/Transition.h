#pragma once
#include "Regex.h"
class Transition
{
public:
	Transition(int startState, Regex expr, int endState);
	
	void printTransition();

private:
	std::pair<int, Regex> m_transition;
	int m_endState;
};

