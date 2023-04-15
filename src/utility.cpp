#include "utility.h"

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
        out << "Marker count must be positive integer. Abort\n";
        return false;
    }

    destination = static_cast<size_t>(initialValue);
    return true;
}