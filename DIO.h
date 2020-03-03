
/*
 * MCAL_AVR.h
 *
 *  Created on: Dec 30, 2019
 *      Author: Amr Mohammed Kamal
 */

#ifndef MCAL_AVR_H_
#include <avr/io.h>
#include <util/delay.h>
#define MCAL_AVR_H_
#define ris_edge 	0
#define fal_edge 	1
#define log_change	2
#define low_lev		3
#define INT0		6
#define INT1		7
#define INT2		5
#define PORTa 0
#define PORTb 1
#define PORTc 2
#define PORTd 3
#define PORTe 4
#define DDRa 10
#define DDRb 11
#define DDRc 12
#define DDRd 13
#define PINa 20
#define PINb 21
#define PINc 22
#define PINd 23
#define INPUT 0
#define OUTPUT 1
#define INPUT_FLOAT 2
#define PORT_OUT 0xff
#define PORT_IN 0x00
#define High 1
#define Low 0
#define M_delay_s(var) _delay_ms(1000*var)
#define M_delay_ms(var) _delay_ms(var)
#define M_delay_us(var) _delay_us(var)

void (*DefINT)(void);
void (*INTP_0)(void); //portb pb2 with Microcontroller Control Register MCUCR and General Interrupt Control Register GICR
void (*INTP_1)(void); //portd  pd2
void (*INTP_2)(void); //portd pd3
void INTP_0En (u8_t mode);
void PICredirect_INTP_0(void (*ptr) (void));
void PICredirect_INTP_1(void (*ptr) (void));
void PICredirect_INTP_2(void (*ptr) (void));
volatile GPIOXX* MPIC_getgpio(u8_t PORTxx);
void MPIC_SetBitDir( u8_t  PORTxx , u8_t bitx , u8_t dir);
void MPIC_SetBitsDir( u8_t  PORTxx , u8_t bitx , u8_t bit_counuter , u8_t dir);
void MPIC_SetPORTDir(u8_t  PORTxx ,u8_t dir);
void MPIC_SetBitVal( u8_t  PORTxx , u8_t bitx , u8_t val);
void MPIC_SetBitSVal( u8_t  PORTxx , u8_t bitx , u8_t val,u8_t bit_counuter);
void MPIC_SetPORTVal( u8_t  PORTxx , u8_t val );
u8_t MPIC_GetBitVal ( u8_t  PORTxx , u8_t bitx);
u8_t MPIC_GetPINVal( u8_t  PORTxx );
void PIC_disGINT(void){

}
void PIC_disINT(u8_t INT){

}

#endif /* MCAL_AVR_H_ */
