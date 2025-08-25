#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(string expr) {
    stack<char> ops;
    stringstream output;
    for (char ch : expr) {
        if (isdigit(ch)) output << ch << ' ';
        else if (ch == '(') ops.push(ch);
        else if (ch == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output << ops.top() << ' ';
                ops.pop();
            }
            ops.pop();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(ch)) {
                output << ops.top() << ' ';
                ops.pop();
            }
            ops.push(ch);
        }
    }
    while (!ops.empty()) {
        output << ops.top() << ' ';
        ops.pop();
    }
    return output.str();
}

int evaluatePostfix(string postfix) {
    stack<int> values;
    stringstream ss(postfix);
    string token;
    while (ss >> token) {
        if (isdigit(token[0])) values.push(stoi(token));
        else {
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            if (token == "+") values.push(a + b);
            else if (token == "-") values.push(a - b);
            else if (token == "*") values.push(a * b);
            else if (token == "/") values.push(a / b);
        }
    }
    return values.top();
}

int main() {
    string expr;
    cout << "Enter infix expression: ";
    getline(cin, expr);
    string postfix = infixToPostfix(expr);
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << evaluatePostfix(postfix) << endl;
    return 0;
}
