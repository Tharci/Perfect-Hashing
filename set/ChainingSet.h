//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_CHAININGSET_H
#define PERFECT_HASHING_CHAININGSET_H

#include "Set.h"
#include "../hash-function/HashFunction.h"
#include "../random-gen/PseudoRandomGen.h"

#include <vector>
#include <functional>
#include <list>


template <typename T, typename HashFn>
class ChainingSet : public Set<T> {
    std::vector<std::list<T>> data;
    std::vector<size_t> elementCounts;
    std::shared_ptr<PseudoRandomGen> randomGen = std::make_shared<PseudoRandomGen>();
    HashFn hashFunction {0, randomGen};
    size_t elemCnt = 0;
    size_t collisionCnt = 0;

public:
    // Add an element to the set.
    void add(const T& element) {
        auto i = hashFunction(element);
        auto& list = data[i];
        if (std::find(list.begin(), list.end(), element) == list.end()) {
            list.push_back(element);
            elemCnt++;
            elementCounts[i]++;
            collisionCnt += elementCounts[i] - 1;
        }
    }

    // Remove an element from the set.
    void remove(const T& element) {
        auto i = hashFunction(element);
        auto& list = data[i];
        if (auto it = std::find(list.begin(), list.end(), element); it != list.end()) {
            list.erase(it);
            elemCnt--;
            elementCounts[i]--;
            collisionCnt -= elementCounts[i];
        }
    }

    // Check if an element is in the set.
    bool contains(const T& element) const override {
        const auto& list = data[hashFunction(element)];
        return std::find(list.begin(), list.end(), element) != list.end();
    }

    // Return the number of elements in the set.
    [[nodiscard]] size_t size() const override {
        return elemCnt;
    }

    // Return true if the set is empty.
    [[nodiscard]] bool isEmpty() const override {
        return elemCnt == 0;
    }

    // Remove all elements from the set.
    void clear() {
        data.clear();
        data.resize(hashFunction.size());
        elementCounts.clear();
        elementCounts.resize(hashFunction.size());
        elemCnt = 0;
        collisionCnt = 0;
    }

    // Return the longest bucket size.
    [[nodiscard]] size_t largestBucketSize() const override {
        return *std::max_element(elementCounts.begin(), elementCounts.end());
    }

    [[nodiscard]] size_t numberOfCollisions() const {
        return collisionCnt;
    }

    // Get data.
    [[nodiscard]] const std::vector<std::list<T>>& getData() const {
        return data;
    }

    // Construct the set from iterator.
    void construct(StepIterator<T> begin, StepIterator<T> end, size_t m) override {
        hashFunction = HashFn {m, randomGen};

        clear();

        for (auto it = begin; it != end; ++it) {
            add(*it);
        }
    }

    [[nodiscard]] HashFn getHashFn() const {
        return hashFunction;
    }
};

#endif //PERFECT_HASHING_CHAININGSET_H
