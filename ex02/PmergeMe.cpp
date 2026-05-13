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

// void PmergeMe::insertSorted(std::vector<int>& sorted, int value){
//     std::vector<int>::iterator it = sorted.begin();
//     while (it != sorted.end() && *it < value)
//         ++it;
//     sorted.insert(it, value);
// }

void PmergeMe::binaryInsertVector(std::vector<int>& chain, int value){
    std::vector<int>::iterator position;
    position = std::lower_bound(chain.begin(), chain.end(), value);
    chain.insert(position, value);
}

std::vector<int> PmergeMe::fordJohnsonVector(std::vector<int> v){
    if(v.size() <= 1)
        return v;

    std::vector<std::pair<int, int> > pairs;
    size_t i = 0;
    while (i + 1 < v.size()){
        int a = v[i];
        int b = v[i + 1];

        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
        i += 2;
    }

    bool hasStraggler = false;
    int straggler = 0;
    if (v.size() % 2 != 0){
        hasStraggler = true;
        straggler = v.back();
    }

    std::vector<int> mainChain;
    std::vector<int> pendingChain;

    for (size_t i = 0; i < pairs.size(); i++){
        pendingChain.push_back(pairs[i].first);
        mainChain.push_back(pairs[i].second);
    }
    mainChain = fordJohnsonVector(mainChain);
    if (!pendingChain.empty())
        binaryInsertVector(mainChain, pendingChain[0]);
    std::vector<int> order = buildJacobsthalOrderVector(pendingChain.size());
    for (size_t i = 0; i < order.size(); i++){
        if(order[i] == 0)
            continue;
        binaryInsertVector(mainChain, pendingChain[order[i]]);
    }
    if (hasStraggler)
        binaryInsertVector(mainChain, straggler);
    return mainChain;
}

/// how jacobsthal indices generate with this formula : Jn​=Jn−1​+2Jn−2

std::vector<int> PmergeMe::buildJacobsthalOrderVector(size_t size){
    std::vector<int> order;
    if (size <= 1)
        return order;
    
    std::vector<int> jac;
    
    jac.push_back(0);
    jac.push_back(1);
    
    while(jac.back() < (int)size){
        int next = jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
        jac.push_back(next);
    }
    std::vector<bool> used(size, false);
    for (size_t i = 1; i < jac.size(); i++){
        int index = jac[i];
        if (index < (int)size && !used[index]){
            order.push_back(index);
            used[index] = true;
        }
    }
    for (size_t i = 0; i < size; i++){
        if (!used[i])
            order.push_back(i);
    }
    return order;
}


void PmergeMe::setVector(){
    vec = fordJohnsonVector(vec);
}


void PmergeMe::binaryInsertDeque(std::deque<int>& chain, int value){
    std::deque<int>::iterator position;
    position = std::lower_bound(chain.begin(), chain.end(), value);
    chain.insert(position, value);
}

std::deque<int> PmergeMe::fordJohnsonDeque(std::deque<int> v){
    if(v.size() <= 1)
        return v;

    std::deque<std::pair<int, int> > pairs;
    size_t i = 0;
    while (i + 1 < v.size()){
        int a = v[i];
        int b = v[i + 1];

        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
        i += 2;
    }

    bool hasStraggler = false;
    int straggler = 0;
    if (v.size() % 2 != 0){
        hasStraggler = true;
        straggler = v.back();
    }

    std::deque<int> mainChain;
    std::deque<int> pendingChain;

    for (size_t i = 0; i < pairs.size(); i++){
        pendingChain.push_back(pairs[i].first);
        mainChain.push_back(pairs[i].second);
    }
    mainChain = fordJohnsonDeque(mainChain);
    if (!pendingChain.empty())
        binaryInsertDeque(mainChain, pendingChain[0]);
    std::deque<int> order = buildJacobsthalOrderDeque(pendingChain.size());
    for (size_t i = 0; i < order.size(); i++){
        if(order[i] == 0)
            continue;
        binaryInsertDeque(mainChain, pendingChain[order[i]]);
    }
    if (hasStraggler)
        binaryInsertDeque(mainChain, straggler);
    return mainChain;
}


std::deque<int> PmergeMe::buildJacobsthalOrderDeque(size_t size){
    std::deque<int> order;
    if (size <= 1)
        return order;
    
    std::deque<int> jac;
    
    jac.push_back(0);
    jac.push_back(1);
    
    while(jac.back() < (int)size){
        int next = jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
        jac.push_back(next);
    }
    std::deque<bool> used(size, false);
    for (size_t i = 1; i < jac.size(); i++){
        int index = jac[i];
        if (index < (int)size && !used[index]){
            order.push_back(index);
            used[index] = true;
        }
    }
    for (size_t i = 0; i < size; i++){
        if (!used[i])
            order.push_back(i);
    }
    return order;
}


void PmergeMe::setDeque(){
    deq = fordJohnsonDeque(deq);
}
