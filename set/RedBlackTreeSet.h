//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_REDBLACKTREESET_H
#define PERFECT_HASHING_REDBLACKTREESET_H

#include "Set.h"

#include <set>

template <typename T>
class RedBlackTreeSet : public Set<T> {
    std::set<T> data;

public:
    // Add an element to the set.
    void add(const T& element) {
        data.insert(element);
    }

    // Remove an element from the set.
    void remove(const T& element) {
        data.erase(element);
    }

    // Check if an element is in the set.
    bool contains(const T& element) const override {
        return data.contains(element);
    }

    // Return the number of elements in the set.
    [[nodiscard]] size_t size() const override {
        return data.size();
    }

    // Return true if the set is empty.
    [[nodiscard]] bool isEmpty() const override {
        return data.empty();
    }

    // Remove all elements from the set.
    void clear() {
        data.clear();
    }

    // Construct the set from iterator.
    void construct(StepIterator<T> begin, StepIterator<T> end, size_t n) override {
        clear();

        for (auto it = begin; it != end; ++it) {
            add(*it);
        }
    }
};

#endif //PERFECT_HASHING_REDBLACKTREESET_H
