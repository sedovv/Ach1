#include "config.h"

//0 - ����, 1 - �����
void pin_setup()
{
	DDRC = 0b00000000;
	DDRB = 0b00000000;
	DDRD = 0b00000000;
}