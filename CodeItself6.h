#pragma once
// For getting access to the functions for sensors and engines
#include "QTRSensors.h"      //For the sensors
#include "MotorController.h" //For the engines



class GeneralFunctions {

  public:
    // Initializates the motors, it will run a battery of tests to see if the wheels are
    // doing what they're supposed to. Goes forward, backward, stops, goes left, goes right
    void testEngines();
    // Initializates the sensors
    void setSensors ();
    // Prints on monitor the returned values of the sensors
    void getSensorValues();
    // Prints the position based on QTR library
    void getPosition();
    // Controls speed of both left and right wheels at the same time
    void wheelsController(int leftPower, int rightPower);
    //Code used to run on the circuit
    void followTheWhiteLine();
};
