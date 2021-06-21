#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "timer.h"
#include <avr/interrupt.h>

extern char TIMER1_STR[MAX_LENGTH];
extern char TIMER2_STR[MAX_LENGTH];
extern uint8_t TIMER1_INTERVAL;   
extern uint8_t TIMER2_INTERVAL;

extern char buffer[LEN];
extern volatile unsigned char done;
extern volatile unsigned char IDX;

extern void handler(char *ptr);


#endif /* INTERRUPT_H_ */