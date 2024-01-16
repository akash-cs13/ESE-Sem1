#pragma once

#include "../TrafficSignal/TrafficSignal.h"

class Scheduler {
private:
    TrafficSignal nStrafficSignal;
    TrafficSignal eWtrafficSignal;
public:
    Scheduler(TrafficSignal ns, TrafficSignal ew);
    string getNSScheduler(int time);
    string getEWScheduler(int time);
    void setNSScheduler(TrafficSignalState input);
    void setEWScheduler(TrafficSignalState input);

};