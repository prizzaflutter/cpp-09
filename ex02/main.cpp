#include "PmergeMe.hpp"

int main (int argc, char **argv){
    if (argc < 2){
        std::cout << "Error" << std::endl;
        return 1;
    }
    PmergeMe pm;
    pm.parseInput(argv);
    pm.printBefore();

    clock_t startVec = clock();
    pm.setVector();
    clock_t endVec = clock();

    
    clock_t startDeq = clock();
    pm.setDeque();
    clock_t endDeq = clock();
    
    pm.printAfter();

    double vecTime = ((double)(endVec - startVec) / CLOCKS_PER_SEC) * 1000000;
    double deqTime = ((double)(endDeq - startDeq) / CLOCKS_PER_SEC) * 1000000;

    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << vecTime << " us " << std::endl;
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque : " << deqTime << " us " << std::endl;
    return 1;
}
