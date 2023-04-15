#pragma once
//author: Nikita Kasinski

struct MarkerArgs
{
    int id = -1;
    size_t size = 0;
    int* array = nullptr;
    const int* finish = nullptr;
    CRITICAL_SECTION *iocs = nullptr;
    CRITICAL_SECTION *wcs = nullptr;
};