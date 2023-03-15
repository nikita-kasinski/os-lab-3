#include <iostream>
#include "marker.h"

int main()
{
    int n;
    std::cout << "Enter array size:\n";
    std::cin >> n;
    int *array = new int[n];
    //HANDLE marker_handle = CreateThread(NULL, 0, marker, (void*) &first_id, 0, &marker_id);
    delete[] array;
    return 0;
}