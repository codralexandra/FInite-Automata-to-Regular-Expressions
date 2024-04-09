#include "Regex.h"

Regex::Regex(std::string expr)
{
    regularExpression = expr;
}

Regex::Regex()
{
    regularExpression = "";
}

void Regex::printRegex()
{
    std::cout << regularExpression << std::endl;
}

std::string Regex::getExpression()
{
    return regularExpression;
}

void Regex::setExpression(std::string expr)
{
    regularExpression = expr;
}

Regex Regex::KleeneStar()
{
    std::string newExpr;
    if (regularExpression.size() > 1)
    {
        newExpr = "(" + regularExpression + ")*";
    }
    else newExpr = regularExpression + "*";

    if (std::find(newExpr.begin(), newExpr.end(), '~') != newExpr.end())
    {
        auto end = std::remove(newExpr.begin(), newExpr.end(), '~');
        newExpr.erase(end, newExpr.end());
    }

    return Regex(newExpr);
}

Regex Regex::Concatenate(Regex expression2)
{
    std::string newExpr;
    
    newExpr = regularExpression + expression2.regularExpression;

    if (std::find(newExpr.begin(), newExpr.end(), '~') != newExpr.end())
    {
        auto end = std::remove(newExpr.begin(), newExpr.end(), '~');
        newExpr.erase(end, newExpr.end());
    }
    
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


bool Regex::checkWord(std::string word)
{
    std::replace(regularExpression.begin(), regularExpression.end(), '+', '|');
    std::regex regex_pattern(regularExpression);

    if (std::regex_match(word, regex_pattern))
        return true;

    return false;
}
