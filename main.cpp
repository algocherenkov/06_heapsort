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

//int heap[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};

template <typename T>
class Heap {
    Heap* left{nullptr};
    T value;
    Heap* right{nullptr};
};

void Swap(int* heap, size_t index1, size_t index2)
{
    int temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

size_t getLeftIndex(size_t parentIndex)
{
    return parentIndex*2 + 1;
}

size_t getRightIndex(size_t parentIndex)
{
    return parentIndex*2 + 2;
}

size_t getParent(size_t parentIndex)
{
    return (parentIndex - 1) / 2;
}

void drown(int* heap, size_t index, size_t size)
{
    bool leftExists = true;
    bool rightExists = true;

    size_t left = getLeftIndex(index);
    if(left >= size)
        leftExists = false;

    size_t right = getRightIndex(index);
    if(right >= size)
        rightExists = false;

    size_t largest = 0;

    if((left < size && heap[left] > heap[right]) || (left < size && !rightExists))
        largest = left;
    else
        largest = index;

    if((right < size && heap[right] > heap[largest]) || (right < size && !leftExists ))
        largest = right;

    if(largest != index && heap[index] < heap[largest])
    {
        Swap(heap, index, largest);
        drown(heap, largest, size);
    }
}

void drownIterative(int* heap, size_t index, size_t size)
{
    bool leftExists = true;
    bool rightExists = true;
    bool isSwaped = false;
    size_t left = getLeftIndex(index);
    size_t right = getRightIndex(index);

    if(left >= size)
        leftExists = false;
    if(right >= size)
        rightExists = false;

    while(leftExists)
    {
        size_t largest = 0;
        if((left < size && heap[left] > heap[right]) || (left < size && !rightExists))
            largest = left;
        else
            largest = index;

        if((right < size && heap[right] > heap[largest]) || (right < size && !leftExists ))
            largest = right;

        if(largest != index && heap[index] < heap[largest])
        {
            Swap(heap, index, largest);
            isSwaped = true;
        }

        if(!isSwaped)
            break;

        isSwaped = false;

        index = largest;
        left = getLeftIndex(index);
        right = getRightIndex(index);
        leftExists = true;
        rightExists = true;

        if(left >= size)
            leftExists = false;
        if(right >= size)
            rightExists = false;
    }
}

void buildHeap(int* heap, size_t size)
{
    for(int i = static_cast<int>((size - 1)/2); i >= 0; i--)
        drown(heap, static_cast<size_t>(i), size);
}

void buildHeapIterativeDrown(int* heap, size_t size)
{
    for(int i = static_cast<int>((size - 1)/2); i >= 0; i--)
        drownIterative(heap, static_cast<size_t>(i), size);
}

void heapSort(int* heap, size_t size)
{
    buildHeap(heap, size);
    for(size_t i = size; i >= 1; i--)
    {
        Swap(heap, i - 1, 0);
        drown(heap, 0, i - 1);
    }
}

BOOST_AUTO_TEST_CASE(build_heap_test)
{    
    int heap[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};
    size_t size = sizeof (heap)/sizeof (int);
    buildHeap(heap, size);
    for(size_t i = 0; i <= (size - 1)/2; i++)
    {
        BOOST_CHECK_MESSAGE(heap[i] >= heap[getLeftIndex(i)], "left node: " << getLeftIndex(i) << " is not less than parent: " << i);

        if(getRightIndex(i) < size)
            BOOST_CHECK_MESSAGE(heap[i] >= heap[getRightIndex(i)], "right node: " << getRightIndex(i) << " is not less than parent: " << i);
    }
    BOOST_TEST_MESSAGE("test is done");
}

BOOST_AUTO_TEST_CASE(build_heap_with_iterative_drown_test)
{
    int heap[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};
    size_t size = sizeof (heap)/sizeof (int);
    buildHeapIterativeDrown(heap, size);
    for(size_t i = 0; i <= (size - 1)/2; i++)
    {
        BOOST_CHECK_MESSAGE(heap[i] >= heap[getLeftIndex(i)], "left node: " << getLeftIndex(i) << " is not less than parent: " << i);

        if(getRightIndex(i) < size)
            BOOST_CHECK_MESSAGE(heap[i] >= heap[getRightIndex(i)], "right node: " << getRightIndex(i) << " is not less than parent: " << i);
    }
    BOOST_TEST_MESSAGE("test is done");
}

BOOST_AUTO_TEST_CASE(sort_heap_test)
{
    int heap[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};
    size_t size = sizeof (heap)/sizeof (int);
    heapSort(heap, size);
    for(size_t i = 0; i <= (size - 1)/2; i++)
    {
        if(i == size - 1)
            break;
        BOOST_CHECK_MESSAGE(heap[i] <= heap[i + 1], "heap wasn't sorted");
    }
    BOOST_TEST_MESSAGE("test is done");
}
BOOST_AUTO_TEST_SUITE_END()
