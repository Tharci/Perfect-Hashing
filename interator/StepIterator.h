//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_STEPITERATOR_H
#define PERFECT_HASHING_STEPITERATOR_H

#include "iterator"


template<typename T>
class StepIterator : public std::iterator<std::input_iterator_tag, T> {
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

    bool operator==(const StepIterator& rhs) const {
        return value == rhs.value;
    }

    bool operator!=(const StepIterator& rhs) const {
        return !(rhs == *this);
    }

    T operator*() const {
        return value;
    }

    StepIterator begin() {
        return StepIterator(from, from, to, step);
    }

    StepIterator end() {
        return StepIterator(to, from, to, step);
    }
};



#endif //PERFECT_HASHING_STEPITERATOR_H
