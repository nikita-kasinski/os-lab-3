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

void Utility::outputArray(std::ostream &out, const int *array, const size_t &size)
{
    for (size_t i = 0; i < size; ++i)
    {
        out << array[i] << ' ';
    }
    out << "\n";
}

void Utility::outputMarkers(std::ostream &out, const int *finish, const size_t &markerCount)
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

size_t Utility::inputWorkingMarkerId(
    std::istream &in,
    std::ostream &out,
    const int *finish,
    const size_t &size,
    const std::string inputPrompt)
{
    bool correct = false;
    int id;
    while (!correct)
    {
        out << inputPrompt;
        in >> id;
        id--;
        if (id < 0)
        {
            continue;
        }
        if (finish[id] == 0)
        {
            correct = true;
        }
    }

    return static_cast<size_t>(id);
}

void Utility::clearArray(int *array, const size_t &size, const int idToClear)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (array[i] == idToClear + 1)
        {
            array[i] = Utility::valueToInitialize;
        }
    }
}