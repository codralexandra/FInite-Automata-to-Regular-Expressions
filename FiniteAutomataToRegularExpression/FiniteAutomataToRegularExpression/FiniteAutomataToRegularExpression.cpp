#include <iostream>
#include "FiniteAutomata.h"
#include "Regex.h"

int main()
{
    FiniteAutomata automata;
    automata = automata.readAutomata("automata.in");
    automata.printAutomata();

    std::cout << std::endl;

    Regex regularExpr = automata.getRegularExpression();

    std::cout << "Regular expression: ";
    regularExpr.printRegex();

    //tests:
    //(pt al doilea exemplu imi accepta cuv vid doar pt unele expresii for some reason)
    std::string word = "";
    if(regularExpr.checkWord(word))
        std::cout<<"True";

}

