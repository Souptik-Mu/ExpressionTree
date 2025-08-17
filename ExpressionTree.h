//#pragma once

#include <map>
#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <optional>
#include <typeinfo>

#include <bits/stdc++.h>

enum TravarseMode
{   PreOrder, InOrder, PostOrder, Branch };

class Token //NODE of the expression tree
{
public:     // data values
    template <typename T> Token(T Value , bool = false);

    char Const = '\0';//flag
    std::optional<char> Operator;
    std::optional<long double> Operand;
public:     //links
    std::optional<Token*> left;
    std::optional<Token*> right;
public:     // info 
    bool isOperator();
    void Show();
    //void Solve();

};

template<typename T>
inline Token::Token(T Value , bool C)
{
    if (C)
        Const = Value;
    else
    {
        if (typeid(Value) == typeid(long double))
            this->Operand = Value;
        else
            this->Operator = Value;
    }
}


class Tree
{
private:
    Token* Root;
private:
    std::vector<Token*> ParseStr(std::string);
    Token* BuildTree(std::vector<Token*>);
    void Display(Token*, const std::string& = "", bool = false);
    long double Solve(Token*);
public:
    //Tree();
    //Tree(std::string);
    bool LoadExpression(std::string);
    void Print(TravarseMode = Branch);
    long double Result();

    //~Tree();
};

// 1st er dilke no er age - thakle nebena