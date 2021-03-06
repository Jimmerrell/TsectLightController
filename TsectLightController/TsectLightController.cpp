
#include <iostream>

#include "Utils.h"
#include "SimpleTimer.h"
#include "LightController.h"

using namespace Utils;

int main()
{
    std::map<int, std::string> COLOR_STRINGS;
    COLOR_STRINGS[COLOR::RED] = "RED";
    COLOR_STRINGS[COLOR::GREEN] = "GREEN";
    COLOR_STRINGS[COLOR::YELLOW] = "YELLOW";

    bool bRunning = true;
    float prevTime = 0.0;

    LightController controller;
    SimpleTimer timer;

    timer.Start();
    while (bRunning)
    {
        float currentTime = timer.GetTimeInSeconds();
        float deltaTime = currentTime - prevTime;
        if (deltaTime >= 1.0f)
        {
            prevTime = currentTime;
            controller.UpdateController();

            //print status
            std::string status = "STATUS: Time: ";
            status += timer.GetTimeInMinutesAndSeconds();
            print(status, COLOR::WHITE, 0);

            print(" || ", COLOR::WHITE, 0);

            int EW_colorID = controller.GetEastWestColor();
            status = "EW Color: " + COLOR_STRINGS[EW_colorID];
            print(status, controller.GetEastWestColor(), 0);

            print(" || ", COLOR::WHITE, 0);

            int NB_colorID = controller.GetNorthBoundColor();
            status = "NB Color: " + COLOR_STRINGS[NB_colorID];
            print(status, controller.GetNorthBoundColor());


            //set up approaches by cars on the northbound road every 50 seconds starting at 15 seconds
            if (timer.GetTimeInSeconds() > 15 && timer.GetTimeInSeconds() < 30)
                controller.NorthBoundCarSensed(true);
            else if (timer.GetTimeInSeconds() > 15 &&
                (int(timer.GetTimeInSeconds()) % 50 == 0 ||
                int(timer.GetTimeInSeconds()) % 50 <= 11))
            {
                controller.NorthBoundCarSensed(true);
            }
            else
                controller.NorthBoundCarSensed(false);
         }
    }
    timer.Stop();
}

