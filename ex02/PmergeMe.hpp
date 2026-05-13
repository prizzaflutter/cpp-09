#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include<deque>
#include<vector>
#include<string>

class PmergeMe {
    private:
        std::vector<int> vec;
        std::deque<int> deq;
        bool isValidNumber(const std::string& str);
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void parseInput(char **argv);

        void printBefore() const;
        void printAfter() const;

        void setVector();
        std::vector<int>  fordJohnsonVector(std::vector<int> v);
        void binaryInsertVector(std::vector<int>& chain, int value);

        void setDeque(); 
        std::deque<int> fordJohnsonDeque(std::deque<int> d);
        void binaryInsertDeque(std::deque<int>& chain, int value);
        std::vector<int> buildJacobsthalOrderVector(size_t size);
        std::deque<int> buildJacobsthalOrderDeque(size_t size);
};

#endif