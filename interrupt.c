#include "interrupt.h"

ISR (TIMER1_COMPA_vect)
{
  SendStr(TIMER1_STR);
}


ISR (TIMER2_COMP_vect)
{
  SendStr(TIMER2_STR);
}

ISR(USART_RXC_vect)
{
	char bf = UDR;
	if (bf == ':' || IDX >= LEN)
	{
		buffer_rx[IDX] = '\0';
		IDX=0;
		//done=1;
		handler(buffer_rx);
		clearStr(buffer_rx);
	}
	else
	{
	  buffer_rx[IDX]=bf;
	  IDX++;	
	}
}