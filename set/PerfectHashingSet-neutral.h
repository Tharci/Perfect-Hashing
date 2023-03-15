//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_PERFECTHASHINGSET_H
#define PERFECT_HASHING_PERFECTHASHINGSET_H

#include "Set.h"
#include "ChainingSet.h"

#include <vector>
#include <cmath>


template <typename T, typename HashFn>
struct DataElement {
    HashFn hashFn;
    std::vector<T> data;

    DataElement(const HashFn& hashFn, const std::vector<T>& data) : hashFn(hashFn), data(std::move(data)) {}

    bool contains(const T& element) const {
        return data[hashFn(element)] == element;
    }
};


template <typename T, typename HashFn>
class PerfectHashingSet : public Set<T> {
    HashFn hashFn;
    std::vector<DataElement<T, HashFn>> data;
    size_t elementCnt = 0;

public:
    // Construct the set from iterator.
    void construct(StepIterator<T> begin, StepIterator<T> end, size_t n) override {
        this->elementCnt = n;

        size_t m = 4 * HashFn(1).getC() * n;
        data.clear();
        data.reserve(m);

        while (true) {
            hashFn = HashFn(m);
            ChainingSet<T> tmp_a(hashFn);

            for (auto it = begin; it != end; ++it) {
                tmp_a.add(*it);
            }

            if (tmp_a.numberOfCollisions() > n/2.) {
                continue;
            }

            for (size_t i = 0; i < m; i++) {
                const auto& list = tmp_a.getData()[i];

                while (true) {
                    auto [success, dataElement] = hash_subarray(list);
                    if (success) {
                        data.push_back(dataElement);
                        break;
                    }
                }
            }

            return;
        }
    }

    std::pair<bool, DataElement<T, HashFn>> hash_subarray(const std::list<T>& list) {
        auto m_i = 2 * hashFn.getC() * (unsigned long long) pow(list.size(), 2);
        auto h = HashFn(m_i);
        auto b = std::vector<T>(h.size());
        auto neutral_element = T();

        for (const auto& element : list) {
            auto j = h(element);
            if (b[j] != neutral_element) {
                return {false, DataElement<T, HashFn>(h, {})};
            }

            b[j] = element;
        }

        return {true, DataElement<T, HashFn>(h, b)};
    }

    // Check if an element is in the set.
    bool contains(const T& element) const override {
        return data[hashFn(element)].contains(element);
    }

    // Return the number of elements in the set.
    [[nodiscard]] size_t size() const override {
        return elementCnt;
    }

    // Return true if the set is empty.
    [[nodiscard]] bool isEmpty() const override {
        return elementCnt == 0;
    }
};

#endif //PERFECT_HASHING_PERFECTHASHINGSET_H
