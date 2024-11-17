/*
 * motor_driver.c
 *
 *  Created on: Nov 16, 2024
 *      Author: saeed
 */
#include "motor_driver.h"

// Function to set motor speed
void Motor_SetSpeed(motor *m, int16_t target_speed) {
    const uint16_t step = 10;  // Increment or decrement step size
    const uint16_t delay = 10; // Delay in milliseconds between steps

    // Smoothly adjust speed to target_speed
    while (m->current_speed != target_speed) {
        if (m->current_speed < target_speed) {
            m->current_speed += step;
            if (m->current_speed > target_speed) {
                m->current_speed = target_speed;  // Prevent overshooting
            }
        } else if (m->current_speed > target_speed) {
            m->current_speed -= step;
            if (m->current_speed < target_speed) {
                m->current_speed = target_speed;  // Prevent undershooting
            }
        }

        // Update PWM duty cycle for forward or reverse direction
        if (m->current_speed > 0) {
            // Forward direction
            __HAL_TIM_SET_COMPARE(m->tim, m->ch1, m->current_speed);
            __HAL_TIM_SET_COMPARE(m->tim, m->ch2, 0);
        } else if (m->current_speed < 0) {
            // Reverse direction
            __HAL_TIM_SET_COMPARE(m->tim, m->ch1, 0);
            __HAL_TIM_SET_COMPARE(m->tim, m->ch2, -m->current_speed);  // Convert to positive
        } else {
            // Stop motor
            __HAL_TIM_SET_COMPARE(m->tim, m->ch1, 0);
            __HAL_TIM_SET_COMPARE(m->tim, m->ch2, 0);
        }

        // Start PWM channels
        HAL_TIM_PWM_Start(m->tim, m->ch1);
        HAL_TIM_PWM_Start(m->tim, m->ch2);

        HAL_Delay(delay);  // Add a small delay for smooth transition
    }
}

// Function to initialize a motor instance
motor Motor_Init(TIM_HandleTypeDef *tim, uint32_t ch1, uint32_t ch2) {
    motor m;
    m.tim = tim;
    m.ch1 = ch1;
    m.ch2 = ch2;
    m.current_speed = 0;            // Initialize speed to 0
    m.speed = Motor_SetSpeed;       // Assign the speed function
    return m;
}

