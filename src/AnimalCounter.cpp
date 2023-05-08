//
// Created by daniel on 08/05/23.
//

#include <iostream>
#include "AnimalCounter.h"

AnimalCounter::AnimalCounter(int width, int area) : width(width), n(area-width) {
    assert(n >= width -1); // otherwise there are no solutions that are at least as long as wide
    signatures[Signature::initialSignature(width)] = 1;
}

void AnimalCounter::incrementArea() {
    std::unordered_map<Signature, count_type> nplus1Signatures;
    for(const auto &sigCount : signatures) {
        const Signature & currentSignature = sigCount.first;
        const count_type & currentCount = sigCount.second;
        std::cout << "Considering " << currentSignature << " = " << currentCount << std::endl;
        if(currentSignature.canAddBackwardOverhang(width)) {
            std::cout << "adding overhang" << std::endl;
            nplus1Signatures[currentSignature.backwardOverhang(width)] += currentCount;
        }
        for(int cursor = 0; cursor < width; ++cursor) {
            if(currentSignature.canAddAt(cursor)) {
                std::cout << "Adding bit at " << cursor << std::endl;
                Signature newSignature = currentSignature.addAt(cursor, width);
                nplus1Signatures[newSignature] += currentCount;
                while(newSignature.canFlip()) {
                    std::cout << "Flipping " << newSignature << std::endl;
                    newSignature.flipAssign();
                    nplus1Signatures[newSignature] += currentCount;
                }
            }
        }
    }


    signatures = std::move(nplus1Signatures);
    n-=1;
    // delete any signatures that are too short
    deleteShortSigs();
}


void AnimalCounter::deleteShortSigs() {
    // TODO: ...
}

