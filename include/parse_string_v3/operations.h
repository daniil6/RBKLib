#ifndef COPERATIONS_H
#define COPERATIONS_H

#include <stdint.h>
#include <vector>

class COperations
{
private:
    typedef double (COperations::*iFunc)(const double&, const double&);

    std::vector<std::pair<char, iFunc>> m_operations;

    /**
     * @brief Addition between a and b
     * @param a - left value
     * @param b - right value
     * @return result addition
     */
    double Addition(const double& a, const double& b);

    /**
     * @brief Subtraction between a and b
     * @param a - left value
     * @param b - right value
     * @return result subtraction
     */
    double Subtraction(const double& a, const double& b);

    /**
     * @brief Multiplication between a and b
     * @param a - left value
     * @param b - right value
     * @return result multiplication
     */
    double Multiplication(const double& a, const double& b);

    /**
     * @brief Division between a and b
     * @param a - left value
     * @param b - right value
     * @return result division
     */
    double Division(const double& a, const double& b);

public:
    COperations();
    ~COperations();

    /**
     * @brief Calculation between a and b depending on sign
     * @param a - left value
     * @param b - right value
     * @param sign - action sign ( '+' '-' '*' '/' )
     * @return result calculation
     */
    double Calculate(const double& a, const double& b, const char* sign);

    /**
     * @brief Greatest common divisor between a and b
     * @param a - left value
     * @param b - right value
     * @return result greatest common divisor
     */
    static uint64_t GCD(uint64_t a, uint64_t b);

    /**
     * @brief Max between a and b
     * @param a - left value
     * @param b - right value
     * @return result max
     */
    static double Max(const double& a, const double& b);

    /**
     * @brief Min between a and b
     * @param a - left value
     * @param b - right value
     * @return result min
     */
    static double Min(const double& a, const double& b);
};

#endif // COPERATIONS_H
