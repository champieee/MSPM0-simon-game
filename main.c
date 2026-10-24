#include "engr2350_mspm0.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void GPIOInit(void);
void setRGB(int8_t color);
void timerInit(void);

Timers_TimerConfig timerConfig;
volatile uint32_t milliseconds = 0;

int main(void) {
	uint8_t pattern[10];
	int8_t answer[10];
	int8_t pressed;
	uint8_t i, j;
	uint8_t length;
	uint8_t correct;
	uint32_t start;
	uint32_t responseStart;
	uint32_t blinkStart;
	uint32_t displayTime;

	sysInit();
	GPIOInit();
	timerInit();

	printf("\r\n...Lab 2... ");

	while (!GPIO_readPins(GPIOB, GPIO_PIN2)) {
		if (!GPIO_readPins(GPIOA, GPIO_PIN7)) {
			delay_cycles(320e3);
			if (!GPIO_readPins(GPIOA, GPIO_PIN7)) {
				setRGB(0);
			}

			do {
				while (!GPIO_readPins(GPIOA, GPIO_PIN7)) {
				}
				delay_cycles(320e3);
			} while (!GPIO_readPins(GPIOA, GPIO_PIN7));

			setRGB(-1);
		}
		else if (!GPIO_readPins(GPIOA, GPIO_PIN14)) {
			delay_cycles(320e3);
			if (!GPIO_readPins(GPIOA, GPIO_PIN14)) {
				setRGB(1);
			}

			do {
				while (!GPIO_readPins(GPIOA, GPIO_PIN14)) {
				}
				delay_cycles(320e3);
			} while (!GPIO_readPins(GPIOA, GPIO_PIN14));

			setRGB(-1);
		}
		else if (!GPIO_readPins(GPIOB, GPIO_PIN5)) {
			delay_cycles(320e3);
			if (!GPIO_readPins(GPIOB, GPIO_PIN5)) {
				setRGB(2);
			}

			do {
				while (!GPIO_readPins(GPIOB, GPIO_PIN5)) {
				}
				delay_cycles(320e3);
			} while (!GPIO_readPins(GPIOB, GPIO_PIN5));

			setRGB(-1);
		}
		else if (!GPIO_readPins(GPIOB, GPIO_PIN21)) {
			delay_cycles(320e3);
			if (!GPIO_readPins(GPIOB, GPIO_PIN21)) {
				setRGB(3);
			}

			do {
				while (!GPIO_readPins(GPIOB, GPIO_PIN21)) {
				}
				delay_cycles(320e3);
			} while (!GPIO_readPins(GPIOB, GPIO_PIN21));

			setRGB(-1);
		}
		else if (!GPIO_readPins(GPIOB, GPIO_PIN23)) {
			delay_cycles(320e3);
			if (!GPIO_readPins(GPIOB, GPIO_PIN23)) {
				setRGB(4);
			}

			do {
				while (!GPIO_readPins(GPIOB, GPIO_PIN23)) {
				}
				delay_cycles(320e3);
			} while (!GPIO_readPins(GPIOB, GPIO_PIN23));

			setRGB(-1);
		}
		else if (!GPIO_readPins(GPIOB, GPIO_PIN25)) {
			delay_cycles(320e3);
			if (!GPIO_readPins(GPIOB, GPIO_PIN25)) {
				setRGB(5);
			}

			do {
				while (!GPIO_readPins(GPIOB, GPIO_PIN25)) {
				}
				delay_cycles(320e3);
			} while (!GPIO_readPins(GPIOB, GPIO_PIN25));

			setRGB(-1);
		}
		else {
			setRGB(-1);
		}

	}
	setRGB(-1);
	while (GPIO_readPins(GPIOB, GPIO_PIN2));

	while (1) {
		length = 1;
		displayTime = 500;
		srand(milliseconds);
		for (i = 0; i < 10; i++) {
			pattern[i] = rand() % 6;
		}

		start = milliseconds;
		while ((uint32_t)(milliseconds - start) < 1000u);

		while (1) {
			GPIO_clearPins(GPIOA, GPIO_PIN13);
			GPIO_setPins(GPIOA, GPIO_PIN12);

			for (i = 0; i < length; i++) {
				setRGB(pattern[i]);

				start = milliseconds;
				while (milliseconds - start < displayTime);

				setRGB(-1);

				start = milliseconds;
				while (milliseconds - start < displayTime);
			}

			GPIO_clearPins(GPIOA, GPIO_PIN12);
			GPIO_setPins(GPIOA, GPIO_PIN13);

			correct = 1;

			for (j = 0; j < length; j++) {
				answer[j] = -1;
				responseStart = milliseconds;

				while (answer[j] == -1) {
					if ((uint32_t)(milliseconds - responseStart) >= 3000u) {
						answer[j] = -2;
						break;
					}
					pressed = -1;

					if (!GPIO_readPins(GPIOA, GPIO_PIN7)) {
						pressed = 0;
					}
					else if (!GPIO_readPins(GPIOA, GPIO_PIN14)) {
						pressed = 1;
					}
					else if (!GPIO_readPins(GPIOB, GPIO_PIN5)) {
						pressed = 2;
					}
					else if (!GPIO_readPins(GPIOB, GPIO_PIN21)) {
						pressed = 3;
					}
					else if (!GPIO_readPins(GPIOB, GPIO_PIN23)) {
						pressed = 4;
					}
					else if (!GPIO_readPins(GPIOB, GPIO_PIN25)) {
						pressed = 5;
					}

					if (pressed != -1) {
						delay_cycles(320e3);

						if (
						    (pressed == 0 && !GPIO_readPins(GPIOA, GPIO_PIN7)) ||
						    (pressed == 1 && !GPIO_readPins(GPIOA, GPIO_PIN14)) ||
						    (pressed == 2 && !GPIO_readPins(GPIOB, GPIO_PIN5)) ||
						    (pressed == 3 && !GPIO_readPins(GPIOB, GPIO_PIN21)) ||
						    (pressed == 4 && !GPIO_readPins(GPIOB, GPIO_PIN23)) ||
						    (pressed == 5 && !GPIO_readPins(GPIOB, GPIO_PIN25))
						) {
							setRGB(pressed);

							do {
								while (
								    !GPIO_readPins(GPIOA, GPIO_PIN7)  ||
								    !GPIO_readPins(GPIOA, GPIO_PIN14) ||
								    !GPIO_readPins(GPIOB, GPIO_PIN5)  ||
								    !GPIO_readPins(GPIOB, GPIO_PIN21) ||
								    !GPIO_readPins(GPIOB, GPIO_PIN23) ||
								    !GPIO_readPins(GPIOB, GPIO_PIN25)
								) {
									if ((uint32_t)(milliseconds - responseStart) >= 3000u) {
										answer[j] = -2;
										break;
									}
								}
								if (answer[j] == -2) break;
								delay_cycles(320e3);
								if ((uint32_t)(milliseconds - responseStart) >= 3000u) {
									answer[j] = -2;
									break;
								}
							} while (
							    !GPIO_readPins(GPIOA, GPIO_PIN7)  ||
							    !GPIO_readPins(GPIOA, GPIO_PIN14) ||
							    !GPIO_readPins(GPIOB, GPIO_PIN5)  ||
							    !GPIO_readPins(GPIOB, GPIO_PIN21) ||
							    !GPIO_readPins(GPIOB, GPIO_PIN23) ||
							    !GPIO_readPins(GPIOB, GPIO_PIN25)
							);

							setRGB(-1);
							if (answer[j] != -2) answer[j] = pressed;
						}
					}
				}

				if (answer[j] != pattern[j]) {
					correct = 0;
					printf("Incorrect!\r\n");
					break;
				}

			}

			if (!correct || length == 10) break;

			printf("Correct!\r\n");
			length++;
			displayTime = displayTime * 9 / 10;
		}

		setRGB(-1);
		if (correct) {
			printf("You win!\r\n");
			GPIO_clearPins(GPIOA, GPIO_PIN12);
			GPIO_setPins(GPIOA, GPIO_PIN13);
		} else {
			printf("Score: %u\r\n", (unsigned int)(length - 1));
			GPIO_clearPins(GPIOA, GPIO_PIN13);
			GPIO_setPins(GPIOA, GPIO_PIN12);
		}
		printf("Press and release PB2 to play again.\r\n");

		blinkStart = milliseconds;
		while (!GPIO_readPins(GPIOB, GPIO_PIN2)) {
			if ((uint32_t)(milliseconds - blinkStart) >= 250u) {
				if (correct) {
					GPIO_togglePins(GPIOA, GPIO_PIN13);
				} else {
					GPIO_togglePins(GPIOA, GPIO_PIN12);
				}
				blinkStart = milliseconds;
			}
		}
		GPIO_clearPins(GPIOA, GPIO_PIN12 | GPIO_PIN13);
		while (GPIO_readPins(GPIOB, GPIO_PIN2));
	}
}

void GPIOInit(void) {
	GPIO_initDigitalInput(GPIOA, GPIO_PIN7 | GPIO_PIN14);
	GPIO_initDigitalInput(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25 );
	GPIO_initDigitalInput(GPIOB, GPIO_PIN2);

	GPIO_setInternalResistor(GPIOA, GPIO_PIN7 | GPIO_PIN14, GPIO_PULL_UP);
	GPIO_setInternalResistor(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25, GPIO_PULL_UP);

	GPIO_initDigitalOutput(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
	GPIO_initDigitalOutput(GPIOA, GPIO_PIN12 | GPIO_PIN13);
	GPIO_clearPins(GPIOA, GPIO_PIN12 | GPIO_PIN13);
	GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);
}

void setRGB(int8_t color) {
	GPIO_clearPins(GPIOB, GPIO_PIN22 | GPIO_PIN26 | GPIO_PIN27);

	if (color == 0) {
		GPIO_setPins(GPIOB, GPIO_PIN26);
	}
	else if (color == 1) {
		GPIO_setPins(GPIOB, GPIO_PIN27);
	}
	else if (color == 2) {
		GPIO_setPins(GPIOB, GPIO_PIN22);
	}
	else if (color == 3) {
		GPIO_setPins(GPIOB, GPIO_PIN26 | GPIO_PIN22);
	}
	else if (color == 4) {
		GPIO_setPins(GPIOB, GPIO_PIN27 | GPIO_PIN22);
	}
	else if (color == 5) {
		GPIO_setPins(GPIOB, GPIO_PIN26 | GPIO_PIN27);
	}

}

void timerInit(void) {
	timerConfig.mode = TIMER_MODE_PERIODIC_UP;
	timerConfig.clksrc = TIMER_CLOCK_BUSCLK;
	timerConfig.clkdivratio = TIMER_CLOCK_DIVIDE_8;
	timerConfig.clkprescale = 4;
	timerConfig.period = 799;

	Timers_initTimer(TIMG8, &timerConfig);

	Timers_enableInterrupt(TIMG8, TIMER_INTSRC_ZERO);
	NVIC_EnableIRQ(TIMG8_INT_IRQn);

	Timers_startTimer(TIMG8);
}

void TIMG8_IRQHandler(void) {
	if (Timers_getActiveInterrupt(TIMG8) == TIMER_INTSRC_ZERO) {
		milliseconds++;
	}
}
