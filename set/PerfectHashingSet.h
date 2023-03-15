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
    std::vector<std::pair<bool, T>> data;

    DataElement(const HashFn& hashFn, const std::vector<std::pair<bool, T>>& data) : hashFn(hashFn), data(std::move(data)) {}

    // Move constructor.
    DataElement(DataElement&& other) noexcept : hashFn(other.hashFn), data(std::move(other.data)) {}

    // Move assignment.
    DataElement& operator=(DataElement&& other) noexcept {
        hashFn = other.hashFn;
        data = std::move(other.data);
        return *this;
    }

    // Copy constructor.
    DataElement(const DataElement& other) : hashFn(other.hashFn), data(other.data) {}

    // Copy assignment.
    DataElement& operator=(const DataElement& other) {
        hashFn = other.hashFn;
        data = other.data;
        return *this;
    }

    bool contains(const T& element) const {
        if (data.empty()) return false;

        auto [b, dataElement] = data[hashFn.hash(element)];
        return b && dataElement == element;
    }
};


template <typename T, typename HashFn>
class PerfectHashingSet : public Set<T> {
    HashFn hashFn;
    std::vector<DataElement<T, HashFn>> data;
    size_t elementCnt = 0;
    std::shared_ptr<RandomGen<unsigned long long>> randomGen = std::make_shared<PseudoRandomGen>();

public:
    // Construct the set from iterator.
    void construct(StepIterator<T> begin, StepIterator<T> end, size_t n) override {
        this->elementCnt = n;

        auto m = (size_t) (4 * HashFn(1, randomGen).getC() * n);
        data.clear();

        while (true) {
            ChainingSet<T, HashFn> tmp_a;
            tmp_a.construct(begin, end, m);

            if (tmp_a.numberOfCollisions() > n/2.) {
                std::cout << "[" << typeid(HashFn).name() << "]" "FAIL 1. Retrying..." << std::endl;
                continue;
            }

            hashFn = tmp_a.getHashFn();
            data.reserve(m);

            for (size_t i = 0; i < m; i++) {
                const auto& list = tmp_a.getData()[i];
                while (true) {
                    auto [success, dataElement] = hash_subarray(list);
                    if (success) {
                        data.push_back(std::move(dataElement));
                        break;
                    }
                }
            }

            return;
        }
    }

    std::pair<bool, DataElement<T, HashFn>> hash_subarray(const std::list<T>& list) {
        auto m_i = 2 * hashFn.getC() * (unsigned long long) pow(list.size(), 2);
        auto h = HashFn(m_i, randomGen);
        auto b = std::vector<std::pair<bool, T>>(h.size());

        for (const auto& element : list) {
            auto j = h(element);
            if (b[j].first) {
                std::cout << "[" << typeid(HashFn).name() << "]" "FAIL 2. Retrying..." << std::endl;
                return {false, DataElement<T, HashFn>(h, {})};
            }

            b[j] = {true, element};
        }

        return {true, DataElement<T, HashFn>(h, b)};
    }

    // Check if an element is in the set.
    bool contains(const T& element) const override {
        return data[hashFn.hash(element)].contains(element);
    }

    // Return the number of elements in the set.
    [[nodiscard]] size_t size() const override {
        return elementCnt;
    }

    // Return true if the set is empty.
    [[nodiscard]] bool isEmpty() const override {
        return elementCnt == 0;
    }

    // Return the longest bucket size.
    [[nodiscard]] size_t largestBucketSize() const override {
        auto comp = [&](const DataElement<T, HashFn>& a, const DataElement<T, HashFn>& b) {
            return a.data.size() < b.data.size();
        };

        return std::max_element(data.begin(), data.end(), comp)->data.size();
    }
};

#endif //PERFECT_HASHING_PERFECTHASHINGSET_H
