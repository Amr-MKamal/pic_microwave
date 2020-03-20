#include "stdtypes.h"
#include "MCAL_PIC18F.h"
#include <pic16/pic18f452.h>
#include <stdio.h>
volatile GPIOXX* MCAL_PIC_getgpio(u8_t PORTxx){
	GPIOXX* GPIOx;
switch (PORTxx){
case PORTa :
	GPIOx->PORTX=(volatile u8_t *)(0x0F80);
	GPIOx->TRISX=(volatile u8_t *)(0x0F92);
	GPIOx->LATX=(volatile u8_t *)(0x0F89);
	return GPIOx;break;
case PORTb :
	GPIOx->PORTX=(volatile u8_t *)(0x0F81);
	GPIOx->TRISX=(volatile u8_t *)(0x0F93);
	GPIOx->LATX=(volatile u8_t *)(0x0F8A);
	return GPIOx;break;
case PORTc :
	GPIOx->PORTX=(volatile u8_t *)(0x0F82);
	GPIOx->TRISX=(volatile u8_t *)(0x0F94);
	GPIOx->LATX=(volatile u8_t *)(0x0F8B);
	return GPIOx;break;
case PORTd :
	GPIOx->PORTX=(volatile u8_t *)(0x0F83);
	GPIOx->TRISX=(volatile u8_t *)(0x0F95);
	GPIOx->LATX=(volatile u8_t *)(0x0F8C);
	return GPIOx;break;
case PORTe :
	GPIOx->PORTX=(volatile u8_t *)(0x0F84);
	GPIOx->TRISX=(volatile u8_t *)(0x0F96);
	GPIOx->LATX=(volatile u8_t *)(0x0F8D);
	return GPIOx;break;
default:
    return NULL;}

return 0;}
void MCAL_PIC_Init_Port(u8_t PORTxx){
if ((PORTxx==PORTd) || (PORTxx==PORTe)) {ADCON1=0xff;}
return;}
void MCAL_PIC_SetBitDir( u8_t  PORTxx , u8_t bitx , u8_t dir){
	GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);
	if (dir==INPUT){set_bit(*(gpio->TRISX),bitx);}
			else {clr_bit(*(gpio->TRISX),bitx);}
return;}
void MCAL_PIC_SetBitsDir( u8_t  PORTxx , u8_t bitx , u8_t bit_counuter , u8_t dir){
int i ; for (i=0 ; i<bit_counuter;i++){MCAL_PIC_SetBitDir(PORTxx,bitx,dir); bitx++;}return ;}
void MCAL_PIC_SetPORTDir(u8_t  PORTxx ,u8_t dir){
	GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);
	if (dir==INPUT){*(gpio->TRISX)=PORT_IN;}
			else {*(gpio->TRISX)=PORT_OUT;}
}
void MCAL_PIC_SetBitVal( u8_t  PORTxx , u8_t bitx , u8_t val){
	GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);
    if (val==0){set_bit(*(gpio->LATX),bitx);}
    else {clr_bit(*(gpio->LATX),bitx);}
return;}
void MCAL_PIC_SetBitSVal( u8_t  PORTxx , u8_t bitx , u8_t val,u8_t bit_counuter){
    GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);
	if (val==0){set_bits(*(gpio->LATX),bitx,val);}
	else if(val==1) {clr_bits(*(gpio->LATX),bitx,val);}
}
void MCAL_PIC_SetPORTVal( u8_t  PORTxx , u8_t val ){
GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);	*(gpio->LATX)=val; return;}

u8_t MCAL_PIC_GetBitVal ( u8_t  PORTxx , u8_t bitx){
GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);
return get_bit(*(gpio->PORTX),bitx);}
u8_t MCAL_PIC_GetPINVal( u8_t  PORTxx ){
    GPIOXX* gpio=MCAL_PIC_getgpio(PORTxx);return *(gpio->PORTX);
    }

