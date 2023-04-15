#pragma once
#include <cstdlib>
#include <string>
#include <fstream>

class Utility
{
private:

public:

    static constexpr int valueToInitialize = 0;
    
    // initializes array with valueToInitialize
    static int *initializeArray(size_t size);

    // reads integer from in, puts it into destination. If something went wrong returns false
    static bool readPositiveInteger(
        std::istream &in,
        std::ostream &out,
        size_t &destination,
        const std::string &inputPrompt,
        const std::string &inputFailedPrompt);

    // outputs array to out
    static void outputArray(std::ostream &out, const int *array, const size_t &size);

    // outputs working markers
    static void outputMarkers(std::ostream &out, const int *finish, const size_t &markerCount);

    // inputs working marker id
    static size_t inputWorkingMarkerId(
        std::istream &in,
        std::ostream &out,
        const int *finish,
        const size_t &size,
        const std::string inputPrompt);

    // reset all positions in the array filled with IdToClear + 1
    static void clearArray(int *array, const size_t &size, const int IdToClear);
};