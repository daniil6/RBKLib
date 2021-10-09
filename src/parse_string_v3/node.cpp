#include "parse_string_v3/node.h"

CStringTree::CStringTree()
{
    Init();
}

CStringTree::~CStringTree()
{
}

CStringTree::CStringTree(const std::string& value)
    : m_data(value)
{
    Init();
}

void CStringTree::Init()
{
    m_type = NodeType::Sign;
    m_pMap = nullptr;
    m_parent = nullptr;
    m_left = nullptr;
    m_right = nullptr;
}

std::string CStringTree::GetData()
{
    return m_data;
}

CStringTree* CStringTree::GetParent()
{
    return m_parent;
}

CStringTree* CStringTree::GetLeft()
{
    return m_left;
}

CStringTree* CStringTree::GetRight()
{
    return m_right;
}

void CStringTree::SetData(std::string data)
{
    m_data = data;
}

void CStringTree::SetParent(CStringTree* parent)
{
    m_parent = parent;
}

void CStringTree::SetLeft(CStringTree* left)
{
    m_left = left;
}

void CStringTree::SetRight(CStringTree* right)
{
    m_right = right;
}

void CStringTree::SetMap(MapPoint map, NodeType type)
{
    if(m_pMap != nullptr)
        DeleteMap();

    m_pMap = map;
    m_itrMap = map->begin();
    m_type = type;
}

void CStringTree::DeleteMap()
{
    if(m_pMap != nullptr) {
        delete m_pMap;
        m_pMap = nullptr;
    }
}

NodeType CStringTree::GetType()
{
    return m_type;
}

double CStringTree::GetFirst()
{
    if(m_pMap != nullptr)
        return m_itrMap->first;
    return 0;
}

double CStringTree::GetSecond()
{
    if(m_pMap != nullptr)
        return m_itrMap->second;
    return 0;
}

void CStringTree::GetConfines(TGraphConfines& confines)
{
    confines.max = COperations::Min(confines.max, std::prev(m_pMap->end())->first);
    confines.min = COperations::Max(confines.min, m_itrMap->first);
    confines.step = COperations::GCD(confines.step, std::next(m_itrMap)->first - m_itrMap->first);
    if(confines.step != 0) {
        if(int(confines.max - confines.min) % confines.step)
            confines.step = COperations::GCD(confines.step, confines.max - confines.min);
    } else
        confines.step = 1;
}

double CStringTree::GetInterpolation(const double& x, const MapIterator& itr_prev, const MapIterator& itr_post)
{
    double x1 = itr_prev->first;
    double y1 = itr_prev->second;
    double x2 = itr_post->first;
    double y2 = itr_post->second;

    return (y2 - y1) / (x2 - x1) * (x - x1) + y1;
}

double CStringTree::GetValue(const double& step)
{
    if(m_pMap == nullptr)
        throw ErrorMapPoint;

    auto itr = m_pMap->lower_bound(step);
    if(itr == m_pMap->end())
        throw ErrorGraph;
    if(itr->first != step) {
        if(itr == m_pMap->begin())
            return GetInterpolation(step, itr, std::next(itr));
        else
            return GetInterpolation(step, std::prev(itr), itr);
    } else
        return itr->second;
}