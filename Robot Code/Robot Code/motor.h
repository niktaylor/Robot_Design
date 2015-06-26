/*
motor.h
Contains data structures and function prototypes relating to the motor driver.
*/

#ifndef MOTOR_H
#define MOTOR_H

enum DIRECTION {FORWARD, REVERSE, LEFT, RIGHT};

void init_motor();
void move();
void stop_motor();

#endif