#ifndef TYPE_H
#define TYPE_H

#include "node.h"

// type for string tree
typedef CNode<std::string> StringTree;

// type for double and char tree
struct TData {
private:
    double value = 0;

public:
    char sign = '\0';
    double* pvalue = &value;
};

typedef CNode<TData> NumeralTree;

#endif // TYPE_H