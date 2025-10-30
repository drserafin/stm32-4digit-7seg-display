# STM32 4-Digit 7-Segment Display Lab

## Physical Wiring
<img width="852" height="679" alt="image" src="https://github.com/user-attachments/assets/5db6763b-331f-4dda-9dc8-9d69dd039797" />


This repository contains the lab project for configuring a **4-digit 7-segment display** using an **STM32F0 Discovery board**.
[![Watch the demo video](https://img.youtube.com/vi/SvJLYGhE8S0/0.jpg)](https://youtu.be/SvJLYGhE8S0)


## Project Description

The goal of this lab is to:

- Interface a 4-digit 7-segment display with the STM32F0 microcontroller.
- Use a **74HC595 shift register** to drive the display.
- Implement time-multiplexing to show numbers on all four digits.
- Optionally handle button input to increment/decrement values.

## Hardware Connections

### STM32 → Shift Register (74HC595)
| STM32 Pin | Shift Register Pin | Label | Notes |
|-----------|-----------------|-------|-------|
| PA7       | SER             | Serial Data Input | MOSI |
| PA6       | RCLK            | Latch Clock      |      |
| PA5       | SRCLK           | Shift Register Clock | SCK |

### Shift Register → 4-Digit 7-Segment (5641AS)
| 74HC595 Pin | Label | 7-Segment Segment |
|-------------|-------|-----------------|
| Q0 (15)     | QA    | A               |
| Q1 (1)      | QB    | B               |
| Q2 (2)      | QC    | C               |
| Q3 (3)      | QD    | D               |
| Q4 (4)      | QE    | E               |
| Q5 (5)      | QF    | F               |
| Q6 (6)      | QG    | G               |

### STM32 → 4-Digit 7-Segment Digits
| Digit | STM32 Pin |
|-------|-----------|
| 1     | PC0       |
| 2     | PC1       |
| 3     | PC2       |
| 4     | PC3       |

### STM32 → Buttons
- Configure GPIO pins for increment and decrement buttons.

## Files Included

- `Core/Inc` — Header files
- `Core/Src` — Source files
- `lab2_october.ioc` — CubeMX configuration file

## Usage

1. Open the project in STM32CubeIDE.
2. Build and flash the project to the STM32F0 Discovery board.
3. Observe the 4-digit 7-segment display counting or responding to button input.

## Notes

- `.gitignore` excludes build files, temporary files, and IDE configurations.
- Only source files (`Core/`) and CubeMX config (`.ioc`) are tracked.

---

