/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef INT_LCD_SPI_H
#define	INT_LCD_SPI_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

typedef enum HD44780_configuration_commands{
  Clear_display,
  Return_home,
  Display_on,
  Display_off,
  Cursor_on,
  Cursor_off,
  Cursor_blink_on,
  Cursor_blink_off
}LCD_configuration_command;

//external function declarations:
void LCD_init();
void LCD_send_string(char *str);
void LCD_set_cursor(uint8_t row, uint8_t column);
void LCD_config(LCD_configuration_command command);


//external variable declarations:
typedef volatile struct{
  uint8_t Increment                :1;
  uint8_t Display_shift            :1;
  uint8_t Display_on_off           :1; 
  uint8_t Cursor_on_off            :1;
  uint8_t Cursor_blink             :1;
  uint8_t Shift_method             :1;
  uint8_t Shift_direction          :1;
  uint8_t Data_length              :1;
  uint8_t Number_lines             :1;
  uint8_t Font                     :1;
  uint8_t Backlight                :1;
}HD44780_configuration_state;

HD44780_configuration_state LCD_configuration_state;

typedef volatile struct{
  uint8_t Clear_display;
  uint8_t Return_home;
  uint8_t Entry_mode_set;
  uint8_t Display_on_off_control;
  uint8_t Cursor_or_display_shift;
  uint8_t Function_set;
  uint8_t Set_DDRAM_address;
}HD44780_instruction_set;

HD44780_instruction_set LCD_instruction_set;

#endif	/* INT_LCD_SPI_H*/

