#include "timer.h"


void timer_1_setup()
{
  TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
  TIMSK |= (1<<OCIE1A); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
  TCCR1B &= ~0b00000111;
  TCCR1B |= 0b00000101; //делитель 1024 => увеличение счётчика каждые 0.512 ms
}

void timer_2_setup()
{
  TCCR2 |= (1<<WGM21);
  TIMSK |= (1<<OCIE2); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
  TCCR2 &= ~0b00000111;
  TCCR2 |= 0b00000111; //делитель 1024 => увеличение счётчика каждые 0.512 ms
}


void timer_1_set(uint8_t interval)
{
  OCR1AL = interval - 1;
}

void timer_2_set(uint8_t interval)
{
  OCR2 = interval - 1;
}

void timer_1_reset()
{
  TCNT1L = 0;
  TCNT1H = 0;
}

void timer_2_reset()
{
  TCNT2 = 0;
}