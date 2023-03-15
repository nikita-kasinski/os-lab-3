//author: Nikita Kasinski
#include "windows.h"
#include <iostream>

DWORD WINAPI marker(LPVOID args)
{
    int id = *(int*)args;
    std::cout << "Create marker with id " << id << "\n";
}