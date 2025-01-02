#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

bool isnum(char c);
double operate(double, double, char);
double factorial(double);
int op_precedence(char c);

class expression {
   private:
    std::stack<char> *operators;
    std::stack<double> *operands;
    std::string str;

   public:
    void process() {
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
            if (this->operators->top() == '(') this->operators->pop();
    }

    size_t str_len;
    double result;

    expression(std::string expr) {
        this->str = "(" + expr + ")";
        this->str_len = expr.length() + 2;
        this->operands = new std::stack<double>;
        this->operators = new std::stack<char>;
    }

    void evaluate() {
        bool FIRST_NEGATIVE = false;

        for (size_t i = 0; i < this->str_len; i++) {
            if (str[i] == ' ') continue;

            char c = str[i];

            if (c == '-' && this->operands->empty()) {
                FIRST_NEGATIVE = true;
                continue;
            }

            if (isnum(c)) {
                std::string::size_type double_at = i, double_len = 1;

                while (isnum(str[++i]) || str[i] == '.') double_len++;
                i--;

                std::string operand_str = str.substr(double_at, double_len);
                double operand = std::stod(operand_str);

                // check for post number function
                if (str[i + 1] == '!')
                    std::cout << factorial(operand) << std::endl;

                this->operands->push(FIRST_NEGATIVE ? -operand : operand);
                FIRST_NEGATIVE = false;
            }

            else {
                if (c != ')') {
                    if (this->operators->empty() ||
                        op_precedence(c) <=
                            op_precedence(this->operators->top()))
                        this->operators->push(c);

                    else {
                        this->process();
                        this->operators->push(c);
                    }
                }

                else
                    while (this->operators->top() != '(') this->process();
            }
        }
        this->result = this->operands->top();
        this->operands->pop();
    }
};

double operate(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*' || op == 'x') return a * b;
    if (op == '/') return a / b;
    if (op == '^') return pow(a, b);
}

bool isnum(char c) { return (48 <= c && c <= 57); }

int op_precedence(char c) {
    if (c == '(') return 5;

    if (c == '+' || c == '-') return 5;

    if (c == '*' || c == '/' || c == 'x') return 4;

    if (c == '^') return 3;

    if (c == ')') return 1;
}

double factorial(double oprnd) {
    return (oprnd == 0) ? 1.0 : oprnd * factorial(oprnd - 1);
}
