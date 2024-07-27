#include "GpioController.h"

GpioController::GpioController()
{
    gpio.init();
}

GpioController::~GpioController(){}

void GpioController::chModeOutput(int pinNo)
{
    gpio.chModeOutput(pinNo);
}

void GpioController::chModeInput(int pinNo)
{
    gpio.chModeInput(pinNo);
}

void GpioController::setHigh(int pinNo)
{
    gpio.setHigh(pinNo);
}

void GpioController::setLow(int pinNo)
{
    gpio.setLow(pinNo);
}
