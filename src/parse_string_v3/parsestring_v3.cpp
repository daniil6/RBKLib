#include "parse_string_v3/parsestring_v3.h"

CParseStringV3::CParseStringV3(ListNameAndPointGraph* listGraph, const double& min, const double& max)
    : m_listGraph(listGraph)
{
    m_min = min;
    m_max = max;
}

CParseStringV3::~CParseStringV3()
{
}

void CParseStringV3::Process(CStringTree*& node, CSign* sign)
{
    if(node == nullptr)
        return;

    char ch = 0;
    int count = 0;
    bool signup = false;

    std::string formula = &node->m_data[0];
    CStringTree* point = new CStringTree;

    while(1) {
        ch = formula[count++];
        if(ch == sign->first() || ch == sign->second() || ch == '\0') {

            if(point->m_data == m_previois) {
                if(point != node)
                    delete point;
                return;
            }

            if(point->GetData() == "")
                point->SetData("0");

            m_previois = point->m_data;
            node->m_data = ch;

            Process(point, (sign == &m_plusminus) ? (CSign*)&m_timedivid : (CSign*)&m_plusminus);

            ConvertAndLink(point);

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

            if(ch == '\0')
                return;

            node->m_parent = new CStringTree;
            node->m_parent->m_left = node;
            node = node->m_parent;
            point = new CStringTree;
            m_previois = "_";
        } else {
            if(ch == '(') {
                int counter = 1;
                if(sign == &m_plusminus)
                    point->m_data.push_back(ch);
                while(counter != 0) {
                    ch = formula[count++];
                    point->m_data.push_back(ch);
                    if(ch == ')')
                        counter--;
                    if(ch == '(')
                        counter++;
                }
                if(sign == &m_timedivid)
                    point->m_data.pop_back();
            } else
                point->m_data.push_back(ch);
        }
    }
}

void CParseStringV3::ConvertAndLink(CStringTree* node)
{
    double val = 0;
    std::string name = node->GetData();

    if(node->GetType() == NodeType::Sign) {
        try {
            val = std::stod(name);

            m_confines.min = COperations::Max(m_confines.min, m_min);
            m_confines.max = COperations::Min(m_confines.max, m_max);
            m_confines.step = COperations::GCD(m_confines.step, m_confines.max - m_confines.min);

            node->SetMap(new std::map<double, double>{ { m_confines.min, val }, { m_confines.max, val } });
            return;
        } catch(const std::invalid_argument& ia) {
            val = 0;
        } catch(const std::out_of_range& oor) {
            val = 0;
        }
    }

    if(m_listGraph != nullptr) {
        for(auto& p : *m_listGraph) {
            if(p.first == name) {
                node->SetMap(p.second, NodeType::Graph);
                node->GetConfines(m_confines);
                return;
            }
        }
    }
}

void CParseStringV3::Calculate(CStringTree* node, const double& step)
{
    CStringTree* left = node->GetLeft();
    CStringTree* right = node->GetRight();

    if(left != nullptr && right != nullptr) {
        Calculate(left, step);
        Calculate(right, step);

        double x = left->GetValue(step);
        double y = right->GetValue(step);

        x = m_operations.Calculate(x, y, &node->m_data[0]);
        node->SetMap(new std::map<double, double>{ { step, x } });
    } else if(node->GetType() == NodeType::Value)
        node->SetMap(new std::map<double, double>{ { step, node->GetSecond() } });
}

void CParseStringV3::DeleteTree(CStringTree* node)
{
    if(node != nullptr) {
        DeleteTree(node->GetLeft());
        DeleteTree(node->GetRight());

        if(node->GetType() != NodeType::Graph)
            node->DeleteMap();

        delete node;
        node = nullptr;
    }
}

CStringTree* CParseStringV3::Make(std::string formula)
{
    CStringTree* stringTree = new CStringTree(formula);
    m_confines.reset();
    m_previois = "_";

    Process(stringTree, &m_plusminus);

    CStringTree* point = nullptr;
    point = stringTree;
    stringTree = stringTree->m_left;
    stringTree->m_parent = nullptr;
    delete point;

    return stringTree;
}

size_t CParseStringV3::GetNameGraph(std::string& formula, std::string& nameGraph, const std::string& findAgr)
{
    size_t posBegin = formula.find(findAgr);

    if(posBegin != std::string::npos) {

        formula.erase(posBegin, findAgr.size() + 1);

        size_t posEnd = formula.find(')', posBegin);

        formula.erase(posEnd, 1);

        size_t size = posEnd - posBegin;

        nameGraph = formula.substr(posBegin, size);

        formula.erase(posBegin, size);
    }

    return posBegin;
}

TGraphConfines CParseStringV3::GetConfines()
{
    if(m_confines.min >= m_confines.max)
        throw ErrorInterpolationCrossing;

    return m_confines;
}