#include <iostream>

#include "ExpressionTree.h"

int main()
{
    std::string p;
    Tree exp;

    std::cout << "Enter a Expression :";
    std::cin >> p ;

    exp.LoadExpression(p);
    exp.Print();
    
    std::cout << "Solved result : " << exp.Result();
}