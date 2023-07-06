/********************************************************************************/
#ifndef MYTIMER_H_INCLUDED
#define MYTIMER_H_INCLUDED
#include <windows.h>
class myTimer{
    LARGE_INTEGER F; //Frequency
    LARGE_INTEGER sT; // Start Time
    LARGE_INTEGER eT; // End Time
    double interval; // End Time - Start Time in seconds
public:
myTimer() { QueryPerformanceFrequency(&F); }
    void StartTimer(){ QueryPerformanceCounter(&sT); }
    void EndTimer(){ QueryPerformanceCounter(&eT); }
    double GetInterval() {
        return (double) (eT.QuadPart - sT.QuadPart) / F.QuadPart;
    }
};
#endif // MYTIMER_H_INCLUDED
/********************************************************************************/
