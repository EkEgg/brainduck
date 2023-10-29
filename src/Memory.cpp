#include "Memory.h"
#include "Configuration.h"
#include <iostream>
#include <algorithm>
#include <sstream>

unsigned char* array;
size_t arraySize;
size_t index;
size_t leftBoundary;
size_t rightBoundary;

size_t nextArraySize(void);

void expandArray(void);

void Memory::initialize(void)
{
    arraySize = Configuration::initialMemorySize();
    try
    {
        array = new unsigned char[arraySize]();
    }
    catch(const std::bad_alloc& e)
    {
        throw NoMemoryForProgramMemory(arraySize);
    }
    index = 0;
    leftBoundary = 0;
    rightBoundary = arraySize;
}

void Memory::destroy(void)
{
    delete[] array;
}

size_t nextArraySize(void)
{
    size_t newArraySize = Configuration::memoryGrowthFactor() * arraySize;
    newArraySize = std::max(newArraySize, arraySize+1);
    return newArraySize;
}

void expandArray(void)
{
    size_t newArraySize = nextArraySize();
    unsigned char* newArray;
    size_t i = 0;
    try
    {
        newArray = new unsigned char[newArraySize]();
    }
    catch(const std::bad_alloc& e)
    {
        throw Memory::NoMemoryForProgramMemory(newArraySize);
    }
    for(size_t j = 0; j <= leftBoundary; j++)
    {
        newArray[i] = array[j];
        i++;
    }
    i = newArraySize-1;
    for(size_t j = arraySize-1; j >= rightBoundary; j--)
    {
        newArray[i] = array[j];
        i--;
    }
    if(index >= rightBoundary) index += newArraySize - arraySize;
    rightBoundary = i+1;
    delete[] array;
    array = newArray;
    arraySize = newArraySize;
}

void Memory::incrementCell(void)
{
    array[index]++;
}

void Memory::decrementCell(void)
{
    array[index]--;
}

void Memory::incrementIndex(void)
{
    if(Configuration::memoryType() == Configuration::MemoryType::CIRCULAR)
    {
        index++;
        if(index == arraySize) index = 0;
        return;
    }
    if(index + 1 == rightBoundary) expandArray();
    index++;
    if(index == arraySize) index = 0;
    if(index < rightBoundary) leftBoundary = std::max(leftBoundary, index);
}

void Memory::decrementIndex(void)
{
    if(Configuration::memoryType() == Configuration::MemoryType::CIRCULAR)
    {
        if(index == 0) index = arraySize-1;
        else index--;
        return;
    }
    if(index >= rightBoundary)
    {
        if(index - 1 == leftBoundary) expandArray();
        index--;
        rightBoundary = std::min(rightBoundary, index);
        return;
    }
    if(index == 0)
    {
        if(arraySize - 1 == leftBoundary) expandArray();
        index = arraySize - 1;
        rightBoundary = std::min(rightBoundary, index);
        return;
    }
    index--;
}

void Memory::readCell(void)
{
    std::cin >> array[index];
}

void Memory::printCell(void)
{
    std::cout << array[index];
}

bool Memory::isCellZero(void)
{
    return array[index] == 0;
}

Memory::NoMemoryForProgramMemory::NoMemoryForProgramMemory(size_t newMemorySize) :
        std::runtime_error((std::ostringstream() << "Could not allocate program memory with "
                                                 << newMemorySize << " bytes.").str().c_str())
        {}
