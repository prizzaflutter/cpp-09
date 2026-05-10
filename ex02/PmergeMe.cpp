#include "PmergeMe.hpp"
#include <climits>
#include <cstdlib>
#include <ctime>

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other): vec(other.vec), deq(other.deq){}

PmergeMe& PmergeMe::operator=(const PmergeMe& other){
    if (this != &other){
        vec = other.vec;
        deq = other.deq;
    }
    return *this;
}

PmergeMe::~PmergeMe(){}

bool PmergeMe::isValidNumber(const std::string& str) {
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.size(); i++){
        if (!std::isdigit(str[i]))
            return false;
    }
    if (str.size() > 10)
        return false;
    if (str.size() == 10 && str > "2147483647")
        return false;
    int value = std::atoi(str.c_str());
    if (value > INT_MAX)
        return false;
    return true;
}

void PmergeMe::parseInput(char **argv){
    for (int i = 1; argv[i]; i++){
        std::string str = argv[i];
        if (!isValidNumber(str)){
            std::cout << "Error" << std::endl;
            exit(1);
        }
        int num = std::atoi(str.c_str());
        vec.push_back(num);
        deq.push_back(num);
    }
}

void PmergeMe::printBefore() const {
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printAfter() const {
    std::cout << "Afeter: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::insertSorted(std::vector<int>& sorted, int value){
    std::vector<int>::iterator it = sorted.begin();
    while (it != sorted.end() && *it < value)
        ++it;
    sorted.insert(it, value);
}

std::vector<int> PmergeMe::mergeSortVector(std::vector<int> v){
    if (v.size() <= 1)
        return v;
    std::vector<int> left;
    std::vector<int> right;

    size_t midle = v.size() / 2;
    for (size_t i = 0; i < midle; i++)
        left.push_back(v[i]);
    for (size_t i = midle; i < v.size(); i++)
        right.push_back(v[i]);
    left = mergeSortVector(left);
    right = mergeSortVector(right);

    std::vector<int> result;
    for(size_t i = 0; i < left.size(); i++)
        result.push_back(left[i]);
    for(size_t i = 0; i < right.size(); i++)
        insertSorted(result, right[i]);
    return result;
}

void PmergeMe::setVector(){
    vec = mergeSortVector(vec);
}


void PmergeMe::insertSortedDeque(std::deque<int>& sorted, int value){
    std::deque<int>::iterator it = sorted.begin();
    while(it != sorted.end() && *it < value)
        ++it;
    sorted.insert(it, value);
}

std::deque<int>  PmergeMe::mergeSortDeque(std::deque<int> d){
    if (d.size() <= 1)
        return d;

    std::deque<int> left;
    std::deque<int> right;

    size_t midle = d.size() / 2;
    
    for (size_t i = 0; i < midle; i++)
        left.push_back(d[i]);
    
    for (size_t i = midle; i < d.size(); i++)
        right.push_back(d[i]);

    left = mergeSortDeque(left);
    right = mergeSortDeque(right);

    std::deque<int> result;
    for(size_t i = 0; i < left.size(); i++)
        result.push_back(left[i]);
    for(size_t i = 0; i < right.size(); i++)
        insertSortedDeque(result, right[i]);
    return result;
}

void PmergeMe::setDeque(){
    deq = mergeSortDeque(deq);
}
