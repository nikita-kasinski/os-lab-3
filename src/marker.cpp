//author: Nikita Kasinski
#include "windows.h"
#include <iostream>
#include "struct_args.h"
#include <random>

DWORD WINAPI marker(LPVOID _args)
{
    MarkerArgs args = *(MarkerArgs*)_args;
    int id = args.id;
    int* array = args.array;
    int n = args.n;
    int* finish = args.finish;
    CRITICAL_SECTION *iocs = args.iocs;
    CRITICAL_SECTION *wcs = args.wcs;
    EnterCriticalSection(iocs);
    std::cout << "Create marker with id " << id + 1 << "\n";
    LeaveCriticalSection(iocs);
    std::string eventName = "Marker event " + std::to_string(id + 1);
    std::string workEventName = "Work event " + std::to_string(id + 1);
    HANDLE event = CreateEvent(NULL, TRUE, FALSE, eventName.c_str());
    HANDLE workEvent = CreateEvent(NULL, TRUE, FALSE, workEventName.c_str());
    std::mt19937 mrand(id);
    while(true)
    {
        int pos = mrand() % n;
        EnterCriticalSection(wcs);
        if (array[pos] == 0)
        {
            Sleep(5);
            array[pos] = id + 1;
            Sleep(5);
            LeaveCriticalSection(wcs);
        }
        else
        {
            LeaveCriticalSection(wcs);
            EnterCriticalSection(iocs);
            std::cout << "Marker " << id + 1 << " is waiting\n";
            LeaveCriticalSection(iocs);
            SetEvent(event);
            ResetEvent(workEvent);
            WaitForSingleObject(workEvent, INFINITE);
            if (finish[id] == 1) 
            {
                EnterCriticalSection(wcs);
                for (size_t i = 0; i < n; ++i)
                {
                    if (array[i] == id + 1)
                    {
                        array[i] = 0;
                    }
                }
                LeaveCriticalSection(wcs);
                break;
            }
        }
    }
    return 0;
}