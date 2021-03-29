#include "parse/parsestring.h"
#include "convert_string_double.h"

CParseString::CParseString()
{
    m_sign = nullptr;
    m_pdata = &m_data;
}

CParseString::~CParseString()
{
}

void CParseString::Process(StringTree*& node)
{
    m_numberentries++;

    if(node == nullptr)
        return;

    std::string str = &node->m_data[0];
    const char* in = &str[0];

    char ch = 0;
    StringTree* point = new StringTree;
    int counter = 0;
    bool signup = false;

    while(1) {
        ch = *in++;
        if(ch == m_sign->first() || ch == m_sign->second() || ch == '\0') {

            if(point->m_data == m_previois) {
                // m_numberentries--;
                if(point != node)
                    delete point;
                return;
            }

            if(point->GetData() == "")
                point->SetData("0");

            m_previois = point->m_data;
            node->m_data = ch;

            m_sign == & m_plusminus ? m_sign = &m_timedivid : m_sign = &m_plusminus;
            Process(point);
            m_sign == & m_plusminus ? m_sign = &m_timedivid : m_sign = &m_plusminus;

            if(signup == false) {
                signup = true;
                if(point->m_left != nullptr) {
                    point->m_left->m_parent = node;
                    node->m_left = point->m_left;
                    delete point;
                } else
                    node->m_left = point;
            } else {
                if(point->m_left != nullptr) {
                    point->m_left->m_parent = node->m_left;
                    node->m_left->m_right = point->m_left;
                    delete point;
                } else
                    node->m_left->m_right = point;
            }

            if(ch == '\0') {
                // m_numberentries--;
                return;
            }

            node->m_parent = new StringTree;
            node->m_parent->m_left = node;
            node = node->m_parent;
            point = new StringTree;
            m_previois = "_";
        } else {
            if(ch == '(') {
                counter++;
                if(m_sign == &m_plusminus)
                    point->m_data.push_back(ch);
                while(counter != 0) {
                    ch = *in++;
                    point->m_data.push_back(ch);
                    if(ch == ')')
                        counter--;
                    if(ch == '(')
                        counter++;
                }
                if(m_sign == &m_timedivid)
                    point->m_data.pop_back();
            } else
                point->m_data.push_back(ch);
        }
    }
}

void CParseString::ConvertAndLink(StringTree* in_node, NumeralTree*& out_node)
{
    if(in_node != nullptr) {

        out_node = new NumeralTree;

        ConvertAndLink(in_node->GetLeft(), out_node->m_left);
        ConvertAndLink(in_node->GetRight(), out_node->m_right);

        if(in_node->GetLeft() == nullptr || in_node->GetRight() == nullptr)
            return;

        out_node->m_data.sign = in_node->GetData()[0];

        std::string left = in_node->GetLeft()->GetData();
        std::string right = in_node->GetRight()->GetData();

        if(left == "x0") {
            out_node->m_left->m_data.pvalue = nullptr;
        } else {
            *(out_node->m_left->m_data.pvalue) = ConvertStringToDouble(left);
        }

        if(right == "x0") {
            out_node->m_right->m_data.pvalue = nullptr;
        } else {
            *(out_node->m_right->m_data.pvalue) = ConvertStringToDouble(right);
        }
    }
}

void CParseString::Calculate(NumeralTree* node)
{
    double a = 0;
    double b = 0;

    if(node != nullptr) {
        Calculate(node->GetLeft());
        Calculate(node->GetRight());

        if(node->GetLeft() == nullptr || node->GetRight() == nullptr)
            return;

        a = *node->GetLeft()->GetData().pvalue;
        b = *node->GetRight()->GetData().pvalue;

        *node->GetData().pvalue = m_operations.Calculate(a, b, &node->m_data.sign);
    }
}

void CParseString::DeleteTree(StringTree* stringTree, NumeralTree* numeralTree)
{
    if(stringTree != nullptr && numeralTree != nullptr) {
        DeleteTree(stringTree->GetLeft(), numeralTree->GetLeft());
        DeleteTree(stringTree->GetRight(), numeralTree->GetRight());

        delete stringTree;
        delete numeralTree;

        stringTree = nullptr;
        numeralTree = nullptr;
    }
}

void CParseString::Make(std::string formula, TParseResult& result)
{
    StringTree* stringTree = new StringTree(formula);
    NumeralTree* numeralTree = nullptr;

    m_sign = &m_plusminus;
    m_numberentries = 0;
    m_previois = "_";

    Process(stringTree);

    StringTree* point = nullptr;
    point = stringTree;
    stringTree = stringTree->m_left;
    stringTree->m_parent = nullptr;
    delete point;

    ConvertAndLink(stringTree, numeralTree);
    Calculate(numeralTree);

    result.numeralTree = numeralTree;
    result.stringTree = stringTree;
    result.value = *numeralTree->GetData().pvalue;
}

void CParseString::DeleteParseResult(TParseResult& result)
{
    DeleteTree(result.stringTree, result.numeralTree);
    result.value = 0;
}

int CParseString::GetNumberEntries()
{
    return m_numberentries;
}