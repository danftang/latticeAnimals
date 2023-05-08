// Counts the number of lattice animals of exactly a given width
// and at least width long
//
// Created by daniel on 08/05/23.
//

#ifndef LATTICEANIMALS_ANIMALCOUNTER_H
#define LATTICEANIMALS_ANIMALCOUNTER_H

#include <unordered_map>
#include <cassert>
#include "Signature.h"

class AnimalCounter {
public:
    typedef unsigned long long count_type;

    const int width;
    int n; // area to add
    std::unordered_map<Signature, count_type>   signatures; // counts of all animals by signature

    AnimalCounter(int width, int area);

    void incrementArea();
    void deleteShortSigs();

    friend std::ostream &operator <<(std::ostream &out, const AnimalCounter &counter) {
        for(const auto &sig : counter.signatures) {
            out << sig.first << " = " << sig.second << std::endl;
        }
        return out;
    }

};


#endif //LATTICEANIMALS_ANIMALCOUNTER_H
