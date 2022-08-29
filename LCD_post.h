/* 
 * File:   LCD_post.h
 * Author: paola
 *
 * Created on 25 de agosto de 2022, 22:47
 */

#ifndef LCD_POST_H
#define	LCD_POST_H
#define _XTAL_FREQ 8000000

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);

void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);


#endif	/* LCD_POST_H */

