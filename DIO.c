#include "stdtypes.h"
#include <pic16/pic18f452.h>



typedef struct GPIOX {
	volatile u8_t* PORTX;
	volatile u8_t* TRISX;
	volatile u8_t* LATX;
};typedef struct GPIOX GPIOXX;

enum _Mode {OnChange,Ris_edge,Fal_edge};
void MPIC_INTP_En (u8_t id, u8_t source ,u8_t Mode){
//maybe a var list
if(id==PORTb){MPIC_EnINTPx(source,Mode)}
else {
switch (id){
case OnChange:
 break;
case Ris_edge:
    break; } }
return;}
void MPIC_EnINTPx(u8_t source , u8_t mode){
INTCON2bits.RBPU=0; //enable pull-up on portb
LATB=0XFF; //pulling high
INTCONbits.PEIE = 1;
switch (mode){
case OnChange:
    MPIC_SetBitDir(PORTb,source,INPUT);
    INTCONbits.RBIE=1; //enables port change interrupt
    INTCON2bits.RBIP=1; //high priority bit
    INTCONbits.RBIF=0;
    MPIC_EnGINTP();
    break;
case default:
     MPIC_SetBitDir(id,source,INPUT);
     switch(source){
        case 0:
            INTCONbits.INT0IE=1;
            INTCONbits.INT0IF=0;
            if(mode==Ris_edge){INTCON2bits.INTEDG0=1;}
                    else{INTCON2bits.INTEDG0=0;}
            break;
        case 1:
            INTCON3bits.INT1IE=1;
            INTCON3bits.INT1IF=0;
            if(mode==Ris_edge){INTCON2bits.INTEDG1=1;}
                    else{INTCON2bits.INTEDG1=0;}
            break;
        case 2:
            INTCON3bits.INT2IE=1;
            INTCON3bits.INT2IF=0;
            if(mode==Ris_edge){INTCON2bits.INTEDG2=1;}
                    else{INTCON2bits.INTEDG2=0;}
            break;}
     MPIC_EnGINTP();break;}

return;}

void MPIC_EnGINTP(void) {INTCONbits.GIE = 1;} //enables general interrupt
void MPIC_DisGINT(void){ INTCONbits.GIE = 0;}
void MPIC_DisINT(u8_t INT){

}
/*ISR Masking to use certain funcitions for different situation
intialize a pointer to a function that takes void and return void, like this [void (*DefINT (void);] then intialize a function to control what the previous
function will be directed [void AVR_DefINTCALLBACK(void (*ptr) (void)){{DefINT=ptr;return;}}] , Example :void Vsys_clk(void), AVRredirect_DefINT( Vsys_clk ) DefInt(); DefInt will
now execute vsys_clock*/

void PICredirect_INTP_0(void (*ptr) (void)){INTP_0=ptr; return;}
void PICredirect_INTP_1(void (*ptr) (void)){INTP_1=ptr; return;}
void PICredirect_INTP_2(void (*ptr) (void)){INTP_2=ptr; return;}
volatile GPIOXX* MPIC_getgpio(u8_t PORTxx){
	GPIOXX* GPIOx;
switch (PORTxx){
case PORTa :
	GPIOx->PORTX=(volatile u8_t *)(0x0F80);
	GPIOx->TRISX=(volatile u8_t *)(0x0F92);
	GPIOx->LATX=(volatile u8_t *)(0x0F89);
	break;return GPIOx;
case PORTb :
	GPIOx->PORTX=(volatile u8_t *)(0x0F81);
	GPIOx->TRISX=(volatile u8_t *)(0x0F93);
	GPIOx->LATX=(volatile u8_t *)(0x0F8A);
	break;return GPIOx;
case PORTc :
	GPIOx->PORTX=(volatile u8_t *)(0x0F82);
	GPIOx->TRISX=(volatile u8_t *)(0x0F94);
	GPIOx->LATX=(volatile u8_t *)(0x0F8B);
	break;return GPIOx;
case PORTd :
	GPIOx->PORTX=(volatile u8_t *)(0x0F83);
	GPIOx->TRISX=(volatile u8_t *)(0x0F95);
	GPIOx->LATX=(volatile u8_t *)(0x0F8C);
	break;return GPIOx;
case PORTe :
	GPIOx->PORTX=(volatile u8_t *)(0x0F84);
	GPIOx->TRISX=(volatile u8_t *)(0x0F96);
	GPIOx->LATX=(volatile u8_t *)(0x0F8D);
	break;return GPIOx;
default:
    return NULL;}

return 0;}
void MPIC_Init_Port(u8_t PORTxx){
if ((PORTxx==PORTd) || (PORTxx==PORTe)) {ADCON1=0xff;}
return;}
void MPIC_SetBitDir( u8_t  PORTxx , u8_t bitx , u8_t dir){
	GPIOXX* gpio=MPIC_getgpio(PORTxx);
	if (dir==INPUT){set_bit(*(gpio->TRISX),bitx);}
			else {clr_bit(*(gpio->TRISX),bitx);}
return;}
void MPIC_SetBitsDir( u8_t  PORTxx , u8_t bitx , u8_t bit_counuter , u8_t dir){
int i ; for (i=0 ; i<bit_counuter;i++){MAVR_SetBitDir(PORTxx,bitx,dir); bitx++;}return ;}
void MPIC_SetPORTDir(u8_t  PORTxx ,u8_t dir){
	GPIOXX* gpio=MPIC_getgpio(PORTxx);
	if (dir==INPUT){*(gpio->TRISX)=PORT_IN;}
			else {*(gpio->TRISX)=PORT_OUT;}
}
void MPIC_SetBitVal( u8_t  PORTxx , u8_t bitx , u8_t val){
	GPIOXX* gpio=MPIC_getgpio(PORTxx);
    if (val==0){set_bit(*(gpio->LATX),bitx);}
    else {clr_bit(*(gpio->LATX),bitx);}
return;}
void MPIC_SetBitSVal( u8_t  PORTxx , u8_t bitx , u8_t val,u8_t bit_counuter){
    GPIOXX* gpio=MPIC_getgpio(PORTxx);
	if (val==0){set_bits(*(gpio->LATX),bitx,val);}
	else if(val==1) {clr_bits(*(gpio->LATX),bitx,val);}
}
void MPIC_SetPORTVal( u8_t  PORTxx , u8_t val ){
GPIOXX* gpio=MPIC_getgpio(PORTxx);	*(gpio->LATX)=val; return;}

u8_t MPIC_GetBitVal ( u8_t  PORTxx , u8_t bitx){
GPIOXX* gpio=MPIC_getgpio(PORTxx);
return get_bit(*(gpio->PORTX),bitx);}
u8_t MPIC_GetPINVal( u8_t  PORTxx ){
    GPIOXX* gpio=MPIC_getgpio(PORTxx);return *(gpio->PORTX);
    }

