#ifndef CStringTree_H
#define CStringTree_H

#include <float.h>
#include <map>
#include <string>
#include <vector>

#include "parse_string_v3/operations.h"

typedef std::map<double, double>* MapPoint;
typedef std::vector<std::pair<std::string, MapPoint>> ListNameAndPointGraph;

typedef std::_Rb_tree_iterator<std::pair<double const, double>> MapIterator;

enum NodeType : uint8_t { Value = 0x01, Graph = 0x02, Sign = 0x04 };
enum ErrorParse : uint8_t { ErrorGraph = 0x30, ErrorMapPoint = 0x50, ErrorInterpolationCrossing = 0x90 };

struct TGraphConfines {
    uint64_t step = 0;
    double max = DBL_MAX;
    double min = -DBL_MAX;

    void reset()
    {
        step = 0;
        min = -DBL_MAX;
        max = DBL_MAX;
    }
};

class CStringTree
{
private:
    MapPoint m_pMap;      /*!< Point to map.*/
    MapIterator m_itrMap; /*!< Iterator of map.*/
    NodeType m_type;      /*!< Type node.*/

    /**
     * @brief Init value
     */
    void Init();

public:
    std::string m_data; /*!< Node data.*/

    CStringTree* m_left;   /*!< Node left.*/
    CStringTree* m_right;  /*!< Node right.*/
    CStringTree* m_parent; /*!< Node parent.*/

    CStringTree();
    CStringTree(const std::string& value);
    ~CStringTree();

    // Get node
    CStringTree* GetLeft();
    CStringTree* GetRight();
    CStringTree* GetParent();

    // Set node
    void SetLeft(CStringTree* left);
    void SetRight(CStringTree* right);
    void SetParent(CStringTree* parent);

    /**
     * @brief Get data node
     * @return data
     */
    std::string GetData();

    /**
     * @brief Set data node
     * @param data
     */
    void SetData(std::string data);

    /**
     * @brief Set new map
     * @param map - poin map
     * @param type - type node
     */
    void SetMap(MapPoint map, NodeType type = NodeType::Value);

    /**
     * @brief Delete map
     */
    void DeleteMap();

    /**
     * @brief Get type node
     * @return type
     */
    NodeType GetType();

    /**
     * @brief Get value with interpolation
     * @param step - given value
     * @return second value of iterator map
     */
    double GetValue(const double& step);

    /**
     * @brief Get confines
     * @param confines - value confines
     */
    void GetConfines(TGraphConfines& confines);

    /**
     * @brief Calculate interpolation value
     * @param x - value which need interpolation
     * @param itr_prev - previously iterator map
     * @param itr_post - posterior iterator map
     * @return result interpolation
     */
    double GetInterpolation(const double& x, const MapIterator& itr_prev, const MapIterator& itr_post);

    /**
     * @brief Get first value of iterator map
     * @return first value
     */
    double GetFirst();

    /**
     * @brief Get second value of iterator map
     * @return second value
     */
    double GetSecond();
};

#endif // CStringTree_H