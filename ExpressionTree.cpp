#include "ExpressionTree.h"

static std::map<char, int> PrecedenceOf = { {'\0',-1} , {'-',1} , {'+',1} , {'*',2} , {'/',2} , {'^',3} };


void Token::Show()
{
    if (Operand.has_value())
        std::cout << "(" << Operand.value() << ")";
    if (Operator.has_value())
        std::cout << "[" << Operator.value() << "]";
    if (Const != '\0')
        std::cout << " " << Const << " ";
        
}

bool Token::isOperator()
{
    return Operator.has_value();
}



std::vector<Token*> Tree::ParseStr(std::string Expr)
{
    bool ret = true;
    std::string numstr;
    long double tempn;
    std::vector<Token*> TokenList;

    //TokenList.empty();
    for (int i = 0; i <= Expr.size(); i++)
    {char w = Expr[i];
        
        if (isdigit(w) || w == '.' )
        {
            numstr += w;
            if (!isdigit(Expr[i + 1]) && Expr[i + 1] != '.')
            {
                tempn = std::strtold(numstr.c_str(), NULL);
                numstr = "";
                TokenList.push_back(new Token(tempn));
            }
        }
        else if (ispunct(w))
            TokenList.push_back(new Token(w));
        else
            ret = false;
    }
    return TokenList;
}

Token* Tree::BuildTree(std::vector<Token*> TokenList)
{
    std::stack<Token*> OperatorStk;
    std::stack<Token*> OperandStk;

    for (auto token : TokenList)
    {
        if (token->isOperator())
        {
            if (token->Operator.value() == '(')
                OperatorStk.push(token);
            else if (token->Operator.value() == ')')
            {
                while (!OperatorStk.empty() && OperatorStk.top()->Operator.value() != '(')
                {
                    Token* root = OperatorStk.top(); OperatorStk.pop();
                    root->right = OperandStk.top(); OperandStk.pop();
                    root->left = OperandStk.top(); OperandStk.pop();
                
                    OperandStk.push(root);
                }
                if(!OperatorStk.empty())///////////////////first sonkha ta kheye felche jodi bracket thake
                    OperatorStk.pop();
            }
            else
            {
                while (!OperatorStk.empty() && PrecedenceOf[token->Operator.value_or('\0')] <= PrecedenceOf[OperatorStk.top()->Operator.value_or('\0')])
                {
                    Token* root = OperatorStk.top(); OperatorStk.pop();
                    root->right = OperandStk.top(); OperandStk.pop(); 
                    root->left = OperandStk.top(); OperandStk.pop();

                    OperandStk.push(root);
                }
                OperatorStk.push(token);
            }
        }
        else
            OperandStk.push(token);
    }
    while (!OperatorStk.empty())
    {
        Token* root = OperatorStk.top(); OperatorStk.pop();
        root->right = OperandStk.top(); OperandStk.pop();
        root->left = OperandStk.top(); OperandStk.pop();

        OperandStk.push(root);
    }

    return OperandStk.top();
}

void Tree::Display(Token* r, const std::string& DalPala, bool isDoga)
{
    std::string blank = "     ";
    std::string line = { char(954) ,' ' , ' ', ' ', ' ' }; //│
    std::string upp = { char(969), char(973),char(973) ,char(973) };//╔─── 
    std::string down = { char(968), char(973),char(973) ,char(973) }; //└─── 
    if (r != nullptr)
    {
        if(r->right.has_value())
            Display(r->right.value(), DalPala + (!isDoga ? line : blank), true);

        std::cout << DalPala;
        std::cout << (isDoga ? upp : down);
        r->Show(); std::cout << std::endl;

        if(r->left.has_value())
            Display(r->left.value(), DalPala + (isDoga ? line : blank), false);
    }
}

long double Tree::Solve(Token* r)
{
    if (r != nullptr)
    {
        if (!r->isOperator())
            return r->Operand.value_or(0);
        else
        {
            long double Lo, Ro;
            if (r->left.has_value())
                Lo = Solve(r->left.value());
            if (r->right.has_value())
                Ro = Solve(r->right.value());
           
            switch (r->Operator.value())
            {
            case '^':   
                return pow(Lo, Ro);
                break;
            case '/':   
                return (Lo / Ro);
                break;
            case '*':   
                return (Lo * Ro);
                break;
            case '+':   
                return (Lo + Ro);
                break;
            case '-':   
                return (Lo - Ro);
                break;
            default:    
                return 0;
                break;
            }
        }
    }
    return 0;
}

bool Tree::LoadExpression(std::string Expr)
{
    //Expr.erase(std::remove_if(Expr.begin(), Expr.end(), ::isspace)); //remove al spaces
   
    //check blanced bracket
    
    Root = BuildTree(ParseStr(Expr));       
    return true;

    
}

void Tree::Print(TravarseMode m)
{
    switch (m)
    {
    case PreOrder:
        break;
    case InOrder:
        break;
    case PostOrder: 
        break;
    case Branch:    Display(Root);
        break;
    default:
        break;
    }
}

long double Tree::Result()
{
    return Solve(Root);
}