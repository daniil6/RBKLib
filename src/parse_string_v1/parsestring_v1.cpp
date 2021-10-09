#include "parse_string_v1/parsestring_v1.h"

CParseStringV1::CParseStringV1()
{
    m_root = nullptr;
}

CParseStringV1::~CParseStringV1()
{
}

void CParseStringV1::DeleteTree(StringTree* node)
{
    if(node != nullptr) {
        DeleteTree(node->GetLeft());
        DeleteTree(node->GetRight());
        delete node;
        node = nullptr;
    }
}

void CParseStringV1::TreeCopyProcess(StringTree* tree, StringTree* treeCopy)
{
    if(tree->GetLeft() != nullptr || tree->GetRight() != nullptr) {
        treeCopy->SetLeft(new StringTree(tree->GetLeft()->GetData()));
        TreeCopyProcess(tree->GetLeft(), treeCopy->GetLeft());
        treeCopy->SetRight(new StringTree(tree->GetRight()->GetData()));
        TreeCopyProcess(tree->GetRight(), treeCopy->GetRight());
        treeCopy->SetData(tree->GetData());
    }
}

StringTree* CParseStringV1::TreeCopy(StringTree* tree)
{
    StringTree* treeCopy = new StringTree("_");
    TreeCopyProcess(tree, treeCopy);
    return treeCopy;
}

StringTree* CParseStringV1::Make(std::string str_entry)
{
    m_root = new StringTree(str_entry);
    for(auto rit = str_entry.rbegin(); rit != str_entry.rend(); ++rit)
        if(*rit == '*' || *rit == '/' || rit == str_entry.rend() - 1)
            TraversalTree(m_root);
    return m_root;
}

std::string CParseStringV1::CharToString(char symbol)
{
    std::string chartostring = "";
    chartostring += symbol;
    return chartostring;
}

void CParseStringV1::CreatTree(StringTree* node, char signOne, char signTwo)
{
    std::string str = node->GetData();

    std::stack<std::string> stackBorder;
    std::string content;
    for(auto rit = str.rbegin(); rit != str.rend(); ++rit) {
        if(*rit == ')')
            stackBorder.push("skobka");

        if(*rit == '(') {
            if(!stackBorder.empty())
                stackBorder.pop();
            else {
                // wxMessageBox(wxT("Error. Something wrong"));
                break;
            }
        }

        if(stackBorder.empty()) {
            if(*rit == signOne || *rit == signTwo) {
                if(!content.empty()) {
                    node->SetData(CharToString(*rit));
                    node->SetLeft(new StringTree(content));
                    node->SetRight(new StringTree(CharToString('0')));
                    node = node->GetRight();

                    content.clear();
                }
            } else
                content.insert(0, CharToString(*rit));
        } else
            content.insert(0, CharToString(*rit));
    }
    if(!content.empty())
        node->SetData(content);
}

void CParseStringV1::DeleteBracket(StringTree* node)
{
    if(node != nullptr) {

        DeleteBracket(node->GetLeft());
        DeleteBracket(node->GetRight());

        std::string str = node->GetData();
        while(str.back() == '\0')
            str.pop_back();

        if(str.front() == '(' && str.back() == ')')
            str = str.substr(1, str.find_last_of(str.back()) - 1);

        node->SetData(str);
    }
}

bool CParseStringV1::CheckPlusMinusSign(std::string str)
{
    bool nosign = false;
    std::stack<std::string> stackBorder;
    for(auto rit = str.rbegin(); rit != str.rend(); ++rit) {
        if(*rit == ')')
            stackBorder.push("skobka");

        if(*rit == '(') {
            if(!stackBorder.empty())
                stackBorder.pop();
            else {
                // wxMessageBox(wxT("Error. Something wrong"));
                break;
            }
        }

        if(stackBorder.empty())
            if(*rit == '+' || *rit == '-')
                nosign = true;
    }
    return nosign;
}

void CParseStringV1::CheckAggregateFunction(StringTree* node)
{
    const std::string MassAggregateFunc[6] = { "SUM", "MAX", "MIN", "CNT", "AVG", "MDN" };

    std::string str = node->GetData();
    while(str.back() == '\0')
        str.pop_back();

    for(int i = 0; i < 6; i++) {
        if(str.find(MassAggregateFunc[i]) != std::string::npos) {
            str = str.substr(3);
            if(str.front() == '(' && str.back() == ')')
                str = str.substr(1, str.find_last_of(str.back()) - 1);
            node->SetData(MassAggregateFunc[i]);
            node->SetLeft(new StringTree(CharToString('0')));
            node->SetRight(new StringTree(str));
            i = 6;
        }
    }
}

void CParseStringV1::TraversalTree(StringTree* node)
{
    if(node != nullptr) {
        if(CheckPlusMinusSign(node->GetData()))
            CreatTree(node, '+', '-');
        else {
            CreatTree(node, '*', '/');
            DeleteBracket(node);
            if(node->GetData().size() > 3)
                CheckAggregateFunction(node);
        }

        TraversalTree(node->GetLeft());
        TraversalTree(node->GetRight());
    }
}