#include <stack>
#include <cctype>
#include <string>
#include <stdio.h>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string infixToPostfix(const string& expression) {
    stack<char> s;
    string result;

    for (size_t i = 0; i < expression.length(); i++) {
    	char symbol = expression[i];
        if (isalnum(symbol)) {
            result += symbol;
        } else if (symbol == '(') {
            s.push(symbol);
        } else if (symbol == ')') {
            while (!s.empty() && s.top() != '(') {
                result += s.top();
                s.pop();
            }
            s.pop();
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(symbol)) {
                result += s.top();
                s.pop();
            }
            s.push(symbol);
        }
    }

    while (!s.empty()) {
        result += s.top();
        s.pop();
    }

    return result;
}

int main() {
    string infix_expression = "A+B*(C^D-E)";
    string postfix_expression = infixToPostfix(infix_expression);
    printf("Hasil konversi ke postfix: %s\n", postfix_expression.c_str());
    return 0;
}
