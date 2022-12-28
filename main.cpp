#include <iostream>
#include "expression.h"

int main(int argc, char **argv)
{

    if (argc > 1)
    {
        std::string expression_str;
        for (int i = 0; i < (argc - 1); i++)
            expression_str += argv[i];

        expression e(expression_str);
        e.evaluate();
        std::cout << e.result << std::endl;
    }

    else
    {
        std::string input;
        std::cout << "type !help for help\n";

        while (true)
        {
            std::cout << "expression > ";
            std::getline(std::cin, input);

            if (input[0] == '!')
            {
                if (input.substr(1) == "help")
                {
                    std::cout << "clc version 1.0" << std::endl;
                    std::cout << "description: evaluates arithmetic expressions" << std::endl;
                    std::cout << "author: Vipul Kumar" << std::endl;
                    std::cout << "\ncommands:\n\thelp\n\texit" << std::endl;
                }

                else if (input.substr(1) == "exit")
                {
                    std::cout << "bye" << std::endl;
                    exit(0);
                }
            }

            expression e(input);
            e.evaluate();
            std::cout << e.result << std::endl;
        }
    }

    return 0;
}
