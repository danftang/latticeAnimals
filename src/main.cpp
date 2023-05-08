#include <iostream>

#include "AnimalCounter.h"

int main() {
    AnimalCounter myCounter(3,5);

    std::cout << "Initial state" << std::endl;
    std::cout << myCounter << std::endl;

    myCounter.incrementArea();

    std::cout << "Final state" << std::endl;
    std::cout << myCounter << std::endl;

    return 0;
}
