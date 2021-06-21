#include "timer.h"


void timer_1_setup()
{
  TCCR1B |= (1<<WGM12); // ������������� ����� ��� (����� �� ����������)
  TIMSK |= (1<<OCIE1A); //������������� ��� ���������� ���������� 1��� �������� �� ���������� � OCR1A(H � L)
  TCCR1B &= ~0b00000111;
  TCCR1B |= 0b00000101; //�������� 1024 => ���������� �������� ������ 0.512 ms
}

void timer_2_setup()
{
  TCCR2 |= (1<<WGM21);
  TIMSK |= (1<<OCIE2); //������������� ��� ���������� ���������� 1��� �������� �� ���������� � OCR1A(H � L)
  TCCR2 &= ~0b00000111;
  TCCR2 |= 0b00000111; //�������� 1024 => ���������� �������� ������ 0.512 ms
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