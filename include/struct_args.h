#pragma once
//author: Nikita Kasinski

struct MarkerArgs
{
    int id = -1;
    int n = 0;
    int* array = nullptr;
    int* finish = nullptr;
    CRITICAL_SECTION *iocs = nullptr;
    CRITICAL_SECTION *wcs = nullptr;
};