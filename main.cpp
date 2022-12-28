#include <iostream>
#include "expression.h"

int main(int argc, char **argv)
{

    if (argc >= 2)
    {
        std::string expression_str;
        for (int i = 1; i < argc; i++)
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

            // command block
            if (input[0] == '!')
            {
                if (input.substr(1) == "help")
                {
                    std::cout << "clc" << std::endl;
                    std::cout << "description: evaluates arithmetic expressions" << std::endl;
                    std::cout << "author: Vipul Kumar" << std::endl;
                    std::cout << "\ncommands:\n\thelp\n\texit" << std::endl;
                    
                }

                else if (input.substr(1) == "exit")
                {
                    std::cout << "bye" << std::endl;
                    exit(0);
                }
                continue;
            }

            expression e(input);
            e.evaluate();
            std::cout << e.result << std::endl;
        }
    }

    return 0;
}
