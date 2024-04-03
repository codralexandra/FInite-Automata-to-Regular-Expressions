#include <iostream>
#include "FiniteAutomata.h"
#include "Regex.h"

int main()
{
    FiniteAutomata automata;
    automata = automata.readAutomata("automata.in");
    automata.printAutomata();

    /*Regex expr1("b*a");
    Regex expr2("a+bb*a");
    Regex expr3("~b*a");
    
    expr2 = expr2.KleeneStar();
    expr1 = expr1.Concatenate(expr2);
    expr1.printRegex();

    expr3 = expr3.removeLambdas();
    expr3.printRegex();*/
}

