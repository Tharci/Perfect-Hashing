//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_SETTESTER_H
#define PERFECT_HASHING_SETTESTER_H

#include "../set/Set.h"
#include "../set/ChainingSet.h"

#include <chrono>
#include <utility>
#include <fstream>


struct SetTesterResult {
    size_t size;
    long long insertionTime;
    long long queryTime;
    size_t largest_bucket_size = 0;

    friend std::ostream& operator<<(std::ostream& os, const SetTesterResult& result) {
        os << "Size: " << result.size << std::endl;
        os << "Insertion time: " << (double) result.insertionTime * 10e-6 << "ms" << std::endl;
        os << "Query time: " << (double) result.queryTime * 10e-6 << "ms" << std::endl;
        os << "Overall time: " << (double) (result.insertionTime + result.queryTime) * 10e-6 << "ms" << std::endl;
        if (result.largest_bucket_size > 0) {
            os << "Largest bucket size: " << result.largest_bucket_size << std::endl;
        }
        return os;
    }
};


template <typename T>
class SetTester {
    std::string name;
    Set<T>& set;
    std::vector<SetTesterResult> results;

public:
    explicit SetTester(std::string name, Set<T>& set) : name(std::move(name)), set(set) {}

    template <typename Iterator>
    SetTesterResult test(Iterator begin, Iterator end, size_t n) {
        auto insertionStart = std::chrono::high_resolution_clock::now();
        set.construct(begin, end, n);
        auto insertionEnd = std::chrono::high_resolution_clock::now();
        auto insertionTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
                insertionEnd - insertionStart).count();

        auto queryStart = std::chrono::high_resolution_clock::now();
        for (auto it = begin; it != end; ++it) {
            auto contains = set.contains(*it);
            if (!contains) {
                throw std::runtime_error("SetTester: Set should contain all the inserted elements.");
            }
        }
        auto queryEnd = std::chrono::high_resolution_clock::now();
        auto queryTime = std::chrono::duration_cast<std::chrono::nanoseconds>(queryEnd - queryStart).count();

        auto largest_bucket_size = set.largestBucketSize();

        SetTesterResult result = {
                .size = set.size(),
                .insertionTime = insertionTime,
                .queryTime = queryTime,
                .largest_bucket_size = largest_bucket_size
        };

        results.push_back(result);
        return result;
    }

    [[nodiscard]] const std::vector<SetTesterResult>& getResults() const {
        return results;
    }

    friend std::ostream& operator<<(std::ostream& os, const SetTester& tester) {
        os << "[TEST] " << tester.name << std::endl;
        auto i = 1;
        for (const auto& result : tester.results) {
            os << "------ RUN " << i << " ------" << std::endl << result << std::endl;
            i++;
        }
        return os;
    }

    //Dump results to a file
    void dumpResults(const std::string& filename) {
        std::ofstream file;
        file.open(filename);

        file << "Size\tInsertion time (ns)\tQuery time (ns)\tLargest bucket" << std::endl;
        for (const auto& result : results) {
            file << result.size << "\t" << result.insertionTime << "\t" << result.queryTime << "\t" << result.largest_bucket_size << std::endl;
        }

        file.close();
    }

};

#endif //PERFECT_HASHING_SETTESTER_H
