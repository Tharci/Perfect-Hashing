#include <iostream>
#include <filesystem>

#include "set/RedBlackTreeSet.h"
#include "test/SetTester.h"
#include "interator/StepIterator.h"
#include "set/ChainingSet.h"
#include "hash-function/MultiplyShiftHash.h"
#include "hash-function/StdHash.h"
#include "set/PerfectHashingSet.h"
#include "hash-function/SplitMixHash.h"


int main() {
    auto redBlackTreeSet = RedBlackTreeSet<int>();
    auto retBlackTreeSetTester = SetTester("Red Black Tree default impl", redBlackTreeSet);

    ChainingSet<int, MultiplyShiftHash> chainingSet_1;
    auto chainingSetTester_1 = SetTester("Chaining, MultiplyShiftHash, m=10000", chainingSet_1);

    ChainingSet<int, StdHash> chainingSet_2;
    auto chainingSetTester_2 = SetTester("Chaining, MultiplyShiftHash, m=10000", chainingSet_2);

    ChainingSet<int, SplitMixHash> chainingSet_3;
    auto chainingSetTester_3 = SetTester("Chaining, SplitMixHash, m=10000", chainingSet_3);

    auto perfectSet = PerfectHashingSet<int, MultiplyShiftHash>();
    auto perfectSetTester = SetTester("PerfectHashingSet, MultiplyShiftHash", perfectSet);

    auto perfectSet_2 = PerfectHashingSet<int, SplitMixHash>();
    auto perfectSetTester_2 = SetTester("PerfectHashingSet, SplitMixHash", perfectSet_2);

    std::cout << "Running tests...." << std::endl << std::endl;

    for (int p = 5; p <= 22; p++) {
        auto n1 = (int) pow(2, p-1);
        auto n2 = (int) pow(2, p);
        for (int i = 0; i < 4; i++) {auto step = 100;
            auto n = n1 + (n2 - n1) / 4 * (i + 1);
            auto to =  n * step;

            std::cout << "Running tests for n = " << n << ", p = " << p << ", to = " << to << std::endl;

            auto iterator = StepIterator<int>(0, to, step);

            retBlackTreeSetTester.test(iterator.begin(), iterator.end(), n);
            chainingSetTester_1.test(iterator.begin(), iterator.end(), n);
            // chainingSetTester_2.test(iterator.begin(), iterator.end(), n);
            // chainingSetTester_3.test(iterator.begin(), iterator.end(), n);
            perfectSetTester.test(iterator.begin(), iterator.end(), n);
            // perfectSetTester_2.test(iterator.begin(), iterator.end(), n);
        }
    }

    std::cout << retBlackTreeSetTester << std::endl << std::endl;
    std::cout << chainingSetTester_1 << std::endl << std::endl;
    std::cout << chainingSetTester_2 << std::endl << std::endl;
    std::cout << chainingSetTester_3 << std::endl << std::endl;
    std::cout << perfectSetTester << std::endl << std::endl;
    std::cout << perfectSetTester_2 << std::endl << std::endl;

    // Delete files in output folder
    std::filesystem::remove_all("output");
    std::filesystem::create_directory("output");

    retBlackTreeSetTester.dumpResults("output/Red Black Tree Set.csv");
    chainingSetTester_1.dumpResults("output/Chaining Set.csv");
    // chainingSetTester_2.dumpResults("output/Chaining Set Std Hash.csv");
    // chainingSetTester_3.dumpResults("output/Chaining Set Split Mix Hash.csv");
    perfectSetTester.dumpResults("output/Perfect Hashing Set.csv");
    // perfectSetTester_2.dumpResults("output/Perfect Hashing Set Split Mix Hash.csv");

    return 0;
}
