#include "Scheduler.h"
#include "../TrafficSignal/TrafficSignal.h"
#include <string.h>

using namespace std;

Scheduler::Scheduler(TrafficSignal ns, TrafficSignal ew): nStrafficSignal(ns), eWtrafficSignal(ew) {}

void Scheduler::setNSScheduler(TrafficSignalState input){
    if (input == TrafficSignalState::SOS){
        nStrafficSignal.setState(TrafficSignalState::SOS);
        eWtrafficSignal.setState(TrafficSignalState::STOP);
    }
}

void Scheduler::setEWScheduler(TrafficSignalState input){
    if (input == TrafficSignalState::SOS){
        nStrafficSignal.setState(TrafficSignalState::STOP);
        eWtrafficSignal.setState(TrafficSignalState::SOS);
    }
}

string Scheduler::getNSScheduler(int time){
    if(nStrafficSignal.getState()=="SOS"||eWtrafficSignal.getState()=="SOS"){
        return nStrafficSignal.getState();
    } else {
    if(time < 26){
        nStrafficSignal.setState(TrafficSignalState::GO);
        return "GO";
    } else if (time >= 26 && time < 28){
        nStrafficSignal.setState(TrafficSignalState::WAIT);
        return "WAIT";
    } else if (time >= 28 && time < 59){
        nStrafficSignal.setState(TrafficSignalState::STOP);
        return "STOP";
    } else if (time >= 59 && time < 60){
        nStrafficSignal.setState(TrafficSignalState::WAIT);
        return "WAIT";
    } else {
        return "DISABLED";
    }        
    }
}

string Scheduler::getEWScheduler(int time){
    if(nStrafficSignal.getState()=="SOS"||eWtrafficSignal.getState()=="SOS"){
        return eWtrafficSignal.getState();
    } else {
    if(time < 29){
        eWtrafficSignal.setState(TrafficSignalState::STOP);
        return "STOP";
    } else if (time >= 29 && time < 30){
        eWtrafficSignal.setState(TrafficSignalState::WAIT);
        return "WAIT";
    } else if (time >= 30 && time < 56){
        eWtrafficSignal.setState(TrafficSignalState::GO);
        return "GO";
    } else if (time >= 56 && time < 58){
        eWtrafficSignal.setState(TrafficSignalState::WAIT);
        return "WAIT";
    }  else if (time >= 58 && time < 60){
        eWtrafficSignal.setState(TrafficSignalState::STOP);
        return "STOP";
    } else {
        return "DISABLED";
    }
    }
}