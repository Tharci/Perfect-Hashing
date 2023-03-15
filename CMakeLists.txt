cmake_minimum_required(VERSION 3.22)
project(perfect_hashing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
# STRING(REPLACE "/O2" "/Ox" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

add_executable(perfect_hashing main.cpp set/Set.h set/PerfectHashingSet.h set/ChainingSet.h set/RedBlackTreeSet.h hash-function/HashFunction.h hash-function/MultiplyShiftHash.h test/SetTester.h interator/StepIterator.h hash-function/StdHash.h random-gen/RandomGen.h random-gen/PseudoRandomGen.h interator/Iterator.h hash-function/SplitMixHash.h)
