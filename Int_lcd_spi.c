/*
 * File:   Int_lcd_spi.c
 * Author: rbs
 *
 * Created on April 17, 2017, 9:22 PM
 */


#include <xc.h>
#include "Int_lcd_spi.h"

//internal function declarations:
void Write_data(uint8_t data);
void Format_data(uint8_t data, uint8_t Instruction_type);

//internal functions

void Write_data(uint8_t data){
  uint8_t Clear_enable = ~(0x80);
  Clear_enable += data;
// _CS = 0;                   //chip select = 0
//  SSP1BUF = (data|_E);       //send out data with E pin high
//  __delay_ms(2);
//  _CS = 1;                   //clock data out of LCD backpack shift register
//  __delay_ms(2);             //delay for HD44780 to process
//
//   _CS = 0;                  //chip select = 0
//  SSP1BUF = data;            //send out data with E pin low to set HD44780
//  __delay_ms(2);
//  _CS = 1;                   //clock data out of LCD backpack shift register
//  __delay_ms(2);
}

void Format_data(uint8_t data, uint8_t Instruction_type){
  uint8_t Upper_nibble = 0x00;
  uint8_t Lower_nibble = 0x00;
  uint8_t Backlight = LCD_configuration_state.Backlight;
  const uint8_t Set_enable = 0x08;
  uint8_t Set_type = Instruction_type<<2;
  
  /* Adafruit LCD serial backpack bit configuration:
  *  UPPER:
  *  [DB4 | DB5 | DB6 | DB7 | E | RS | RW | LITE]
  *  LOWER:
  *  [DB0 | DB1 | DB2 | DB3 | E | RS | RW | LITE]
  *  HD44780 incoming instruction configuration:
  *  [DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0]
  */
  
  //Reverse bit order of data
  data = (data & 0xF0) >> 4 | (data & 0x0F) << 4;
  data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
  data = (data & 0xAA) >> 1 | (data & 0x55) << 1;
  //data order now:  [DB0 | DB1 | DB2 | DB3 | DB4 | DB5 | DB6 | DB7]
  
  //mask unwanted bits and set enable, register set, and back light bits
  Upper_nibble = ((data & 0x0F)<<4) | Set_enable | Set_type | Backlight;
  Lower_nibble = (data & 0xF0)      | Set_enable | Set_type | Backlight;
  
  Write_data(Upper_nibble);
  Write_data(Lower_nibble);
}

//external functions

void LCD_init(){ 
  //set default HD44780 configuration
  LCD_configuration_state.Data_length     = 0;  //4bit
  LCD_configuration_state.Display_shift   = 0;  //no shift
  LCD_configuration_state.Display_on_off  = 1;  //display on
  LCD_configuration_state.Cursor_on_off   = 1;  //cursor on
  LCD_configuration_state.Cursor_blink    = 0;  //no blink
  LCD_configuration_state.Shift_method    = 0;  //move cursor
  LCD_configuration_state.Font            = 0;  //5x8 pixel font
  LCD_configuration_state.Increment       = 1;  //increment
  LCD_configuration_state.Number_lines    = 1;  //2 lines
  LCD_configuration_state.Shift_direction = 0;  //no shift
  LCD_configuration_state.Backlight       = 1;  //Backlight on
  
  uint8_t Backlight = LCD_configuration_state.Backlight;

  
  //construct the instruction set from the default configuration
  LCD_instruction_set.Clear_display = 0x01;
  LCD_instruction_set.Return_home = 0x02;
  LCD_instruction_set.Entry_mode_set = (0x04)
    |((LCD_configuration_state.Increment)<<1)
    |((LCD_configuration_state.Display_shift)<<0);
  LCD_instruction_set.Display_on_off_control = (0x08)
    |((LCD_configuration_state.Display_on_off)<<2)
    |((LCD_configuration_state.Cursor_on_off)<<1)
    |((LCD_configuration_state.Cursor_blink)<<0);
  LCD_instruction_set.Cursor_or_display_shift = (0x10)
    |((LCD_configuration_state.Shift_method)<<3)
    |((LCD_configuration_state.Shift_direction)<<2);
  LCD_instruction_set.Function_set = (0x20) 
    |((LCD_configuration_state.Data_length)<<4)        
    |((LCD_configuration_state.Number_lines)<<3)        
    |((LCD_configuration_state.Font)<<2);
  LCD_instruction_set.Set_DDRAM_address = 0x80;
  
  //initialization routine
  /* function set to 8bit 8bit TX
   * function set to 8bit 8bit TX
   * function set to 8bit 8bit TX
   * function set to 4bit 8bit TX
   * function set to 4bit 4bit TX
   * Display on/off
   * Display clear
   * Entry mode set
   */
  Write_data(0b11001000 | Backlight);  //first 4 writes are handled manually...
  Write_data(0b11001000 | Backlight);  //in 8 bit mode until 4-bit mode is... 
  Write_data(0b11001000 | Backlight);  //successfully initialized
  Write_data(0b01001000 | Backlight);
  Format_data(LCD_instruction_set.Function_set, 0);
  Format_data(LCD_instruction_set.Display_on_off_control, 0);
  Format_data(LCD_instruction_set.Clear_display, 0);
  Format_data(LCD_instruction_set.Entry_mode_set, 0);
}

void LCD_send_string(char *str){
  while(*str){
    Format_data((uint8_t) *str, 1);
    str++;
  }
}

void LCD_set_cursor(uint8_t row, uint8_t column){
  uint8_t address = 0x00;
  if(row>1){
    address = address + 64;
  }
  address = address + column - 1;
  Format_data(address|LCD_instruction_set.Set_DDRAM_address, 1);  
}

void LCD_config(LCD_configuration_command command){
  //determine the command sent 
  //update LCD_configuration_state if necessary
  //update the LCD_instruction_set if necessary
  //send data out for formatting and serial output
  
  switch (command){
    case Clear_display:
      Format_data(LCD_instruction_set.Clear_display, 0);
      break;
    case Return_home:
      Format_data(LCD_instruction_set.Return_home, 0);
      break;
    case Display_on:
      LCD_configuration_state.Display_on_off  = 1;
      LCD_instruction_set.Display_on_off_control |=
        ((0x01)<<2);
      Format_data(LCD_instruction_set.Display_on_off_control, 0);
      break;
    case Display_off:
      LCD_configuration_state.Display_on_off  = 0;
      LCD_instruction_set.Display_on_off_control &= ~((0x01)<<2);
      Format_data(LCD_instruction_set.Display_on_off_control, 0);
      break;
    case Cursor_on:
      LCD_configuration_state.Cursor_on_off   = 1;
      LCD_instruction_set.Display_on_off_control |= ((0x01)<<1);
      Format_data(LCD_instruction_set.Display_on_off_control, 0);
      break;
    case Cursor_off:
      LCD_configuration_state.Cursor_on_off   = 0;
      LCD_instruction_set.Display_on_off_control &= ~((0x01)<<1);
      Format_data(LCD_instruction_set.Display_on_off_control, 0);
      break;
    case Cursor_blink_on:
      LCD_configuration_state.Cursor_blink = 1;
      LCD_instruction_set.Display_on_off_control |= ((0x01)<<0);
      Format_data(LCD_instruction_set.Display_on_off_control, 0);
      break;
    case Cursor_blink_off:
      LCD_configuration_state.Cursor_blink = 0;
      LCD_instruction_set.Display_on_off_control &= ~((0x01)<<0);
      Format_data(LCD_instruction_set.Display_on_off_control, 0);
      break;
    default:
      break;
  }
}