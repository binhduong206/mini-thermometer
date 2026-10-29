#include "my_DHT11.h"

void set_pin_to_input(DHT11 *dht11)
{
      GPIO_InitTypeDef GPIO_InitStruct = {0};
      GPIO_InitStruct.Pin = dht11->Data_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      GPIO_InitStruct.Pull = GPIO_PULLUP;
      HAL_GPIO_Init(dht11->DATA_PORT, &GPIO_InitStruct);
}

void set_pin_to_output(DHT11 *dht11)
{
      GPIO_InitTypeDef GPIO_InitStruct = {0};
      GPIO_InitStruct.Pin = dht11->Data_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(dht11->DATA_PORT, &GPIO_InitStruct);
}

uint8_t DHT11_start(DHT11 *dht11)
{
      uint16_t timeout;

      set_pin_to_output(dht11);
      HAL_GPIO_WritePin(dht11->DATA_PORT, dht11->Data_Pin, GPIO_PIN_SET);
      delay_us(1);
      HAL_GPIO_WritePin(dht11->DATA_PORT, dht11->Data_Pin, GPIO_PIN_RESET);
      delay_ms(20);
      HAL_GPIO_WritePin(dht11->DATA_PORT, dht11->Data_Pin, GPIO_PIN_SET);
      delay_us(30);
      set_pin_to_input(dht11);

      timeout = 0;
      while (HAL_GPIO_ReadPin(dht11->DATA_PORT, dht11->Data_Pin) == GPIO_PIN_SET)
      {
            timeout++;
            delay_us(1);
            if (timeout > 100) return 0;
      }

      timeout = 0;
      while (HAL_GPIO_ReadPin(dht11->DATA_PORT, dht11->Data_Pin) == GPIO_PIN_RESET)
      {
            timeout++;
            delay_us(1);
            if (timeout > 100) return 0;
      }

      timeout = 0;
      while (HAL_GPIO_ReadPin(dht11->DATA_PORT, dht11->Data_Pin) == GPIO_PIN_SET)
      {
            timeout++;
            delay_us(1);
            if (timeout > 100) return 0;
      }

      return 1;
}

uint8_t DHT11_read_byte(DHT11 *dht11)
{
    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        uint16_t timeout = 0;

        // Chờ hết mức LOW của bit
        while (HAL_GPIO_ReadPin(dht11->DATA_PORT, dht11->Data_Pin) == GPIO_PIN_RESET)
        {
            delay_us(1);

            if (++timeout > 100)
                return 0;
        }

        // Lấy mẫu trong xung HIGH
        delay_us(40);

        data <<= 1;

        if (HAL_GPIO_ReadPin(dht11->DATA_PORT, dht11->Data_Pin) == GPIO_PIN_SET)
        {
            data |= 1;
        }

        // Chờ xung HIGH kết thúc
        timeout = 0;

        while (HAL_GPIO_ReadPin(dht11->DATA_PORT, dht11->Data_Pin) == GPIO_PIN_SET)
        {
            delay_us(1);

            if (++timeout > 100)
                return 0;
        }
    }

    return data;
}

