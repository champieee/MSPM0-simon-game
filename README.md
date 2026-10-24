# MSPM0 Simon Game

A Simon-style memory game written in C for the MSPM0 microcontroller.

## What it does

- Generates a random sequence of up to 10 colors.
- Shows one more color each round, replaying the earlier colors.
- Lets the player enter the sequence with six bumpers.
- Gives the player up to 3 seconds for each bumper response.
- Speeds up the sequence by 10% after each successful round.
- Shows win or loss with the bi-color LED and lets the player restart.

## Hardware and pin connections

| Component | MSPM0 pin |
|---|---|
| Bumper 1 | PA7 |
| Bumper 2 | PA14 |
| Bumper 3 | PB5 |
| Bumper 4 | PB21 |
| Bumper 5 | PB23 |
| Bumper 6 | PB25 |
| Start button | PB2 |
| RGB LED red | PB26 |
| RGB LED green | PB27 |
| RGB LED blue | PB22 |
| Status bi-color LED red/green | PA12 / PA13 |

The bumper inputs use internal pull-up resistors, so each bumper should pull its input to ground when pressed. PB2 is active high and uses an external pull-down resistor. Wire LEDs with the resistors and polarity specified by the circuit schematic.

## Build and run

Build with an MSPM0 toolchain and a project that provides the `engr2350_mspm0.h` library. Add the game source to the project (for example, as `main.c`), build it, and flash it to the board. The provided header and library are required; this source file is not a standalone MSPM0 project.

## Files

- `main.c` — game logic, GPIO setup, RGB LED control, and timer interrupt.
