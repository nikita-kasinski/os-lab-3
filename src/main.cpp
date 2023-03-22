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
    HANDLE *workEvents = new HANDLE[marker_count];
    for (size_t i = 0; i < marker_count; ++i)
    {
        std::string eventName = "Marker event " + std::to_string(i + 1);
        std::string workEventName = "Work event " + std::to_string(i + 1);
        events[i] = CreateEvent(NULL, TRUE, FALSE, eventName.c_str());
        workEvents[i] = CreateEvent(NULL, TRUE, FALSE, workEventName.c_str());
    }
    HANDLE *markers = new HANDLE[marker_count];
    MarkerArgs *args = new MarkerArgs[marker_count];
    unsigned long int *markerThreadIds = new unsigned long int[marker_count];
    int *finish = new int[marker_count];
    CRITICAL_SECTION *iocs = new CRITICAL_SECTION;
    CRITICAL_SECTION *wcs = new CRITICAL_SECTION;
    InitializeCriticalSection(iocs);
    InitializeCriticalSection(wcs);
    for (size_t i = 0; i < marker_count; ++i)
    {
        finish[i] = 0;
        args[i].id = i;
        args[i].n = n;
        args[i].array = array;
        args[i].finish = finish;
        args[i].iocs = iocs;
        args[i].wcs = wcs;
        markers[i] = CreateThread(NULL, 0, marker, (void *)(&args[i]), 0, &markerThreadIds[i]);
    }
    for (size_t i = 0; i < marker_count; ++i)
    {
        WaitForMultipleObjects(marker_count, events, TRUE, INFINITE);
        std::cout << "Array:\n";
        for (size_t i = 0; i < n; ++i)
        {
            std::cout << array[i] << ' ';
        }
        std::cout << "\nIds of working markers: ";
        for (size_t i = 0; i < marker_count; ++i)
        {
            if (finish[i] == 0)
            {
                std::cout << i + 1 << ' ';
            }
        }
        std::cout << "\n";
        bool correct = false;
        int id = -1;
        while (!correct)
        {
            std::cout << "Enter working marker id :\n";
            std::cin >> id;
            id--;
            if (id < 0)
            {
                continue;
            }
            if (finish[id] == 0)
            {
                correct = true;
            }
        }
        std::cout << "Finish marker " << id + 1 << "\n";
        finish[id] = 1;
        SetEvent(workEvents[id]);
        WaitForSingleObject(markers[id], INFINITE);
        std::cout << "Array:\n";
        for (size_t i = 0; i < n; ++i)
        {
            std::cout << array[i] << ' ';
        }
        std::cout << "\n\n";
        for (size_t i = 0; i < marker_count; ++i)
        {
            if (finish[i] == 0)
            {
                ResetEvent(events[i]);
                SetEvent(workEvents[i]);
            }
        }
    }
    for (size_t i = 0; i < marker_count; ++i)
    {
        CloseHandle(events[i]);
        CloseHandle(markers[i]);
    }
    DeleteCriticalSection(iocs);
    DeleteCriticalSection(wcs);
    delete iocs;
    delete wcs;
    delete[] array;
    delete[] events;
    delete[] args;
    delete[] finish;
    return 0;
}