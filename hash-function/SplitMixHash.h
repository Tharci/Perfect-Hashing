//
// Created by tmarc on 07/03/2023.
//

#ifndef PERFECT_HASHING_SPLITMIXHASH_H
#define PERFECT_HASHING_SPLITMIXHASH_H

#include "HashFunction.h"
#include "../random-gen/RandomGen.h"
#include "../random-gen/PseudoRandomGen.h"

#include <chrono>

class SplitMixHash {
    unsigned long long universe_size;
    unsigned long long seed;
    unsigned int l;

public:

    static unsigned long long splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    explicit SplitMixHash(unsigned long long universe_size,
                          const std::shared_ptr<RandomGen<unsigned long long>>& randomGen) : universe_size(universe_size) {
        this->seed = randomGen->random();
        l = (int) std::log2(universe_size);
    }

    SplitMixHash() : SplitMixHash((unsigned long int) -1, std::make_shared<PseudoRandomGen>()) {}

    [[nodiscard]] unsigned long long hash(const int& element) const {
        return splitmix64(seed + element) >> (64 - l);
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

#endif //PERFECT_HASHING_SPLITMIXHASH_H
