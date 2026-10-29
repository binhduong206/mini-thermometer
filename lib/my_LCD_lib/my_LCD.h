#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f1xx_hal.h"
#include "my_Timer.h"

#define CONFIG_LCD_4_BITS_MODE
#ifdef CONFIG_LCD_4_BITS_MODE
#define LCD_DATA_PINS_QTY 4
#else
#define LCD_DATA_PINS_QTY 8
#endif

typedef struct
{
      /* PORT_MODE
            E : Enable signal for writing or reading data
            RS: Signal for selecting registers:
                  1 : Data register (for read and write)
                  0 : Instruction Register (for write), Busy flag-Address Counter (for read).
            RW:   0 : write mode
                  1 : read mode
      */

      /* PORT_DATA
            4bits : 4 - 7
            8bits : 0 - 7
      */

      GPIO_TypeDef *RW_PORT;
      uint16_t RW_Pin;

      GPIO_TypeDef *RS_PORT;
      uint16_t RS_Pin;

      GPIO_TypeDef *E_PORT;
      uint16_t E_Pin;

      GPIO_TypeDef *DATA_PORT;
      uint16_t DATA_PINS[LCD_DATA_PINS_QTY];
} LCD;

void LCD_init(LCD *lcd);
void LCD_pulse_enable(LCD *lcd);
void LCD_clear_screen(LCD *lcd);
void LCD_write_byte(LCD *lcd, uint8_t data, uint8_t mode);
void LCD_print_data(LCD *lcd, char data);
void LCD_print_buffer(LCD *lcd, char *buffer);
void LCD_go_to_xy(LCD *lcd, uint8_t x, uint8_t y);

#endif
