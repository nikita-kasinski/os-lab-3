//author: Nikita Kasinski
#include "windows.h"
#include <iostream>
#include "struct_args.h"

DWORD WINAPI marker(LPVOID _args)
{
    MarkerArgs args = *(MarkerArgs*)_args;
    int id = args.id;
    int* array = args.array;
    int n = args.n;
    std::cout << "Create marker with id " << id << "\n";
}