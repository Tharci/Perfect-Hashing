//
// Created by tmarc on 05/03/2023.
//

#ifndef PERFECT_HASHING_RANDOMGEN_H
#define PERFECT_HASHING_RANDOMGEN_H

#include<chrono>

template <typename T>
class RandomGen {
public:
    // Return a random element.
    virtual T random() = 0;

    // Seed the generator.
    virtual void seed(unsigned int seed) = 0;

    // Allocate n elements.
    virtual void allocate(size_t size) = 0;
};

#endif //PERFECT_HASHING_RANDOMGEN_H
