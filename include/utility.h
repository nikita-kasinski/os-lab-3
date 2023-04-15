#pragma once
#include <cstdlib>
#include <string>
#include <fstream>

class Utility
{
private:
    static constexpr int valueToInitialize = 0; 
public:
    // initializes array with valueToInitialize
    static int* initializeArray(size_t size);

    // reads integer from in, puts it into destination. If something went wrong returns false
    static bool readPositiveInteger(
        std::istream& in, 
        std::ostream& out,
        size_t& destination, 
        const std::string& inputPrompt, 
        const std::string& inputFailedPrompt);

};