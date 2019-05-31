#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <ctime>
#include <assert.h>
#include <fstream>
#include <math.h>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

constexpr int buff[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};

template <typename T>
class Heap {
    Heap* left{nullptr};
    T value;
    Heap* right{nullptr};
};

BOOST_AUTO_TEST_CASE(build_heap_test)
{



}

BOOST_AUTO_TEST_CASE(shell_sort_test)
{

}
BOOST_AUTO_TEST_SUITE_END()
