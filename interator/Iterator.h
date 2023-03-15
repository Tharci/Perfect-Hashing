//
// Created by tmarc on 05/03/2023.
//

#ifndef PERFECT_HASHING_ITERATOR_H
#define PERFECT_HASHING_ITERATOR_H

/*
// Abstract class for iterators.
template<typename T>
class Iterator {
    T value;
    const T from;
    const T to;
    const T step;

public:
    explicit StepIterator(T value, T from, T to, T step) : value(value), from(from), to(to), step(step) {}

    explicit StepIterator(T from, T to, T step) : StepIterator(from, from, to, step) {}

    StepIterator& operator++() {
        value += step;

        if (value > to) {
            value = to;
        }

        return *this;
    }

    StepIterator operator++(int) {
        StepIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    virtual bool operator==(const StepIterator& rhs) const = 0;

    virtual bool operator!=(const StepIterator& rhs) const = 0;

    virtual T operator*() const = 0;

    virtual Iterator begin() = 0;

    virtual Iterator end() = 0;
};
*/

#endif //PERFECT_HASHING_ITERATOR_H
