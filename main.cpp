#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

bool isnum(char c);
double operate(double, double, char);
int op_precedence(char c);

bool verbosity = false;

std::string help_txt = "clc [expression]\
                        \n\t+ for addition \
                        \n\t\\ for division \
                        \n\tx for multiplication \
                        \n\t- for subtraction \
                        ";

class expression
{
private:
    std::stack<char> *operators;
    std::stack<double> *operands;
    std::string str;

public:
    void process()
    {
        // pop two operands
        double b = this->operands->top();
        this->operands->pop();
        double a = this->operands->top();
        this->operands->pop();
        // pop one operator
        char op = this->operators->top();
        this->operators->pop();
        // push the result of operation on the stack
        this->operands->push(operate(a, b, op));

        if (this->operators->size() > 1)
            if (this->operators->top() == '(')
                this->operators->pop();
    }

    size_t str_len;
    double result;
    expression(std::string expr)
    {
        this->str = "(" + expr + ")";
        this->str_len = expr.length() + 2;
        this->operands = new std::stack<double>;
        this->operators = new std::stack<char>;
    }

    void evaluate()
    {
        for (size_t i = 0; i < this->str_len; i++)
        {

            if (str[i] == ' ')
                continue;

            char c = str[i];

            if (isnum(c))
            {
                std::string::size_type double_at = i, double_len = 1;

                while (isnum(str[++i]) || str[i] == '.')
                    double_len++;
                i--;

                std::string operand_str = str.substr(double_at, double_len);
                double operand = std::stod(operand_str);
                this->operands->push(operand);
            }

            else
            {
                if (c != ')')
                {

                    if (this->operators->empty() ||
                        op_precedence(c) <= op_precedence(this->operators->top()))
                        this->operators->push(c);

                    else
                    {
                        this->process();
                        this->operators->push(c);
                    }
                }

                else
                    while (this->operators->top() != '(')
                        this->process();
            }
        }
        this->result = this->operands->top();
        this->operands->pop();
    }
};

// This Function evaluates the binary operations
double operate(double a, double b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*' || op == 'x')
        return a * b;
    if (op == '/')
        return a / b;
    if (op == '^')
        return pow(a, b);
    return 0.0000; // only for suppressing warnings
}

// used to check whether a character is number or not
bool isnum(char c) { return (48 <= c && c <= 57); }

// returns the operator's precedence
int op_precedence(char c)
{
    if (c == '(')
        return 5;

    if (c == '+' || c == '-')
        return 5;

    if (c == '*' || c == '/' || c == 'x')
        return 4;

    if (c == '^')
        return 3;

    if (c == ')')
        return 1;

    return 0; // only for supressing warnings
};

void interactive()
{
    std::string input;
    std::cout << "type !help for help\n";

    while (true)
    {
        std::cout << "expression > ";
        std::getline(std::cin, input);

        // command block
        if (input[0] != '!')
        {
            expression e(input);
            e.evaluate();
            std::cout << e.result << std::endl;
        }

        else
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
    }
}

int main(int argc, char **argv)
{
    std::vector<char *> flags;
    // putting all flags passed in a vector
    for (int i = 1; i < argc; i++)
        if (argv[i][0] == '-' && sizeof(argv[i]))
            flags.push_back(argv[i]);

    if (argc == 1)
        std::cout << "No arguments" << std::endl;

    else if (argc == 2 && argv[1][0] == '-')
    {
        if (argv[1][1] == 'h')
            std::cout << help_txt << std::endl;

        else if (argv[1][1] == 'i')
            interactive();
    }

    else if (argc >= 2)
    {
        std::string expression_str;
        for (int i = 1; i < argc; i++)
            expression_str += argv[i];

        expression e(expression_str);
        e.evaluate();
        std::cout << e.result << std::endl;
    }

    return 0;
}
