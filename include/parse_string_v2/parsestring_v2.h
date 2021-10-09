#ifndef CPARSESTRINGV2_H
#define CPARSESTRINGV2_H

#include <string>

#include "parse_string_v3/operations.h"
#include "sign.h"
#include "type.h"

struct TParseResult {
    NumeralTree* numeralTree = nullptr;
    StringTree* stringTree = nullptr;
    double value = 0;
};

class CParseStringV2
{
private:
    int m_numberentries;

    CPlusMinus m_plusminus;
    CTimeDivid m_timedivid;
    std::string m_previois;

    COperations m_operations;
    double m_data;
    double* m_pdata;

    void Process(StringTree*& node, CSign* sign);
    void Calculate(NumeralTree* node);
    void DeleteTree(StringTree* stringTree, NumeralTree* numeralTree);
    void ConvertAndLink(StringTree* in_node, NumeralTree*& out_node);

public:
    CParseStringV2();
    ~CParseStringV2();

    void Make(std::string formula, TParseResult& result);
    void DeleteParseResult(TParseResult& result);
    int GetNumberEntries();
};

#endif // CPARSESTRINGV2_H