/* 
 * File:   OSC_post.h
 * Author: paola
 *
 * Created on 25 de agosto de 2022, 22:30
 */

#ifndef OSC_POST_H
#define	OSC_POST_H
#define _XTAL_FREQ 8000000

void config_osc(uint8_t frec);
void config_tmr0(uint8_t prescaler);

#endif	/* OSC_POST_H */

