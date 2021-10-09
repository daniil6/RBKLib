#ifndef CPARSESTRINGV1_H
#define CPARSESTRINGV1_H

#include "parse_string_v2/node.h"
#include <stack>

#include <string>

typedef CNode<std::string> StringTree;

class CParseStringV1
{
private:
    StringTree* m_root;

    /**
     * @brief Parse formula from string to tree
     * @brief according to found sign: signOne and signTwo
     * @param node - node of tree
     * @param signOne - sign one
     * @param signTwo - sign two
     */
    void CreatTree(StringTree* node, char signOne, char signTwo);

    /**
     * @brief Tree traversal and creat branches tree
     * @param node - node of tree
     */
    void TraversalTree(StringTree* node);

    /**
     * @brief Delete front and back bracket if they exist
     * @param node - node tree
     */
    void DeleteBracket(StringTree* node);

    /**
     * @brief Finde plus or minus sign
     * @param str - entry string
     * @return true if plus or minus sign found, otherwise fasle
     */
    bool CheckPlusMinusSign(std::string str);

    /**
     * @brief Convert char to string
     * @param symbol - symbol in format char
     * @return symbol in format string
     */
    std::string CharToString(char symbol);

    /**
     * @brief Check and find aggregate function and create node for tree formula
     * @param node - node for check
     */
    void CheckAggregateFunction(StringTree* node);

    /**
     * @brief Recursive tree traversal for create copy tree
     * @param tree - input tree
     * @param treeCope - output tree
     */
    void TreeCopyProcess(StringTree* tree, StringTree* treeCope);

public:
    CParseStringV1();
    ~CParseStringV1();

    /**
     * @brief Make parse
     * @param str_entry - string formul
     * @return StringTree* - pointer on tree
     */
    StringTree* Make(std::string str_entry);

    /**
     * @brief Create copy tree
     * @param tree - input tree
     * @return StringTree* - pointer on copy tree
     */
    StringTree* TreeCopy(StringTree* tree);

    /**
     * @brief Delete tree from memory
     * @param node - node of tree
     */
    void DeleteTree(StringTree* node);
};

#endif // CPARSESTRINGV1_H
