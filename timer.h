#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

void timer_1_setup();
void timer_2_setup();
void timer_1_set(uint8_t interval);
void timer_2_set(uint8_t interval);
void timer_1_reset();
void timer_2_reset();
#endif /* TIMER_H_ */