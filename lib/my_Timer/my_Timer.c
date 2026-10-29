#include "my_Timer.h"

void delay_us(uint16_t time_us)
{
      htim2.Instance->CNT = 0;
      while (htim2.Instance->CNT < time_us)
      {
      }
}

void delay_ms(uint16_t time_ms)
{
      for (int i = 0; i < time_ms; i++)
      {
            delay_us(1000);
      }
}