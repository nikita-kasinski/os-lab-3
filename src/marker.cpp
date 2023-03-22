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
    int* finish = args.finish;
    CRITICAL_SECTION iocs = *args.iocs;
    CRITICAL_SECTION wcs = *args.wcs;
    std::string eventName = "Marker event " + std::to_string(id);
    HANDLE event = CreateEvent(NULL, TRUE, TRUE, eventName.c_str());
    std::cout << "Create marker with id " << id << "\n";
    //SetEvent(event);
}