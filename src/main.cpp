#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "AirConditionerControllerRaspPico.hpp"

int main()
{
  AirConditionerController *controller = new AirConditionerControllerRaspPico();
  controller->Loop();
}
