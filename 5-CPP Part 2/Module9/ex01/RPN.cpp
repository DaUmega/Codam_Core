#include "RPN.hpp"

RPN::RPN(void)
{}

RPN::~RPN(void)
{}

RPN::RPN(RPN const &other)
{
    (void)(other);
}

RPN &RPN::operator=(RPN const &other)
{
	(void)(other);
    return *this;
}

bool    RPN::operatorCheck(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int    RPN::calculate(const std::string &input)
{
    int                 first;
    int                 second;
    int                 ret;
    std::stack<int>     stack;
    std::string         token;
    std::stringstream   ss(input);

    while (ss >> token)
    {
        if (isdigit(token[0]))
            stack.push(atoi(token.c_str()));
        else if (operatorCheck(token[0]))
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            first = stack.top();
            stack.pop();
            second = stack.top();
            stack.pop();
            ret = operation(token[0], first, second);
            stack.push(ret);
        }
        else
            throw std::runtime_error("Error");
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top();
}

int     RPN::operation(char op, int first, int second)
{
    switch(op)
    {
        case '+':
            return second + first;
        case '-':
            return second - first;
        case '*':
            return second * first;
        case '/':
            if (first == 0)
                throw std::runtime_error("Error");
            return second / first;
        default:
            throw std::runtime_error("Error");
    }
}
