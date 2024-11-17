# STM32 DC Motor Driver

A lightweight and efficient DC motor driver implementation for STM32 microcontrollers, designed for precise and smooth control of DC motors using PWM. This project is specially designed to work with **IBT2 Motor Drivers** as well as **L298N**, **DRV8871**, or other similar H-Bridge motor driver circuits.

---

## Features

- **Multiple Motor Control**: Supports controlling multiple DC motors independently.
- **Smooth Speed Adjustment**: Implements gradual acceleration and deceleration for smooth motor operation.
- **Direction Control**: Forward and reverse direction functionality.
- **PWM-Based Speed Control**: Utilizes PWM (Pulse Width Modulation) signals for precise speed control.
- **Compatibility with Popular Motor Drivers**:
  - **IBT2 Motor Driver**.
  - **L298N**, **DRV8871**, and similar H-Bridge motor driver circuits.
- **Flexible Timer Configuration**: Works with configurable prescaler and period values for timers to achieve custom PWM frequencies.

---

## Wiring Diagram

Below is the wiring diagram for connecting the STM32 microcontroller, IBT2 motor driver, DC motor, and power source:

![Wiring Diagram](https://raw.githubusercontent.com/Dev-Saeed/STM32_DC_Motors_Driver_with_Encoders/main/Wiring.png)

### Wiring Details:
1. **STM32 Board**:
   - Connect **PWM1** (e.g., PA8, TIM1 Channel 1) to **RPWM** on the IBT2 driver.
   - Connect **PWM2** (e.g., PA9, TIM1 Channel 2) to **LPWM** on the IBT2 driver.
   - Ensure the STM32's ground (GND) is connected to the IBT2's ground.

2. **IBT2 Motor Driver**:
   - **RPWM**: Input for controlling the motor's forward direction.
   - **LPWM**: Input for controlling the motor's reverse direction.
   - Connect the motor's terminals to **OUT1** and **OUT2**.
   - Provide sufficient power to the IBT2 via the **+12V** and **GND** terminals.

3. **Power Source**:
   - A 12V LiPo battery is used as the power source for the motor and the IBT2 driver.
   - Ensure the battery's ground is shared with the STM32 and IBT2.

4. **DC Motor**:
   - The motor is connected to the IBT2's output terminals (**OUT1** and **OUT2**).

This wiring allows for bidirectional control of the DC motor using the STM32's PWM signals.

---

## Project Overview

This code is implemented using STM32 HAL libraries and is tailored for projects requiring smooth motor control. It is suitable for:
- Robotics projects.
- Industrial automation.
- Embedded systems requiring precise DC motor control.

---

## Usage

### Hardware Requirements
1. **STM32 Microcontroller**: Compatible with STM32F103 or other STM32 devices.
2. **Motor Driver Circuit**:
   - Recommended: **IBT2 Motor Driver**, **L298N**, **DRV8871**, or similar H-Bridge motor driver.
3. **DC Motors**: For testing and demonstration.
4. **Power Supply**: Ensure the motor driver and microcontroller have an adequate power source.

### Software Requirements
- STM32CubeIDE or compatible IDE.
- STM32 HAL drivers.

---

### How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/STM32-DC-Motor-Driver.git
   ```

2. Import the project into STM32CubeIDE.

3. Configure the hardware as shown in the wiring diagram above.

4. Set up the PWM timer:
   - **Goal**: Achieve a **PWM frequency of 1 kHz**.
   - **Formula for PWM frequency**:
      ```
      f_PWM = f_timer / ((Prescaler + 1) × (Counter Period + 1))
      ```
   - For an internal clock of **72 MHz**, use:
     - **Prescaler**: `72-1` → Divides the timer clock by 72, resulting in a 1 MHz timer frequency.
     - **Counter Period**: `1000-1` → Divides the 1 MHz timer frequency by 1000, resulting in a PWM frequency of 1 kHz.


5. Modify the motor driver functions as needed:
   - Use the `Motor_Init` function to initialize each motor.
   - Use `Motor_SetSpeed` to control speed and direction:
     ```c
     Motor_SetSpeed(&motor1, 500);  // Forward with speed = 500
     Motor_SetSpeed(&motor1, -500); // Reverse with speed = 500
     Motor_SetSpeed(&motor1, 0);    // Stop the motor
     ```

6. Build and flash the code to your STM32 device.

---

### Example Code

Here’s an example of initializing and controlling a motor:

```c
// Initialize Motor
motor motor1 = Motor_Init(&htim1, TIM_CHANNEL_1, TIM_CHANNEL_2);

// Start PWM
HAL_TIM_PWM_Start(motor1.tim, motor1.ch1);
HAL_TIM_PWM_Start(motor1.tim, motor1.ch2);

// Set Motor Speed
Motor_SetSpeed(&motor1, 500);  // Forward at 50% speed
HAL_Delay(2000);
Motor_SetSpeed(&motor1, -500); // Reverse at 50% speed
HAL_Delay(2000);
Motor_SetSpeed(&motor1, 0);    // Stop the motor
```

---

## Supported Motor Drivers

This code is compatible with the following motor driver circuits:
- **IBT2 Motor Driver** (ideal for high-current motors).
- **L298N H-Bridge Motor Driver** (commonly used in hobbyist projects).
- **DRV8871 Motor Driver** (compact and efficient for low-current motors).
- Other similar motor driver circuits.

---

## Contributing

Contributions are welcome! If you’d like to improve the code, add features, or report issues, feel free to open an issue or submit a pull request.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

## Acknowledgments

- Thanks to the STM32 HAL library for providing a robust API for embedded programming.
- Special thanks to the embedded systems community for their continuous support and inspiration.

---
