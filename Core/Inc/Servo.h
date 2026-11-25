#ifndef __SERVO_H
#define __SERVO_H

#include "main.h"

#define SERVO_ANGLE_MIN     0.0f
#define SERVO_ANGLE_MAX     180.0f
#define SERVO_PULSE_MIN_US  550.0f
#define SERVO_PULSE_MAX_US  2450.0f

uint16_t Servo_AngleToCCR(float angle);
void Servo_SetAngle(float angle);
void Servo_Start(void);

#endif
