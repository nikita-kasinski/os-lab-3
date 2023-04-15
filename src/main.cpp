#include <iostream>
#include <string>
#include <string.h>
#include "marker.h"
#include "struct_args.h"
#include "utility.h"

int main()
{
    size_t size, markerCount;

    // reading size
    if (!Utility::readPositiveInteger(
            std::cin,
            std::cout,
            size,
            "Enter array size\n",
            "Array size must be positive integer. Abort\n"))
    {
        return 1;
    }

    // reading markerCount
    if (!Utility::readPositiveInteger(
            std::cin,
            std::cout,
            markerCount,
            "Enter the quantity of markers\n",
            "Marker count must be positive integer. Abort\n"))
    {
        return 2;
    }

    // initializing array
    int *array = Utility::initializeArray(size);

    // initialize events
    HANDLE *events = new HANDLE[markerCount];
    HANDLE *workEvents = new HANDLE[markerCount];
    for (size_t i = 0; i < markerCount; ++i)
    {
        std::string eventName = "Marker event " + std::to_string(i + 1);
        std::string workEventName = "Work event " + std::to_string(i + 1);
        events[i] = CreateEventA(NULL, TRUE, FALSE, eventName.c_str());
        workEvents[i] = CreateEventA(NULL, TRUE, FALSE, workEventName.c_str());
    }

    // initialize critical section
    CRITICAL_SECTION *iocs = new CRITICAL_SECTION;
    CRITICAL_SECTION *wcs = new CRITICAL_SECTION;
    InitializeCriticalSection(iocs);
    InitializeCriticalSection(wcs);

    // initialize markers
    HANDLE *markers = new HANDLE[markerCount];
    MarkerArgs *args = new MarkerArgs[markerCount];
    unsigned long int *markerThreadIds = new unsigned long int[markerCount];
    int *finish = new int[markerCount];

    for (size_t i = 0; i < markerCount; ++i)
    {
        finish[i] = 0;
        args[i].id = i;
        args[i].size = size;
        args[i].array = array;
        args[i].finish = finish;
        args[i].iocs = iocs;
        args[i].wcs = wcs;
        markers[i] = CreateThread(NULL, 0, marker, (void *)(&args[i]), 0, &markerThreadIds[i]);
    }

    // main cycle
    for (size_t i = 0; i < markerCount; ++i)
    {
        WaitForMultipleObjects(markerCount, events, TRUE, INFINITE);

        std::cout << "Array:\n";
        Utility::outputArray(std::cout, array, size);

        std::cout << "\nIds of working markers: ";
        Utility::outputMarkers(std::cout, finish, markerCount);
        
        size_t id = Utility::inputWorkingMarkerId(std::cin, std::cout, finish, size, "Enter working marker id: ");
        
        std::cout << "Finishing marker " << id + 1 << "\n";
        finish[id] = 1;

        // set finished marjker event to make him clear the array
        SetEvent(workEvents[id]);
        WaitForSingleObject(markers[id], INFINITE);

        // showing cleared array
        std::cout << "Array:\n";
        Utility::outputArray(std::cout, array, size);
        std::cout << "\n";

        // reseting events for other markers to work
        for (size_t i = 0; i < markerCount; ++i)
        {
            if (finish[i] == 0) // if marker is not finished
            {
                ResetEvent(events[i]);
                SetEvent(workEvents[i]);
            }
        }
    }

    // freeing dynamic memory
    for (size_t i = 0; i < markerCount; ++i)
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