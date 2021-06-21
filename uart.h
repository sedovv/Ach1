#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <string.h>

#define FOSC0 2000000 // Частота тактирования микроконтроллера
#define BAUD 9600
#define MYUBRR FOSC0/16/BAUD-1
#define MAX_LENGTH 10 // Максимальная длина строки
#define LEN 15

void uart_setup();
void USART_Transmit(unsigned char data);
int writeSerial(char* str);
void SendStr(char *string);	
void clearStr(char* str);

char buffer_rx[LEN];
char buffer_tx[LEN];
volatile unsigned char done;
volatile unsigned char IDX;

#endif /* UART_H_ */