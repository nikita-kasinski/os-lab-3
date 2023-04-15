#include "utility.h"

int *Utility::initializeArray(size_t size)
{
    int *array = new int[size];
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = valueToInitialize;
    }

    return array;
}

bool Utility::readPositiveInteger(
    std::istream &in,
    std::ostream &out,
    size_t &destination,
    const std::string &inputPrompt,
    const std::string &inputFailedPrompt)
{
    int initialValue = 0;
    out << inputPrompt;
    in >> initialValue;
    if (initialValue <= 0)
    {
        out << inputFailedPrompt;
        return false;
    }

    destination = static_cast<size_t>(initialValue);
    return true;
}

void Utility::outputArray(std::ostream& out, const int* array, size_t size) 
{
    for (size_t i = 0; i < size; ++i)
    {
        out << array[i] << ' ';
    }
    out << "\n";
}

void Utility::outputMarkers(std::ostream &out, const int *finish, size_t markerCount)
{
    for (size_t i = 0; i < markerCount; ++i)
    {
        if (finish[i] == 0)
        {
            out << i + 1 << ' ';
        }
    }
    out << "\n";
}