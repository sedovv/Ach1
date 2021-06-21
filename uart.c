#include "uart.h"

void uart_setup()
{
    UBRRL= MYUBRR;
    UCSRB=(1<<TXEN)|(1<<RXEN)|(1<<RXCIE);
    UCSRC=(1<<URSEL)|(3<<UCSZ0);
	//UCSRA=(1<<U2X);
	IDX=0;
	done=0;
}

void USART_Transmit(unsigned char data)  //Функция отправки данных
{
	while ( !(UCSRA & (1<<UDRE)) );		 //Ожидание опустошения буфера приема
	while ( !(UCSRA & (1<<UDRE)) );		 //Ожидание опустошения буфера приема
	UDR = data;							 //Начало передачи данных
}

int writeSerial(char* str)
{
	for(int i=0;i<strlen(str); i++)		
	{
		while(!(UCSRA&(1<<UDRE))){};    
		UDR = str[i];
	}
	return 0;
}

void SendStr(char *string)				
{
  while (*string!='\0')					 //Пока первый байт строки не 0 (конец ASCIIZ строки)
  {
	while ( !(UCSRA & (1<<UDRE)) );		 //Ожидание опустошения буфера приема
	UDR = *string;	
	string++;							 //Не забывая увеличивать указатель,
  }									     //Выбирая новую букву из строки.
}

void clearStr(char* str)
{
	for(int i=0;i<LEN;i++)
    str[i]=0;
}

