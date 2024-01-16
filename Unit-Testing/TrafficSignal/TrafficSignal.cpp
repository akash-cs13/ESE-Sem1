#include <iostream>
#include <string>
#include "TrafficSignal.h"

using namespace std;

TrafficSignal::TrafficSignal(int number) : id(number), state(TrafficSignalState::DISABLED) {}

string TrafficSignal::getState()
{
  switch (state)
  {
  case TrafficSignalState::GO:
    return "GO";
  case TrafficSignalState::SOS:
    return "SOS";
  case TrafficSignalState::STOP:
    return "STOP";
  case TrafficSignalState::WAIT:
    return "WAIT";
  default:
    return "DISABLED";
  }
}

void TrafficSignal::setState(TrafficSignalState input)
{
  state = input;
}

//Implemented to fix defets
int TrafficSignal::getID(){
  return id;
}