
#include "LightController.h"


LightController::LightController()
{
}

LightController::~LightController()
{
}

void LightController::UpdateController()
{
    
    switch (currentState)
    {
    case NB_GREEN:
        northBoundGreen();
        break;
    case NB_YELLOW:
        northBoundYellow();
        break;
    case EW_GREEN:
        eastWestGreen();
        break;
    case EW_YELLOW:
        eastWestYellow();
        break;
    case TRANSITION_TO_NB_GREEN:
        transitionToNorthGreen();
        break;
    case TRANSITION_TO_EW_GREEN:
        transitionToEastWestGreen();
        break;
    default:
        break;
    }
   
}

void LightController::NorthBoundCarSensed(bool bCar)
{
    if (bCar)
        northBoundSensor++;
    else if (!bCarWaiting)
        northBoundSensor = 0;

    if (northBoundSensor >= 10)
        bCarWaiting = true;
}

void LightController::switchState(state stateID)
{
    currentState = stateID;
    secondsInCurrentState = 0;
}

void LightController::northBoundGreen()
{
    // turn to yellow after 5 seconds of inactive sensor or after 40 seconds of NB_GREEN
    northBoundColor = Utils::COLOR::GREEN;
    bCarWaiting = false;
    carWaitTime = 0;

    if (northBoundSensor == 0)
        inactiveSeconds++;
    else
        inactiveSeconds = 0;

    if (inactiveSeconds >= 5)
    {
        switchState(NB_YELLOW);
        return;
    }

    secondsInCurrentState++;

    if(secondsInCurrentState >= 40)
    {
        switchState(NB_YELLOW);
    }
}

void LightController::northBoundYellow()
{
    // for 3 seconds
    northBoundColor = Utils::COLOR::YELLOW;
    secondsInCurrentState++;

    if (secondsInCurrentState >= 3)
    {
        switchState(TRANSITION_TO_EW_GREEN);
    }
}

void LightController::eastWestGreen()
{
    //minimum of 30 seconds
    eastWestColor = Utils::COLOR::GREEN;
    secondsInCurrentState++;

    if (northBoundSensor > 0)
    {
        printCarWaitingUpdate();
    }

    if (secondsInCurrentState >= 30)
    {
        if (bCarWaiting)
        {
            switchState(EW_YELLOW);
            northBoundSensor = 0;
        }
    }
}

void LightController::eastWestYellow()
{
    // for 3 seconds
    eastWestColor = Utils::COLOR::YELLOW;
    secondsInCurrentState++;
    printCarWaitingUpdate();

    if (secondsInCurrentState >= 3)
    {
        switchState(TRANSITION_TO_NB_GREEN);
    }
}

void LightController::transitionToNorthGreen()
{
    // for 2 seconds
    eastWestColor = Utils::COLOR::RED;
    secondsInCurrentState++;
    printCarWaitingUpdate();

    if (secondsInCurrentState >= 2)
    {
        switchState(NB_GREEN);
    }
}

void LightController::transitionToEastWestGreen()
{
    // for 2 seconds
    northBoundColor = Utils::COLOR::RED;
    secondsInCurrentState++;

    if (secondsInCurrentState >= 2)
    {
        switchState(EW_GREEN);
    }
}

void LightController::printCarWaitingUpdate()
{
    carWaitTime++;
    std::string sCarWaiting = "Car waiting in Northbound for ";
    sCarWaiting += std::to_string(carWaitTime);
    sCarWaiting += " seconds.";
    Utils::print(sCarWaiting);
}
