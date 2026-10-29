#ifndef _DHT11_H_
#define _DHT11_H_

#include "stm32f1xx_hal.h"
#include "my_Timer.h"

typedef struct
{
      GPIO_TypeDef *DATA_PORT;
      uint16_t Data_Pin;
} DHT11 ;

uint8_t DHT11_start(DHT11 *DHT11);
void set_pin_to_output(DHT11 *dht11);
void set_pin_to_input(DHT11 *dht11);
uint8_t DHT11_read_byte(DHT11 *dht11);
#endif
