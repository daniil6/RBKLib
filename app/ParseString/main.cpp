#include <stdio.h>

#include <utility>

#include "parse_string_v3/parsestring_v3.h"

int main(int argc, char** argv)
{
    CParseStringV3 parse;
    CStringTree* tree = nullptr;

    char formula[100] = { 0 };
    while(1) {

        printf("Formula: ");
        scanf("%s", formula);

        if(formula[0] == 'q')
            break;

        tree = parse.Make(formula);
        parse.Calculate(tree);
        printf("Result: %f\n", tree->GetSecond());
        CParseStringV3::DeleteTree(tree);
    }

    getchar();
    return 0;
}