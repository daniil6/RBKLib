#ifndef COPERATIONS_H
#define COPERATIONS_H

#include <map>

class COperations
{
private:
    typedef double (COperations::*iFunc)(const double&, const double&);

    std::map<char, iFunc> m_operations;

    double Addition(const double& a, const double& b);
    double Subtraction(const double& a, const double& b);
    double Multiplication(const double& a, const double& b);
    double Division(const double& a, const double& b);
    double Max(const double& a, const double& b);
    double Min(const double& a, const double& b);

public:
    COperations();
    ~COperations();

    double Calculate(const double& a, const double& b, const char* sign);
};

#endif // COPERATIONS_H
