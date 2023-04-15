#pragma once
// author: Nikita Kasinski

struct MarkerArgs
{
    size_t id = 0;
    size_t size = 0;
    int *array = nullptr;
    const int *finish = nullptr;
    CRITICAL_SECTION *iocs = nullptr;
    CRITICAL_SECTION *wcs = nullptr;
};