#include <iostream>
#include "expression.h"

int main(int argc, char **argv)
{
    std::string expression_str = "";
    for (int i=0; i<(argc-1);i++)
        expression_str += argv[i];

    expression e(expression_str);
    e.evaluate();
    std::cout << e.result << std::endl;

    return 0;
}
