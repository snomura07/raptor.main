#include "GpioController.h"

GpioController::GpioController()
{
    this->gpio.init();
}

GpioController::~GpioController(){}

void GpioController::chModeOutput(int pinNo)
{
    this->gpio.chModeOutput(pinNo);
}

void GpioController::chModeInput(int pinNo)
{
    this->gpio.chModeInput(pinNo);
}

void GpioController::setHigh(int pinNo)
{
    this->gpio.setHigh(pinNo);
}

void GpioController::setLow(int pinNo)
{
    this->gpio.setLow(pinNo);
}
