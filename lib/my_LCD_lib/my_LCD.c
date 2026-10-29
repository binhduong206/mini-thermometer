#include "my_LCD.h"

static void LCD_output_bits(LCD *lcd, uint8_t data)
{
      for (uint8_t i = 0; i < LCD_DATA_PINS_QTY; i++)
      {
            GPIO_PinState pin_state = (data & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
            HAL_GPIO_WritePin(lcd->DATA_PORT, lcd->DATA_PINS[i], pin_state);
      }
}

void LCD_write_byte(LCD *lcd, uint8_t data, uint8_t mode)
{
      HAL_GPIO_WritePin(lcd->RS_PORT, lcd->RS_Pin, mode);

      if (lcd->RW_PORT != NULL)
            HAL_GPIO_WritePin(lcd->RW_PORT, lcd->RW_Pin, GPIO_PIN_RESET);

#ifdef CONFIG_LCD_4_BITS_MODE
      LCD_output_bits(lcd, (data >> 4) & 0x0F);
      LCD_pulse_enable(lcd);
      LCD_output_bits(lcd, data & 0x0F);
      LCD_pulse_enable(lcd);
#else
      LCD_output_bits(lcd, data);
      LCD_pulse_enable(lcd);
#endif
}

void LCD_pulse_enable(LCD *lcd)
{
      HAL_GPIO_WritePin(lcd->E_PORT, lcd->E_Pin, GPIO_PIN_RESET);
      delay_us(1);
      HAL_GPIO_WritePin(lcd->E_PORT, lcd->E_Pin, GPIO_PIN_SET);
      delay_us(100);
      HAL_GPIO_WritePin(lcd->E_PORT, lcd->E_Pin, GPIO_PIN_RESET);
      delay_us(1);
}

void LCD_init(LCD *lcd)
{
      delay_ms(20);
#ifdef CONFIG_LCD_4_BITS_MODE
      // 0x03 -> 0000 0011 : transfer three time for 4bits mode
      LCD_output_bits(lcd, 0x03);
      LCD_pulse_enable(lcd);
      delay_ms(5);
      LCD_output_bits(lcd, 0x03);
      LCD_pulse_enable(lcd);
      delay_us(150);
      LCD_output_bits(lcd, 0x03);
      LCD_pulse_enable(lcd);

      // config 4bit mode
      LCD_output_bits(lcd, 0x02);
      LCD_pulse_enable(lcd);

      LCD_write_byte(lcd, 0x28, 0);
#else
      LCD_write_byte(lcd, 0x38, 0);
#endif
      // display on
      LCD_write_byte(lcd, 0x0C, 0);
      LCD_write_byte(lcd, 0x01, 0);
      delay_ms(2);
      LCD_write_byte(lcd, 0x06, 0);
}

// A : 0x41

void LCD_print_data(LCD *lcd, char data)
{
      LCD_write_byte(lcd, data, 1);
}

void LCD_print_buffer(LCD *lcd, char *buffer)
{
      while (*buffer != NULL)
      {
            LCD_write_byte(lcd, *buffer++, 1);
      }
}

void LCD_clear_screen(LCD *lcd)
{
      LCD_write_byte(lcd, 0x01, 0);
      delay_ms(2);
}

void LCD_go_to_xy(LCD *lcd, uint8_t x, uint8_t y)
{
      uint8_t address = 0;
      if (y == 0)
      {
            address += 0x80 + x;
      }
      else
      {
            address += 0xC0 + x;
      }
      LCD_write_byte(lcd, address, 0);
}

char *unsigned_int_to_string(uint16_t value, char *str)
{
      char temp[10];
      uint8_t i = 0;
      int8_t j;

      do
      {
            temp[i++] = '0' + (value % 10);
            value = value / 10;
      } while (value > 0);

      for (j = 0; j < i; j++)
      {
            str[j] = temp[i - j - 1];
      }

      str[i] = '\0';

      return str;
}

char *signed_int_to_string(int16_t value, char *str)
{
      char temp[10];
      uint8_t i = 0;
      int8_t j;
      value = value * -1;
      str[0] = '-';

      do
      {
            temp[++i] = '0' + (value % 10);
            value = value / 10;
      } while (value > 0);

      for (j = 1; j <= i; j++)
      {
            str[j] = temp[i - j + 1];
      }

      str[i + 1] = '\0';

      return str;
}