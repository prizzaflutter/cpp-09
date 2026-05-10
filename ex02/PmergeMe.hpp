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
        std::vector<int>  mergeSortVector(std::vector<int> v);
        void insertSorted(std::vector<int>& sorted, int value);

        void setDeque(); 
        std::deque<int> mergeSortDeque(std::deque<int> d);
        void insertSortedDeque(std::deque<int>& sorted, int value);
};

#endif