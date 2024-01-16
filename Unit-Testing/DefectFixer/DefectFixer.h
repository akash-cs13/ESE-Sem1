#pragma once 

#include "../TrafficSignal/TrafficSignal.h"
#include "../Scheduler/Scheduler.h"

class DefectFixer {
public:
    static void fixInvalidTrafficSignalID(TrafficSignal& trafficSignal, int newID) {
        if(newID > 0){
        trafficSignal = TrafficSignal(newID);
        } else {
            throw std::invalid_argument("Invalid newID value");
        }
    }
};
