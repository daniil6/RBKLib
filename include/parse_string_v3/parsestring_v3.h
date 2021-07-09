#ifndef CPARSESTRINGV3_H
#define CPARSESTRINGV3_H

#include "parse_string_v3/node.h"
#include "parse_string_v2/sign.h"

class CParseStringV3
{
private:
    TGraphConfines m_confines;          /*!< Graph confines.*/
    ListNameAndPointGraph* m_listGraph; /*!< List name graph and point to map of graph.*/
    double m_min;                       /*!< Min value plot for line.*/
    double m_max;                       /*!< Max value plot for line.*/

    std::string m_previois; /*!< Previois parse value.*/

    CPlusMinus m_plusminus;   /*!< Signs compare ( '+' '-' ).*/
    CTimeDivid m_timedivid;   /*!< Signs compare ( '*' '/' ).*/
    COperations m_operations; /*!< Helper class operation.*/

    /**
     * @brief Main process parse string
     * @param node - node of tree
     * @param sign - class CSign contain '+' and '-' or '*' and '/'
     */
    void Process(CStringTree*& node, CSign* sign);

    /**
     * @brief Convert string value tree to duoble or link graph value at tree
     * @param node - node of tree
     */
    void ConvertAndLink(CStringTree* node);

public:
    CParseStringV3(ListNameAndPointGraph* listGraph = nullptr, const double& min = 0, const double& max = 0);
    ~CParseStringV3();

    /**
     * @brief Make tree of string formula
     * @param formula - string formula
     * @return parse tree
     */
    CStringTree* Make(std::string formula);

    /**
     * @brief Get confines for graph: min, max and step
     * @return graph confines
     */
    TGraphConfines GetConfines();

    /**
     * @brief Calculate tree
     * @param node - node of tree
     * @param step - step calculate
     */
    void Calculate(CStringTree* node, const double& step = 0);

    /**
     * @brief Get name graph and his positon and remove his of formula, if corresponds aggregate function
     * @param formula - string formula in which aggregate function is searched
     * @param nameGraph - name graph
     * @param findAgr - name aggregate function
     * @return return positon and name graph, and remove name graph with aggregate function
     */
    static size_t GetNameGraph(std::string& formula, std::string& nameGraph, const std::string& findAgr);

    /**
     * @brief Delete tree, if tree != nullptr
     * @param node - node of tree
     */
    static void DeleteTree(CStringTree* node);
};

#endif // CPARSESTRINGV3_H