//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_STDHASH_H
#define PERFECT_HASHING_STDHASH_H

#include "HashFunction.h"

#include <functional>

class StdHash {
    unsigned long long universe_size;

public:
    explicit StdHash(unsigned long long universe_size, const std::shared_ptr<RandomGen<unsigned long long>>& randomGen) : universe_size(universe_size) {}

    StdHash() : StdHash((unsigned long int) -1, std::make_shared<PseudoRandomGen>()) {}

    [[nodiscard]] unsigned long long hash(const int& element) const {
        return std::hash<int>{}(element) % universe_size;
    }

    [[nodiscard]] size_t size() const {
        return universe_size;
    }

    [[nodiscard]] short getC() const {
        return 2;  // TODO: Find out C ??
    }

    [[nodiscard]] unsigned long long operator()(const int& element) const {
        return hash(element);
    }
};


#endif //PERFECT_HASHING_STDHASH_H
