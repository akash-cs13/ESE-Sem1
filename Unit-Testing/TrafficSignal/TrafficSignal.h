#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

enum class TrafficSignalState
{
    GO,
    WAIT,
    STOP,
    SOS,
    DISABLED
};

class TrafficSignal
{
private:
    int id;
    TrafficSignalState state;

public:
    TrafficSignal(int id);
    string getState();
    void setState(TrafficSignalState input);
    int getID();
};
