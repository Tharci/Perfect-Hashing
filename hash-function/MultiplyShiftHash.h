//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_MULTIPLYSHIFTHASH_H
#define PERFECT_HASHING_MULTIPLYSHIFTHASH_H

#include "HashFunction.h"
#include "../random-gen/PseudoRandomGen.h"

#include <cmath>


class MultiplyShiftHash {
    unsigned long long universe_size;
    unsigned long long a;
    unsigned int l;

public:

    explicit MultiplyShiftHash(unsigned long long universe_size,
                               const std::shared_ptr<RandomGen<unsigned long long>>& randomGen) : universe_size(universe_size) {
        a = randomGen->random();
        l = (int) std::log2(universe_size);
    }

    MultiplyShiftHash() : MultiplyShiftHash((unsigned long int) -1, std::make_shared<PseudoRandomGen>()) {}

    [[nodiscard]] unsigned long long hash(const int& element) const {
        return (a * element) >> (64 - l);
    }

    [[nodiscard]] size_t size() const {
        return universe_size;
    }

    [[nodiscard]] short getC() const {
        return 2;
    }

    [[nodiscard]] unsigned long long operator()(const int& element) const {
        return hash(element);
    }
};

#endif //PERFECT_HASHING_MULTIPLYSHIFTHASH_H
