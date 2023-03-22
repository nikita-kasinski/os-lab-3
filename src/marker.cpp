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
    std::cout << "Create marker with id " << id << "\n";
    LeaveCriticalSection(iocs);
    std::string eventName = "Marker event " + std::to_string(id);
    HANDLE event = CreateEvent(NULL, TRUE, TRUE, eventName.c_str());

    std::mt19937 rand(id);
    while(true)
    {
        int pos = rand() % n;
        EnterCriticalSection(wcs);
        if (array[pos] == 0)
        {
            Sleep(5);
            array[pos] = id;
            Sleep(5);
            LeaveCriticalSection(wcs);
        }
        else
        {
            LeaveCriticalSection(wcs);
            SetEvent(event);
            WaitForSingleObject(event, INFINITE);
            if (finish[id] == 1)
            {
                EnterCriticalSection(wcs);
                for (size_t i = 0; i < n; ++i)
                {
                    if (array[i] == id)
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