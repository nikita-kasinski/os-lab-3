#include <iostream>
#include <string>
#include "marker.h"
#include "string.h"

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
        std::string eventName = "Marker event" + std::to_string(i);
        std::wstring wEventName = std::wstring(eventName.begin(), eventName.end());
        events[i] = CreateEvent(NULL, TRUE, TRUE, wEventName.c_str());
    }
    //HANDLE marker_handle = CreateThread(NULL, 0, marker, (void*) &first_id, 0, &marker_id);
    delete[] array;
    for (size_t i = 0; i < marker_count; ++i)
    {
        CloseHandle(events[i]);
    }
    delete[] events;
    return 0;
}