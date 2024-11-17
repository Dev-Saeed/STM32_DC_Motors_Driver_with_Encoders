/*
 * motor_driver.h
 *
 *  Created on: Nov 16, 2024
 *      Author: Saeed
 *
 *      to use this library to have to:
 *      set the timer Prescaler = 72-1;
 *      set the timer Period    = 1000-1;
 *      and enable the interrupt from the .ioc
 *
 */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_

#include "main.h"  // Include HAL and STM32 headers

// Define motor structure
typedef struct motor {
    TIM_HandleTypeDef *tim;          // Pointer to the timer instance
    uint32_t ch1;                   // PWM channel 1 (positive direction)
    uint32_t ch2;                   // PWM channel 2 (negative direction)
    void (*speed)(struct motor *, int16_t); // Function pointer for speed control
    int16_t current_speed;          // Tracks the current speed of the motor
} motor;

// Function prototypes
motor Motor_Init(TIM_HandleTypeDef *tim, uint32_t ch1, uint32_t ch2);
void Motor_SetSpeed(motor *m, int16_t speed);


#endif /* INC_MOTOR_DRIVER_H_ */
