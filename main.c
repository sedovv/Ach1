#include "config.h"

/*
����� �������� ������ (s) = ���-�� �������� * 10 / 9600
��� ������ "ping\r\n" ����� �������� = 6.25 ms
��� ������ "pong\r\n" ����� �������� = 6.25 ms
4 ����� �������(ms) = (1/(2000000 / 1024)) * 4 * 1000 = 2.048 ms
��� ����� ��������� ���������� � �����-�� ������ ������� ��������� ��� ������������� ����������
� ���������� ������� �� ���������� ���� �� ���������� ������. �.�. ����� �������� ���� ����� > 4 ������ �������,
�� ��������� ������� �� ����� ���������� ���������.
����� ������� ����������� ��������� �������� ����� ����� 6.25 + 6.25 ms = 12.5 ms (25 ������ �������)
����������� ����� ���������� = 25 + 25 = 50
*/

char TIMER1_STR[MAX_LENGTH] = "ping\r\n";
char TIMER2_STR[MAX_LENGTH] = "pong\r\n";
uint8_t TIMER1_INTERVAL = 255;    //����� ���������(ms) = TIMER1_INTERVAL * 0.512
uint8_t TIMER2_INTERVAL = 255;    //����� ���������(ms) = TIMER1_INTERVAL * 0.512
void handler(char *ptr);          //��������� ������
uint8_t check_min_sum_interval(); //�������� �� ����������� 
void save_str(char *string,char *ptr);
uint8_t tick_timer_count = 25;    //����������� �������� ������

int main(void)
{
    uart_setup();
	timer_1_setup();
	timer_2_setup();
	timer_1_set(TIMER1_INTERVAL);
	timer_2_set(TIMER2_INTERVAL);
	sei();
	SendStr("start\r\n");
 
    while (1) 
    {
		
    }
}
/*
��������:
������� ������ �����/������ ���������

�������:
0 - ��������� ��������� 1
1 - ��������� ��������� 2
2 - ��������� ������ 1
3 - ��������� ������ 2
4 - ����� ������� 1
5 - ����� ������� 2

������ 1:
���� ��������� � ���� ������ "0 100:", �� ���������� �������� �� ������������ � ��������� ��������� 1 �� 100.
���� ��������� � ���� ������ "2 ford\r\n:", �� ���������� �������� �� ������������ � ��������� ������ 1 �� ford\r\n.
*/
void handler(char *ptr)
{
  if (*ptr == '0') //��������� TIMER1_INTERVAL
  {  
	  uint8_t temp = (uint8_t)atoi(ptr + 2);//
	  uint8_t TIMER1_INTERVAL_OLD = TIMER1_INTERVAL;
	  TIMER1_INTERVAL = temp;
	  if(check_min_sum_interval() == 0)
	  {
		  timer_1_reset();
	   	  timer_1_set(TIMER1_INTERVAL);
	  }
	  else
	  {
		  SendStr("ERROR\r\n");
		  TIMER1_INTERVAL = TIMER1_INTERVAL_OLD;
	  }	
  }
  else if (*ptr == '1')
  {
	  uint8_t temp = (uint8_t)atoi(ptr + 2);//
	  uint8_t TIMER2_INTERVAL_OLD = TIMER2_INTERVAL;
	  TIMER2_INTERVAL = temp;
	  if(check_min_sum_interval() == 0)
	  {
		  timer_2_reset();
		  timer_2_set(TIMER2_INTERVAL);
	  }
	  else
	  {
		  SendStr("ERROR\r\n");
		  TIMER2_INTERVAL = TIMER2_INTERVAL_OLD;
	  }
  }
  else if (*ptr == '2')
  { 
	 char TIMER1_STR_OLD[MAX_LENGTH];
	 save_str(TIMER1_STR,TIMER1_STR_OLD);
	 save_str((ptr + 2),TIMER1_STR);
	 if(check_min_sum_interval())
	 {
		 SendStr("ERROR\r\n");
		 save_str(TIMER1_STR_OLD, TIMER1_STR);
	 }
  }
  else if (*ptr == '3')
  {
	  char TIMER2_STR_OLD[MAX_LENGTH];
	  save_str(TIMER2_STR,TIMER2_STR_OLD);
	  save_str((ptr + 2),TIMER2_STR);
	  if(check_min_sum_interval())
	  {
		  SendStr("ERROR\r\n");
		  save_str(TIMER2_STR_OLD, TIMER2_STR);
	  }
  }
  else if (*ptr == '4')
  {
	  timer_1_reset();
  }
  else if (*ptr == '5')
  {
      timer_2_reset();
  }
}

uint8_t check_min_sum_interval()
{
	uint8_t TIMER1_STR_COUNT = strlen(TIMER1_STR);
	uint8_t TIMER2_STR_COUNT = strlen(TIMER2_STR);
	uint32_t TIMER1_STR_TIME_TRANSMIT = TIMER1_STR_COUNT * 1000; 
	TIMER1_STR_TIME_TRANSMIT *= 5; 
	TIMER1_STR_TIME_TRANSMIT *= 5;
	TIMER1_STR_TIME_TRANSMIT /= 24; //us
	uint32_t TIMER2_STR_TIME_TRANSMIT = TIMER2_STR_COUNT * 1000; 
	TIMER2_STR_TIME_TRANSMIT *= 5;
	TIMER2_STR_TIME_TRANSMIT *= 5;
	TIMER2_STR_TIME_TRANSMIT /= 24; //us
	uint16_t time_ticks = tick_timer_count * 512;
	uint32_t sum_time_transmit = TIMER1_STR_TIME_TRANSMIT + TIMER2_STR_TIME_TRANSMIT;
	uint32_t sum_time_transmit_tick = sum_time_transmit / 512;
	
	if (TIMER1_INTERVAL <= sum_time_transmit_tick || TIMER2_INTERVAL <= sum_time_transmit_tick)
	{
	    return 1; //�����	
	}
	
	if (sum_time_transmit > time_ticks)
	{
		return 1; //�����
	}
	return 0; 
}


void save_str(char *string, char *ptr)
{
	while (*string!='\0')				 
	{
		*ptr = *string;
		string++;
		ptr++;							
	}
	*ptr ='\0';									    
}


//$0D$0A: