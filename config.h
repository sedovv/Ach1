#ifndef CONFIG_H_
#define CONFIG_H_
#define F_CPU 2000000UL


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "timer.h"
#include "interrupt.h"

void pin_setup();


#endif /* CONFIG_H_ */