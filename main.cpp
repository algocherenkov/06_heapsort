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
    size_t left = getLeftIndex(index);
    size_t right = getRightIndex(index);
    size_t largest = 0;

    if(left < size && heap[left] > heap[index])
        largest = left;
    else
        largest = index;

    if(right < size && heap[right] > heap[largest])
        largest = right;

    if(largest != index)
    {
        Swap(heap, index, largest);
        drown(heap, largest, size);
    }
}

void drownIterative(int* heap, size_t index, size_t size)
{

    bool isSwaped = false;
    size_t left = getLeftIndex(index);
    size_t right = getRightIndex(index);
    size_t largest = 0;

    while(left < size)
    {

        if(left < size && heap[left] > heap[index])
            largest = left;
        else
            largest = index;

        if(right < size && heap[right] > heap[largest])
            largest = right;

        if(largest != index)
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

int removeMax(int* heap, size_t size)
{
    assert(size >= 1);
    int max = heap[0];
    heap[0] = heap[size - 1];
    size--;
    drown(heap, 0, size);
    return max;
}

int removeByIndex(int* heap, size_t size, size_t index)
{
    assert(size >= 1);
    int element = heap[index];
    heap[index] = heap[size - 1];
    size--;
    drown(heap, index, size);
    return element;
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

BOOST_AUTO_TEST_CASE(removeMax_test)
{
    int heap[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};
    size_t sizeTrack = sizeof (heap)/sizeof (int);
    buildHeap(heap, sizeTrack);

    while(sizeTrack > 0)
    {
        //check the heap
        for(size_t i = 0; i <= (sizeTrack - 1)/2; i++)
        {
            if(i == sizeTrack - 1)
                break;

            BOOST_CHECK_MESSAGE(heap[i] >= heap[getLeftIndex(i)], "left node: " << getLeftIndex(i) << " is not less than parent: " << i);

            if(getRightIndex(i) < sizeTrack)
                BOOST_CHECK_MESSAGE(heap[i] >= heap[getRightIndex(i)], "right node: " << getRightIndex(i) << " is not less than parent: " << i);
        }

        int element = heap[0];
        BOOST_CHECK_MESSAGE(element == removeMax(heap, sizeTrack--),"number has not highest priority");
    }

    BOOST_TEST_MESSAGE("test is done");
}

BOOST_AUTO_TEST_CASE(remove_by_index_test)
{
    int heap[12] = {9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7};
    size_t sizeTrack = sizeof (heap)/sizeof (int);
    buildHeap(heap, sizeTrack);

    while(sizeTrack > 0)
    {
        //check the heap
        for(size_t i = 0; i <= (sizeTrack - 1)/2; i++)
        {
            if(i == sizeTrack - 1)
                break;

            BOOST_CHECK_MESSAGE(heap[i] >= heap[getLeftIndex(i)], "left node: " << getLeftIndex(i) << " is not less than parent: " << i);

            if(getRightIndex(i) < sizeTrack)
                BOOST_CHECK_MESSAGE(heap[i] >= heap[getRightIndex(i)], "right node: " << getRightIndex(i) << " is not less than parent: " << i);
        }

        int element = heap[sizeTrack == 1? 0: 1];
        BOOST_CHECK_MESSAGE(element == removeByIndex(heap, sizeTrack, sizeTrack == 1? 0: 1),"number has not highest priority");
        sizeTrack--;
    }

    BOOST_TEST_MESSAGE("test is done");
}
BOOST_AUTO_TEST_SUITE_END()
