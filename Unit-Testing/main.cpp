#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "doctest/doctest.h"
#include "TrafficSignal/TrafficSignal.h"
#include "Scheduler/Scheduler.h"
#include "DefectFixer/DefectFixer.h"

using namespace std;

TEST_SUITE("TrafficSignal"){
TEST_CASE("State Check") {
    TrafficSignal trafficSignal(0);
    CHECK(trafficSignal.getState() == "DISABLED");
    trafficSignal.setState(TrafficSignalState::GO);
    CHECK(trafficSignal.getState() == "GO");
    trafficSignal.setState(TrafficSignalState::WAIT);
    CHECK(trafficSignal.getState() == "WAIT");
    trafficSignal.setState(TrafficSignalState::STOP);
    CHECK(trafficSignal.getState() == "STOP");
    trafficSignal.setState(TrafficSignalState::SOS);
    CHECK(trafficSignal.getState() == "SOS");
}
}

TEST_SUITE("Scehduler"){
TEST_CASE("Time: 10") {

    TrafficSignal nsSignal(0);
    TrafficSignal ewSignal(1);

    Scheduler myScheduler(nsSignal, ewSignal);

    int time = 10;
    //cout << "Time: "+ to_string(time) +", NS: " + myScheduler.getNSScheduler(time) + ", EW: " +     myScheduler.getEWScheduler(time) << endl;
    CHECK(myScheduler.getNSScheduler(time) == "GO");
    CHECK(myScheduler.getEWScheduler(time) == "STOP");
}
TEST_CASE("Time: 30") {

    TrafficSignal nsSignal(0);
    TrafficSignal ewSignal(1);

    Scheduler myScheduler(nsSignal, ewSignal);

    int time = 30;
    //cout << "Time: "+ to_string(time) +", NS: " + myScheduler.getNSScheduler(time) + ", EW: " +     myScheduler.getEWScheduler(time) << endl;
    CHECK(myScheduler.getNSScheduler(time) == "STOP");
    CHECK(myScheduler.getEWScheduler(time) == "GO");
}
TEST_CASE("Time: 28") {

    TrafficSignal nsSignal(0);
    TrafficSignal ewSignal(1);

    Scheduler myScheduler(nsSignal, ewSignal);

    int time = 28;
    //cout << "Time: "+ to_string(time) +", NS: " + myScheduler.getNSScheduler(time) + ", EW: " +     myScheduler.getEWScheduler(time) << endl;
    CHECK(myScheduler.getNSScheduler(time) == "STOP");
    CHECK(myScheduler.getEWScheduler(time) == "STOP");
}
}


TEST_SUITE("Emergency"){
TEST_CASE("Emergency at NS"){
    TrafficSignal nsSignal(0);
    TrafficSignal ewSignal(1);

    Scheduler myScheduler(nsSignal, ewSignal);
    myScheduler.setNSScheduler(TrafficSignalState::SOS);
    int time = 10;
    //cout << "Time: "+ to_string(time) +", NS: " + myScheduler.getNSScheduler(time) + ", EW: " +     myScheduler.getEWScheduler(time) << endl;
    CHECK(myScheduler.getNSScheduler(time) == "SOS");
    CHECK(myScheduler.getEWScheduler(time) == "STOP");
}

TEST_CASE("Emergency at EW"){
    TrafficSignal nsSignal(0);
    TrafficSignal ewSignal(1);

    Scheduler myScheduler(nsSignal, ewSignal);
    myScheduler.setEWScheduler(TrafficSignalState::SOS);
    int time = 10;
    //cout << "Time: "+ to_string(time) +", NS: " + myScheduler.getNSScheduler(time) + ", EW: " +     myScheduler.getEWScheduler(time) << endl;
    CHECK(myScheduler.getNSScheduler(time) == "STOP");
    CHECK(myScheduler.getEWScheduler(time) == "SOS");
}
}

TEST_SUITE("DefectiveTests") {
    TEST_CASE("Invalid Traffic Signal ID") {
        CHECK_NOTHROW(TrafficSignal(-1));
    }

    TEST_CASE("Invalid Scheduler Initialization") {
        TrafficSignal invalidSignal(-1);
        CHECK_NOTHROW(Scheduler(invalidSignal, invalidSignal));
    }

    TEST_CASE("Invalid Time for Scheduler") {
        TrafficSignal nsSignal(0);
        TrafficSignal ewSignal(1);
        Scheduler myScheduler(nsSignal, ewSignal);

        int invalidTime = -5;
        CHECK_NOTHROW(myScheduler.getNSScheduler(invalidTime));
        CHECK_NOTHROW(myScheduler.getEWScheduler(invalidTime));
    }

    TEST_CASE("Invalid TrafficSignalState for Set State") {
        TrafficSignal nsSignal(0);
        TrafficSignal ewSignal(1);
        Scheduler myScheduler(nsSignal, ewSignal);

        CHECK_NOTHROW(myScheduler.setNSScheduler(TrafficSignalState::DISABLED));
        CHECK_NOTHROW(myScheduler.setEWScheduler(TrafficSignalState::DISABLED));
    }

    TEST_CASE("Invalid TrafficSignalState Transition") {
        TrafficSignal nsSignal(0);
        TrafficSignal ewSignal(1);
        Scheduler myScheduler(nsSignal, ewSignal);

        myScheduler.setNSScheduler(TrafficSignalState::GO);

        CHECK_NOTHROW(myScheduler.setNSScheduler(TrafficSignalState::WAIT));
    }

}

TEST_SUITE("DefectiveTests Fixer") {
    TEST_CASE("Fix Invalid Traffic Signal ID") {
        TrafficSignal trafficSignal(0);
        CHECK_THROWS(DefectFixer::fixInvalidTrafficSignalID(trafficSignal, -1));
        CHECK(trafficSignal.getID() == 0);  // ID should not be changed
    }

}
