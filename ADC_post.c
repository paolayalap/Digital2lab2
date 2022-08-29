/* 
 * File:   ADC_post.c
 * Author: paola
 *
 * Created on 25 de agosto de 2022, 22:27
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ADC_post.h"


#define _XTAL_FREQ 8000000



//Conversion de ADC
void convert(char *data, float a, int place) //definition
{
    
	int temp = a;
	float x = 0.0;
	int digits = 0;
	int i = 0, mu = 1;
	int j = 0;
	if(a<0)
	{
		a = a*-1;
		data[i] = '-';
		i++;
	}

	//exponent component
	while(temp != 0){
		temp = temp/10;
		digits++;
	}

	while(digits != 1){
		if(digits == 1)mu = 1;
		else for(j=2; j<=digits; j++)mu = mu*10;

		x = a/mu;
		a = a - ((int)x*mu);
		data[i] = 0x30 + ((int)x);
		i++;
		digits--;
		mu = 1;

	}

	data[i] = '.';
	i++;
	digits = 0;
	for(j = 1; j<=place; j++)mu=mu*10;
	x = (a-(int)a)*mu;
	a = x;
	temp = a;
	x = 0.0;
	mu = 1;
	digits = place;

	while(digits != 1){
		if(digits == 1)mu = 1;
		else for (j=2;j<=digits;j++)mu = mu*10;

		x = a/mu;
		a = a - ((int)x*mu);
		data[i] = 0x30 + ((int)x);
		i++;
		digits--;
		mu = 1;

	}

	data[i] = '\n';

}


void start_adc(uint8_t frec, uint8_t isr, uint8_t Vref, uint8_t justRL){
	
	ADCON0bits.ADON = 1;
	switch (frec){
		case 1:	//Fosc/2
			ADCON0bits.ADCS0 = 0;
			ADCON0bits.ADCS1 = 0;
			break;
		case 2:	//Fosc/8
			ADCON0bits.ADCS0 = 1;
			ADCON0bits.ADCS0 = 0;
			break;
		case 3:	//Fosc/32
			ADCON0bits.ADCS0 = 0;
			ADCON0bits.ADCS1 = 1;
			break;
		case 4:	//FRC
			ADCON0bits.ADCS0 = 1;
			ADCON0bits.ADCS0 = 1;
			break;

	}

	if (isr == 1){
	PIE1bits.ADIE = 1; //se habilita la interrupcion del ADC
	PIE1bits.ADIE = 0;	//se limpia la bandera del ADC
	}

	if (justRL == 0){
		ADCON1bits.ADFM = 0; // se justifica a la izquierda
	}
	else{
		ADCON1bits.ADFM = 1; //se justifica a la derecha
	}

	switch (Vref){

		case 0: //Referencia en VDD y VSS
			ADCON1bits.VCFG0 = 0;
			ADCON1bits.VCFG1 = 0;
			break;

		case 1: //Referencia en Vref+ pin y VSS
			ADCON1bits.VCFG0 = 1;
			ADCON1bits.VCFG1 = 0;
			break;
		case 2: //Referencia en VDD y Vref- pin
			ADCON1bits.VCFG0 = 0;
			ADCON1bits.VCFG1 = 1;
			break;
		case 3: //Referencia en Vref+ pin y Vref- pin
			ADCON1bits.VCFG0 = 1;
			ADCON1bits.VCFG1 = 1;
			break;

	}
}

void start_ch(uint8_t channel){
    switch(channel){
        case 0: //Analogico en pin RA0
            ANSELbits.ANS0 = 1;
            break;
        case 1: //Analogico en pin RA1
            ANSELbits.ANS1 = 1;
            break;
        case 2: //Analogico en pin RA2
            ANSELbits.ANS2 = 1;
            break;
        case 3: //Analogico en pin RA3
            ANSELbits.ANS3 = 1;
            break;
        case 4: //Analogico en pin RA4
            ANSELbits.ANS4 = 1;
            break;
        case 5: //Analogico en pin RE0
            ANSELbits.ANS5 = 1;
            break;
        case 6: //Analogico en pin RE1
            ANSELbits.ANS6 = 1;
            break;
        case 7: //Analogico en pin RE2
            ANSELbits.ANS7 = 1;
            break;
        default:
            ANSELbits.ANS0 = 1;
            break;

    }


}


void Select_ch(uint8_t channel){
	switch (channel){
		case 0:	//AN0
			ADCON0bits.CHS = 0b0000;
			break;
		case 1:	//AN1
			ADCON0bits.CHS = 0b0001;
			break;
		case 2:	//AN2
			ADCON0bits.CHS = 0b0010;
			break;
		case 3:	//AN3
			ADCON0bits.CHS = 0b0011;
			break;
		case 4:	//AN4
			ADCON0bits.CHS = 0b0100;
			break;
		case 5:	//AN5
			ADCON0bits.CHS = 0b0101;
			break;
		case 6:	//AN6
			ADCON0bits.CHS = 0b0110;
			break;
		case 7:	//AN7
			ADCON0bits.CHS = 0b0111;
			break;
		case 8:	//AN8
			ADCON0bits.CHS = 0b1000;
			break;
		case 9:	//AN9
			ADCON0bits.CHS = 0b1001;
			break;
		case 10://AN10
			ADCON0bits.CHS = 0b1010;
			break;
		case 11://AN11
			ADCON0bits.CHS = 0b1011;
			break;
		case 12://AN12
			ADCON0bits.CHS = 0b1100;
			break;
		case 13://AN13
			ADCON0bits.CHS = 0b1101;
			break;
		case 14://AN14
			ADCON0bits.CHS = 0b1110;
			break;

		case 15://AN15
			ADCON0bits.CHS = 0b1111;
			break;

	}
	__delay_us(200);    //Tiempo recomendado de espera por cambio de canal
	ADCON0bits.GO = 1;

}