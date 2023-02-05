//#include <hidef.h>      /* common defines and macros */
#ifndef __12864_H
#define __12864_H 			   
#include "stm32f10x.h"

#define uchar unsigned char
#define uint unsigned int

void LCD_12864_init(void); 
void write_byte(unsigned char A); 
void write_Data(unsigned char b); 
void write_command(unsigned char b); 
void lcd_clear(void);
void lcd_string(unsigned char row,unsigned char col,char *data1);
void clrRAM_12864(void);
void Point_Display(uchar x,uchar y,uchar color);
void Line_Display_Horizontal(uchar x0,uchar x1,uchar y,uchar color);
void Line_Display_Arbitrarily(uchar x0,uchar y0,uchar x1,uchar y1,uchar color);
void Line_Display_Vertical(uchar x,uchar y0,uchar y1,uchar color);
void Round_Display_Hollow(uchar x,uchar y,uchar r);
void Round_Display_Solid(uchar x,uchar y,uchar r);
static void delay_1(vu32 nCount);
static void delay(vu32 nCount);
static void delay_ms(vu32 nCount);

#endif
