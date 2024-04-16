#include "ina238.hpp"
#include "irManager.hpp"
#include "servoController.hpp"
#include <wiringPi.h>

#define DEVICE_ADDRESS 0x40
#define BUS_NUMBER 1
#define SHUNT_RESISTANCE 0.022
#define MAX_CURRENT 0.05

#define IR_PIN 0        // wiringPi pin number
#define SERVO_PIN 23    // wiringPi pin number

void setupModules();

