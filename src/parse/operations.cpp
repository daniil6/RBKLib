#include "parse/operations.h"

COperations::COperations()
{
    m_operations.insert(std::make_pair<char, iFunc>('+', this->Addition));
    m_operations.insert(std::make_pair<char, iFunc>('-', this->Subtraction));
    m_operations.insert(std::make_pair<char, iFunc>('*', this->Multiplication));
    m_operations.insert(std::make_pair<char, iFunc>('/', this->Division));
    m_operations.insert(std::make_pair<char, iFunc>('>', this->Max));
    m_operations.insert(std::make_pair<char, iFunc>('<', this->Min));
}

COperations::~COperations()
{
}

double COperations::Addition(const double& a, const double& b)
{
    return a + b;
}

double COperations::Subtraction(const double& a, const double& b)
{
    return a - b;
}

double COperations::Multiplication(const double& a, const double& b)
{
    return a * b;
}

double COperations::Division(const double& a, const double& b)
{
    if(b != 0)
        return a / b;
    else
        return 0;
}

double COperations::Max(const double& a, const double& b)
{
    if(a > b)
        return a;
    else
        return b;
}

double COperations::Min(const double& a, const double& b)
{
    if(a < b)
        return a;
    else
        return b;
}

double COperations::Calculate(const double& a, const double& b, const char* sign)
{
    for(auto& p : m_operations)
        if(*sign == p.first && p.second != nullptr)
            return (this->*p.second)(a, b);
    return 0;
}
