#pragma once
#include <Windows.h>

class TimeManager {
public:
    TimeManager() {}
    ~TimeManager() {}

    void Init() {
        QueryPerformanceCounter(&beforeInterval);
        QueryPerformanceCounter(&currentInterval);
        QueryPerformanceFrequency(&Frequency);
    }

    void Update() {
        QueryPerformanceCounter(&currentInterval);
        LONGLONG interval = (currentInterval.QuadPart - beforeInterval.QuadPart);

        float dTime = (float)interval / (float)Frequency.QuadPart;

        beforeInterval = currentInterval;
        deltaTime = dTime;
    }

    float GetDeltaTime() { return deltaTime; }

private:
    float deltaTime;
    LARGE_INTEGER beforeInterval, currentInterval, Frequency;
};