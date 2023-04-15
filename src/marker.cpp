//author: Nikita Kasinski
#include <windows.h>
#include <iostream>
#include <random>
#include "struct_args.h"
#include "utility.h"

DWORD WINAPI marker(LPVOID _args)
{
    MarkerArgs args = *(MarkerArgs*)_args;

    size_t id = args.id; // marker id

    int* array = args.array; // array to mark
    size_t size = args.size; // its size

    const int* finish = args.finish; // array which enables marker disabling
    size_t cnt = 0; // counter for marked positions

    CRITICAL_SECTION *iocs = args.iocs; // critical section to access std::cin std::cout
    CRITICAL_SECTION *wcs = args.wcs; // critical section to mark array

    EnterCriticalSection(iocs);
    std::cout << "Create marker with id " << id + 1 << "\n";
    LeaveCriticalSection(iocs);

    // getting event to notify main
    std::string eventName = "Marker event " + std::to_string(id + 1);
    HANDLE event = CreateEventA(NULL, TRUE, FALSE, eventName.c_str());

    // getting event to resume work
    std::string workEventName = "Work event " + std::to_string(id + 1);
    HANDLE workEvent = CreateEventA(NULL, TRUE, FALSE, workEventName.c_str());

    // random number engine
    std::mt19937 mrand(id);

    while(true)
    {
        size_t pos = mrand() % size; // receiving new pos to mark
        EnterCriticalSection(wcs);
        if (array[pos] == Utility::valueToInitialize)
        {
            Sleep(5);
            array[pos] = id + 1; // marking the pos
            ++cnt;
            Sleep(5);

            LeaveCriticalSection(wcs);
        }
        else
        {
            LeaveCriticalSection(wcs);

            EnterCriticalSection(iocs);
            std::cout << "Marker " << id + 1 << " is waiting\n";
            std::cout << "Marked indeces: " << cnt << "\n";
            std::cout << "Filled index: " << pos << "\n\n";
            LeaveCriticalSection(iocs);

            SetEvent(event);
            ResetEvent(workEvent);

            WaitForSingleObject(workEvent, INFINITE);

            if (finish[id] == 1) 
            {
                cnt = 0;
                EnterCriticalSection(wcs);
                Utility::clearArray(array, size, id); // reset all positions filled with id + 1
                LeaveCriticalSection(wcs);
                break;
            }
        }
    }
    return 0;
}