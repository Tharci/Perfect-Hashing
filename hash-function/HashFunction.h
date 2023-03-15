//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_HASHFUNCTION_H
#define PERFECT_HASHING_HASHFUNCTION_H

template <typename T>
class HashFunction {
public:
    // Return the hash value of the given element.
    virtual unsigned long long hash(const T& element) const = 0;

    // Return the size of the hash universe.
    [[nodiscard]] virtual size_t size() const = 0;

    [[nodiscard]] unsigned long long operator()(const T& element) const {
        return hash(element);
    }

    [[nodiscard]] virtual short getC() const = 0;
};

#endif //PERFECT_HASHING_HASHFUNCTION_H
