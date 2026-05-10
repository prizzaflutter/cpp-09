#include "RPN.hpp"
#include <sstream>
#include <cstdlib>
#include <climits>

RPN::RPN(){}

RPN::RPN(const RPN& other): numbers(other.numbers) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other){
        numbers = other.numbers;
    }
    return *this;
}

RPN::~RPN(){}

void RPN::processExpression(const std::string& expression){
    std::stringstream ss(expression);

    std::string token;
    while (ss >> token){
        if (token.length() == 1 && std::isdigit(token[0])){
            int number = std::atoi(token.c_str());
            numbers.push(number);
        }else if (token == "+" || token == "-" || token == "*" || token == "/"){
            if (numbers.size() < 2){
                std::cout << "Error" << std::endl;
                return;
            }
            int a = numbers.top();
            numbers.pop();
            int b = numbers.top();
            numbers.pop();
            long long result;

            if (token == "+")
                result = (long long)b + (long long)a;
            else if (token == "-")
                result = (long long)b - (long long)a;
            else if (token == "*")
                result = (long long)b * (long long)a;
            else{
                if (a == 0){
                    std::cout << "Error" << std::endl;
                    return;
                }
                result = (long long)b / (long long)b;
            } 
            if (result > INT_MAX || result < INT_MIN){
                std::cout << "Error" << std::endl;
                return;
            }
            numbers.push(result);
        }else {
            std::cout << "Error" << std::endl;
            return;
        }
    }
    if (numbers.size() != 1){
            std::cout << "Error" << std::endl;
            return;
    }
    std::cout << numbers.top() << std::endl;
}