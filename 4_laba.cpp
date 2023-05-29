#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isOperator(char c) {                //принимает символ c и проверяет, является ли он оператором (+, -, *, /)
    if (c == '+' || c == '-' || c == '/' || c == '*')
        return true;
    return false;
}

int getPrecedence(char c) {                 //принимает символ c и возвращает его приоритет(Операторы + и - имеют приоритет 1, а операторы * и / имеют приоритет 2.Все остальные символы, которые не являются операторами, имеют приоритет 0)
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

string infixToPostfix(string infix) {        //принимает строку infix, содержащую инфиксное выражение, и преобразует его в постфиксную запись
    stack<char> operatorStack;
    string postfixExpression;

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == ' ')
            continue;

        if (isdigit(infix[i])) {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfixExpression += infix[i];
                i++;
            }
            i--;
            postfixExpression += ' ';
        }
        else if (isOperator(infix[i])) {
            while (!operatorStack.empty() && operatorStack.top() != '(' && getPrecedence(operatorStack.top()) >= getPrecedence(infix[i])) {
                postfixExpression += operatorStack.top();
                operatorStack.pop();
                postfixExpression += ' ';
            }
            operatorStack.push(infix[i]);
        }
        else if (infix[i] == '(') {
            operatorStack.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfixExpression += operatorStack.top();
                operatorStack.pop();
                postfixExpression += ' ';
            }
            operatorStack.pop();
        }
    }

    while (!operatorStack.empty()) {
        postfixExpression += operatorStack.top();
        operatorStack.pop();
        postfixExpression += ' ';
    }

    return postfixExpression;
}

double evaluatePostfix(string postfix) {          //принимает строку postfix,содержащую постфиксное выражение, и вычисляет его результат
    stack<double> operandStack;

    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] == ' ')
            continue;

        if (isdigit(postfix[i])) {
            double num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (double)(postfix[i] - '0');
                i++;
            }
            if (postfix[i] == '.') {
                i++;
                double fraction = 1;
                while (isdigit(postfix[i])) {
                    fraction = fraction / 10;
                    num = num + fraction * (double)(postfix[i] - '0');
                    i++;
                }
            }
            i--;
            operandStack.push(num);
        }
        else if (isOperator(postfix[i])) {
            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();
            if (postfix[i] == '+') {
                operandStack.push(operand1 + operand2);
            }
            else if (postfix[i] == '-') {
                operandStack.push(operand1 - operand2);
            }
            else if (postfix[i] == '*') {
                operandStack.push(operand1 * operand2);
            }
            else if (postfix[i] == '/') {
                operandStack.push(operand1 / operand2);
            }
        }
    }

    return operandStack.top();
}

int main() {
    setlocale(0, "Ru");
    string infixExpression;
    cout << "Введите инфиксное выражение:  ";
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Результат в постфиксной записи: " << postfixExpression << endl;

    double result = evaluatePostfix(postfixExpression);
    cout << "Результат вычисления выражения в постфиксной нотации:  " << result << endl;

    return 0;
}



