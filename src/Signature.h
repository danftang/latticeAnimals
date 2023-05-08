//
// Created by daniel on 08/05/23.
//

#ifndef LATTICEANIMALS_SIGNATURE_H
#define LATTICEANIMALS_SIGNATURE_H

#include <cstddef>
#include <unordered_map>

class Signature {
public:
    typedef unsigned int pattern_type;

    pattern_type bitPattern; // first w bits are the occupation of the leading edge (from the bit before the MSB
                             // to the bit under the MSB, the value of the MSB is always 1),
                             // the w+1 bit is 1 if we can add a backward overhang to the MSB
    unsigned int msb; // most significant bit. Always less than w(w+1) as we don't care once we know the animal is longer than it is wide

    bool canAddBackwardOverhang(int width) const;
    bool canAddAt(int cursor) const;
    bool canFlip() const;
    void flipAssign();
    Signature backwardOverhang(int width) const;
    Signature addAt(int cursor, int width) const;
    bool operator ==(const Signature &other) const;
    std::size_t hash() const noexcept { return bitPattern; }

    void setBit(int i) { bitPattern |= (1u << i); }
    void clearBit(int i) { bitPattern &= (0xffffffffu - (1u<<i)); }
    void clearBits(int from, int to);
    bool isOccupied(int i) const { return (bitPattern & (1u<<i)) != 0; }

    // creates a horizontal bar of size width starting in the lower left corner
    static Signature initialSignature(int width);

    friend std::ostream &operator <<(std::ostream &out, const Signature &sig);
};

template<>
class std::hash<Signature> {
public:
    std::size_t operator()(const Signature &sig) const noexcept {
        return sig.hash();
    }
};



#endif //LATTICEANIMALS_SIGNATURE_H
