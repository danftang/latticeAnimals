//
// Created by daniel on 08/05/23.
//

#include <cassert>
#include <ostream>
#include <bitset>
#include "Signature.h"

Signature Signature::initialSignature(int width) {
    Signature sig;
    sig.bitPattern = 0;
    for(int i =0; i<width; ++i) {
        sig.bitPattern <<= 1;
        sig.bitPattern++;
    }
    sig.msb = width;
    return sig;
}

bool Signature::operator==(const Signature &other) const {
    return bitPattern == other.bitPattern && msb == other.msb;
}

// true if pattern surrounding MSB is
bool Signature::canAddBackwardOverhang(int width) const {
    return bitPattern >> width;
}

Signature Signature::backwardOverhang(int width) const {
    Signature withOverhang(*this);
    withOverhang.setBit(msb-1);
    withOverhang.clearBit(width+1);
    return withOverhang;
}

bool Signature::canAddAt(int cursor) const {
    return cursor == msb+1 || cursor == msb || isOccupied(cursor);
}

// Adds a block on column cursor, on the row above the msb if cursor <= msb
// or on the same row as msb if cursor > msb
Signature Signature::addAt(int cursor, int width) const {
    Signature modifiedSignature(*this);
    // set canAddBackwardOverhang bit
    if(cursor != msb+1 && cursor != msb+2 && cursor > 1 && !isOccupied(cursor-1)) {
        modifiedSignature.setBit(width+1);
    } else {
        modifiedSignature.clearBit(width+1);
    }
    if(cursor <= msb) {
        // delete everything before the cursor and everything after the MSB
        // and set the old MSB to one
        modifiedSignature.clearBits(0, cursor-1);
        modifiedSignature.clearBits(msb+1, width);
        modifiedSignature.setBit(msb);
    } else {
        // delete everything between the msb and the cursor
        modifiedSignature.clearBits(msb+1, cursor-1);
    }
    modifiedSignature.msb = cursor;
    return modifiedSignature;
}

// inclusive on both ends
void Signature::clearBits(int from, int to) {
    int nBitsToDelete = to-from+1;
    pattern_type mask = ((1u << nBitsToDelete) - 1) << from;
    bitPattern &= 0xffffffffu - mask;
}

// true if we can do a flip at the current MSB
// this can occur if all bits in view from the right of the MSB are 1
bool Signature::canFlip() const {
    return (msb == 0 && ((bitPattern & 3) == 3)) || (((bitPattern >> (msb-1)) & 7) == 7);
}

// flip the bit under the current MSB up
void Signature::flipAssign() {
    assert(isOccupied(msb) && isOccupied(msb+1));
    setBit(msb); // old MSB bit moves up
    msb++;
}

std::ostream &operator<<(std::ostream &out, const Signature &sig) {
    out << std::bitset<32>(sig.bitPattern) << ":" << sig.msb;
    return out;
}
