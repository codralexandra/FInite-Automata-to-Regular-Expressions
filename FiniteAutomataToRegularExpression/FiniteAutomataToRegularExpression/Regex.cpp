#include "Regex.h"

Regex::Regex(std::string expr)
{
    regularExpression = expr;
}

void Regex::printRegex()
{
    std::cout << regularExpression << std::endl;
}

std::string Regex::getExpression()
{
    return regularExpression;
}

Regex Regex::KleeneStar()
{
    std::string newExpr;
    if (regularExpression.size() > 1)
    {
        newExpr = "(" + regularExpression + ")*";
    }
    else newExpr = regularExpression + "*";

    return Regex(newExpr);
}

Regex Regex::Concatenate(Regex expression2)
{
    std::string newExpr;
    
    newExpr = regularExpression + expression2.regularExpression;
    
    return Regex(newExpr);
}

Regex Regex::Union(Regex expression2)
{
    std::string newExpr;

    newExpr = regularExpression + "+" + expression2.regularExpression;

    return Regex(newExpr);
}

Regex Regex::removeLambdas()
{
    std::string newExpr = regularExpression;

    size_t pos = 0;
    while ((pos = newExpr.find_first_of('~', pos)) != std::string::npos) {
        newExpr.erase(pos, 1);
    }

    return Regex(newExpr);
}
