#include"MCAL_PIC18F.h"
#include <pic16/pic18f452.h>
#define INTPnot_recognised 0
#define INTP0xSig    2
#define INTP1xSig    3
#define INTP2xSig    4
#define INTPRBxSig   5
#define Timer0OVSig  9
#define Timer0CMSig  10

u8_t current_source=0;
 void (* MCAL_PIC_Timer0OVHandler)       (void);
 void (* MCAL_PIC_HighPriINTPHandler)    (void);
 void (* MCAL_PIC_LowPriINTPHandler)     (void);
 void (* MCAL_PIC_INTP0Handler)          (void);
 void (* MCAL_PIC_INTP1Handler)          (void);
 void (* MCAL_PIC_INTP2Handler)          (void);
 void (* MCAL_PIC_INTPRBHandler)         (void);
 void (* MCAL_PIC_SysClkHandler)         (void);
void MCAL_PIC_INTPEn (u8_t id, u8_t source ,enum _Mode Mode){

if(id==PORTb){MCAL_PIC_EnINTPx(source,Mode);}
else {
switch (Mode){
case OnChange:
 break;
case Ris_edge:
    break; } }
return;}
void MCAL_PIC_EnINTPx(u8_t source , enum _Mode mode){
INTCON2bits.RBPU=0; //enable pull-up on portb
LATB=0XFF; //pulling high
INTCONbits.PEIE = 1;
switch (mode){
case OnChange:
    MCAL_PIC_SetBitDir(PORTb,source,INPUT);
    INTCONbits.RBIE=1; //enables port change interrupt
    INTCON2bits.RBIP=1; //high priority bit
    INTCONbits.RBIF=0;
    MCAL_PIC_EnGINTP();
    break;
default:
     MCAL_PIC_SetBitDir(PORTb,source,INPUT);
     switch(source){
        case 0://INTx0
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
     MCAL_PIC_EnGINTP();}

return;}
void MCAL_PIC_EnGINTP(void) {INTCONbits.GIE = 1;} //enables general interrupt
void MCAL_PIC_DisGINT(void){ INTCONbits.GIE = 0;}
u8_t MCAL_PIC_GetINTSource(void){
    //check for all enabled interrupt sources for interrupt source
if( INTCONbits.INT0IF){return INTP0xSig;}
else if(INTCON3bits.INT1IF){return INTP1xSig;}
else if(INTCON3bits.INT2IF){return INTP2xSig;}
else if(INTCONbits.RBIF)   {return INTPRBxSig;}
else if(INTCON1bits.TMR0IF){return Timer0OVSig;}
else {return INTPnot_recognised;}}
void MCAL_PIC_IntpServe(u8_t source){
switch (source){
    case INTP0xSig: MCAL_PIC_INTP0Handler();break;
    case INTP1xSig: MCAL_PIC_INTP1Handler();break;
    case INTP2xSig: MCAL_PIC_INTP2Handler();break;
    case INTPRBxSig:MCAL_PIC_INTPRBHandler();break;
    case Timer0OVSig:  MCAL_PIC_Timer0OVHandler();break;
    case INTPnot_recognised:  break; //these cases for error handling should handle error by resetting
    default:;}

return;}
void MCAL_PIC_DirectHighISR(void){
if(INTCONbits.RBIF)        {MCAL_PIC_HighPriINTPHandler=MCAL_PIC_INTPRBHandler;    INTCONbits.RBIF=0;}
else if(INTCON1bits.TMR0IF){MCAL_PIC_HighPriINTPHandler=MCAL_PIC_Timer0OVHandler;  INTCON1bits.TMR0IF=0;}
else if(INTCONbits.INT0IF) {MCAL_PIC_HighPriINTPHandler=MCAL_PIC_INTP0Handler;     INTCONbits.INT0IF=0;}
else if(INTCON3bits.INT1IF){MCAL_PIC_HighPriINTPHandler=MCAL_PIC_INTP1Handler;     INTCON3bits.INT1IF=0;}
else if(INTCON3bits.INT2IF){MCAL_PIC_HighPriINTPHandler=MCAL_PIC_INTP2Handler;     INTCON3bits.INT2IF=0;}
return;}
void MCAL_PIC_INTP0redirect(void (*ptr) (void)){MCAL_PIC_INTP0Handler=ptr; return;}
void MCAL_PIC_INTP1redirect(void (*ptr) (void)){MCAL_PIC_INTP1Handler=ptr; return;}
void MCAL_PIC_INTP2redirect(void (*ptr) (void)){MCAL_PIC_INTP2Handler=ptr; return;}
void MCAL_PIC_INTPRBredirect(void (*ptr) (void)){MCAL_PIC_INTPRBHandler=ptr; return;}
void  MCAL_PIC_Timer0OVredirect(void (*P) (void)){MCAL_PIC_Timer0OVHandler=P;return;}
void  MCAL_PIC_DisINT(u8_t INTID){return;}
