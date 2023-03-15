//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_SET_H
#define PERFECT_HASHING_SET_H

#include "iterator"
#include "../interator/StepIterator.h"

template <typename T>
class Set {
public:
    // Check if an element is in the set.
    virtual bool contains(const T& element) const = 0;

    // Return the number of elements in the set.
    [[nodiscard]] virtual size_t size() const = 0;

    // Return true if the set is empty.
    [[nodiscard]] virtual bool isEmpty() const = 0;

    // Construct the set from iterator.
    virtual void construct(StepIterator<T> begin, StepIterator<T> end, size_t n) = 0;

    // Return the longest bucket size.
    [[nodiscard]] virtual size_t largestBucketSize() const {
        return 0;
    }
};

#endif //PERFECT_HASHING_SET_H
