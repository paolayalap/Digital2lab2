/* 
 * File:   mainpost.c
 * Author: paola
 *
 * Created on 25 de agosto de 2022, 22:26
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//LIBRERÍAS
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD_post.h"
#include "ADC_post.h"
#include "OSC_post.h"

//DEFINICIONES
#define _XTAL_FREQ 8000000
#define RS RC0
#define EN RC1
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#define _tmr0_value 217


//VARIABLES
uint8_t canal_act = 0;
volatile uint8_t var_adc0 = 0;
volatile uint8_t var_adc1 = 0;
char adc0[10];
char adc1[10];
float con0 = 0;
float con1 = 0;

//DECLARACIÓN DE FUNCIONES
void config(void);


//INTERRUPCIONES


//CONFIGURACIÓN GENERAL
int main(){
	config();
	Lcd_Init();
    
	start_adc(2,1,0,0); // Fosc/8, No ISR de ADC, Ref Vdd y Vcc, a la izquierda
	start_ch(0);        //Habilita el pin del puerto RA0
	start_ch(1);        //Habilita el pin del puerto RA1
	Select_ch(0);       //Selecciona el canal e inicia la conversión
    Select_ch(1);       //Selecciona el canal e inicia la conversión
	
	

	while(1){
        Lcd_Clear();
		Lcd_Set_Cursor(1,1);        //En esta posición del LCD
		Lcd_Write_String("S1");     //Se escribe esto
		Lcd_Set_Cursor(1,8);
		Lcd_Write_String("S2");
		

		if(PIR1bits.ADIF == 1){
			if(canal_act == 0){
				var_adc0 = ADRESH; //se guarda el valor convertido en la variable
				Select_ch(0);
				canal_act++;
				}
				else{
				var_adc1 = ADRESH; //se guarda el valor convertido en la variable
				Select_ch(1);
				canal_act--;
				}
				PIR1bits.ADIF = 0;
		}
        
        con0 = 0; //se reinicia las veces que se inicia un proceso de envío
        con1 = 0;
        
        //ADC canal 0 
        con0 = (var_adc0 / (float)255)*5;
        convert(adc0, con0, 2);
        
        //ADC canal 1 
        con1 = (var_adc1 / (float)255)*5;
        convert(adc1, con1, 2);
        
        /*Datos de LCD*/
		
		Lcd_Set_Cursor(2,1);
		Lcd_Write_String(adc0);
		Lcd_Set_Cursor(2,5);
		Lcd_Write_String("V");

		Lcd_Set_Cursor(2,7);
		Lcd_Write_String(adc1);
		Lcd_Set_Cursor(2,11);
		Lcd_Write_String("V");

		__delay_ms(5000);
	}


		
        
//        return; lo podría haber usado en caso hubiese 
//        puesto void en lugar de int, con int por lo que tengo
//        entendido, no es necesario
} 





void config(void){
	//Configuración de los puertos 
	ANSEL = 0X00;		//RA0 y RA1 se coloca como entrada analógica 
	ANSELH = 0X00;		//PORTC y PORTD como salidas

	TRISA = 0X03;
	TRISC = 0X00;
	TRISD = 0X00;

	PORTA = 0X00;
	PORTC = 0X00;
	PORTD = 0X00;
   
    return;
}






