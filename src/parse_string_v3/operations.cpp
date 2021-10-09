#include "parse_string_v3/operations.h"

COperations::COperations()
{
    m_operations.push_back({ '+', this->Addition });
    m_operations.push_back({ '-', this->Subtraction });
    m_operations.push_back({ '*', this->Multiplication });
    m_operations.push_back({ '/', this->Division });
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

uint64_t COperations::GCD(uint64_t a, uint64_t b)
{
    while(b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

double COperations::Calculate(const double& a, const double& b, const char* sign)
{
    for(auto& p : m_operations)
        if(*sign == p.first && p.second != nullptr)
            return (this->*p.second)(a, b);
    return 0;
}