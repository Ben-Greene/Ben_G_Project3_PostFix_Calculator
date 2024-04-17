// Ben_G_Project3_PostFix_Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

bool isOperator(char c) { // checks if the char is an operator
    return (c == '+' || c == '*');
}

int calculate(int operand1, int operand2, char op) { // performs the computation 
    if (op == '+') {
        return operand1 + operand2;
    }
    else if (op == '*') {
        return operand1 * operand2;
    }
    return 0;  // Invalid operator
}

int evaluate(const string& equation) {// parses through string and evaluates the entries 
    stack<int> numStack;
    istringstream iss(equation);
    string subString;
    while (iss >> subString) {
        if (isdigit(subString[0])) {
            numStack.push(stoi(subString));
        }
        else if (isOperator(subString[0])) {
            if (numStack.size() < 2) {
                cout << "Invalid expression, please adjust." << endl;
                return 0;  // checks for operands
            }
            int operand2 = numStack.top();
            numStack.pop();
            int operand1 = numStack.top();
            numStack.pop();
            int result = calculate(operand1, operand2, subString[0]);
            numStack.push(result);
        }
    }
    if (numStack.size() != 1) {
        cout << "Invalid expression." << endl;
        return 0;  // checks for valid input
    }
    return numStack.top();
}

int main() {
    cout << "Enter the equation you would like to calculate in postfix notation" << endl
        << "Only evaluate * and + operations" << endl
        << "Enter '=' when done writing the equation, and 'q' to quit" << endl;

    while (true) {
        string user;
        getline(cin, user);

        if (user.empty()) {
            cout << "Please include an input." << endl; // checks if initial input is empty
            continue;
        }
        if (user == "q" || user == "Q") { // exists the program
            cout << "Goodbye!" << endl;
            return 0;
        }
        if (user.find('=') != user.length() - 1) { // ensures the = is at the end 
            cout << "Invalid expression: please include a single = at the end." << endl;
            continue;
        }

        string postfix = user.substr(0, user.length() - 1);  // Remove '='
        int answer = evaluate(postfix);
        cout << "Result: " << answer << endl;
    }

    return 0;
}

