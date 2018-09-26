#pragma once

#include "Utils.h"

class LightController
{
public:
    LightController();
    ~LightController();

    void UpdateController();

    void NorthBoundCarSensed(bool bCar);

    Utils::COLOR GetEastWestColor() const { return eastWestColor; }
    Utils::COLOR GetNorthBoundColor() const { return northBoundColor; }

private:
    enum state
    {
        NB_GREEN, NB_YELLOW,
        EW_GREEN, EW_YELLOW,
        TRANSITION_TO_NB_GREEN, 
        TRANSITION_TO_EW_GREEN
    };

    state currentState = TRANSITION_TO_EW_GREEN;
    void switchState(state stateID);

    Utils::COLOR eastWestColor = Utils::COLOR::RED;
    Utils::COLOR northBoundColor = Utils::COLOR::RED;

    int northBoundSensor = 0;
    int inactiveSeconds = 0;
    int secondsInCurrentState = 0;
    bool bCarWaiting = false;
    int carWaitTime = 0;

    void northBoundGreen();
    void northBoundYellow();
    void eastWestGreen();
    void eastWestYellow();
    void transitionToNorthGreen();
    void transitionToEastWestGreen();

    void printCarWaitingUpdate();

};

