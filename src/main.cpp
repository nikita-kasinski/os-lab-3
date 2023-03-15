#include <iostream>
#include "marker.h"

int main()
{
    std::cout << "Hello world\n";
    int first_id = 1;
    DWORD marker_id;
    HANDLE marker_handle = CreateThread(NULL, 0, marker, (void*) &first_id, 0, &marker_id);
    WaitForSingleObject(marker_handle, INFINITE);
    return 0;
}