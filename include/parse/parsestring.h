#ifndef CPARSESTRING_H
#define CPARSESTRING_H

#include <string>

#include "operations.h"
#include "sign.h"
#include "type.h"

struct TParseResult {
    NumeralTree* numeralTree = nullptr;
    StringTree* stringTree = nullptr;
    double value = 0;
};

class CParseString
{
private:
    int m_numberentries;

    CSign* m_sign;
    CPlusMinus m_plusminus;
    CTimeDivid m_timedivid;
    std::string m_previois;

    COperations m_operations;
    double m_data;
    double* m_pdata;

    void Process(StringTree*& node);
    void Calculate(NumeralTree* node);
    void DeleteTree(StringTree* stringTree, NumeralTree* numeralTree);
    void ConvertAndLink(StringTree* in_node, NumeralTree*& out_node);

public:
    CParseString();
    ~CParseString();

    void Make(std::string formula, TParseResult& result);
    void DeleteParseResult(TParseResult& result);
    int GetNumberEntries();
};

#endif // CPARSESTRING_H