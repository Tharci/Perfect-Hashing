//
// Created by tmarc on 05/03/2023.
//

#ifndef PERFECT_HASHING_PSEUDORANDOMGEN_H
#define PERFECT_HASHING_PSEUDORANDOMGEN_H

#include "RandomGen.h"

#include <random>
#include <ctime>
#include <chrono>


class PseudoRandomGen : public RandomGen<unsigned long long> {
    std::mt19937 rng;
    std::uniform_int_distribution<unsigned long long> distr;

public:
    PseudoRandomGen() {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng = std::mt19937(seed);
    }

    void seed(unsigned int seed) override {
        rng.seed(seed);
    }

    void allocate(size_t size) override {}

    unsigned long long random() override {
        return distr(rng);
    }
};

#endif //PERFECT_HASHING_PSEUDORANDOMGEN_H
