#ifndef CSIGN_H
#define CSIGN_H

#include <utility>

class CSign
{
private:
    typedef std::pair<char, char> Signs;
    Signs m_sign;

public:
    CSign(char first, char second)
    {
        m_sign = std::make_pair(first, second);
    }
    virtual ~CSign() {};

    char first()
    {
        return m_sign.first;
    };

    char second()
    {
        return m_sign.second;
    };
};

class CPlusMinus : public CSign
{
public:
    CPlusMinus()
        : CSign('+', '-') {};
    ~CPlusMinus() {};
};

class CTimeDivid : public CSign
{
public:
    CTimeDivid()
        : CSign('*', '/') {};
    ~CTimeDivid() {};
};

#endif // CSIGN_H