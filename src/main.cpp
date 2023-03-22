#include <iostream>
#include <string>
#include <string.h>
#include "marker.h"
#include "struct_args.h"

int main()
{
    int n;
    std::cout << "Enter array size:\n";
    std::cin >> n;
    int *array = new int[n];
    for (size_t i = 0; i < n; ++i)
    {
        array[i] = 0;
    }
    int marker_count = 0;
    std::cout << "Enter the quantity of markers\n";
    std::cin >> marker_count;
    HANDLE *events = new HANDLE[marker_count];
    for (size_t i = 0; i < marker_count; ++i)
    {
        std::string eventName = "Marker event " + std::to_string(i);
        std::wstring wEventName = std::wstring(eventName.begin(), eventName.end());
        events[i] = CreateEvent(NULL, TRUE, TRUE, eventName.c_str());
    }
    HANDLE *markers = new HANDLE[marker_count];
    MarkerArgs *args = new MarkerArgs[marker_count];
    unsigned long int *markerThreadIds = new unsigned long int[marker_count];
    int *finish = new int[marker_count];
    CRITICAL_SECTION iocs, wcs;
    InitializeCriticalSection(&iocs);
    InitializeCriticalSection(&wcs);
    for (size_t i = 0; i < marker_count; ++i)
    {
        finish[i] = 0;
        args[i].id = i;
        args[i].n = n;
        args[i].array = array;
        args[i].finish = finish;
        args[i].iocs = &iocs;
        args[i].wcs = &wcs;
        markers[i] = CreateThread(NULL, 0, marker, (void*)(&args[i]), 0, &markerThreadIds[i]);
    }
    WaitForMultipleObjects(marker_count, markers, TRUE, INFINITE);
    delete[] array;
    for (size_t i = 0; i < marker_count; ++i)
    {
        CloseHandle(events[i]);
        CloseHandle(markers[i]);
    }
    delete[] events;
    delete[] args;
    delete[] finish;
    return 0;
}