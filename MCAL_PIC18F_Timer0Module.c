#include "MCAL_PIC18F.h"
#include <pic16/pic18f452.h>
#include <stdio.h>
#include <math.h>

 u8_t global_prescaler;
void MCAL_PIC_InitTimer0(u8_t mode,u16_t prescaler){
SysTime.ticks=1;SysTime.milliseconds=0; SysTime.seconds=0; SysTime.minutes=0; //defaults value assigned
TMR0H = 0;           TMR0L = 0; //resetting
T0CONbits.TMR0ON=1; //enable
switch(mode){
case bit8_OV:
    T0CONbits.T08BIT=1; //8bit operation
    T0CONbits.T0CS=0; //same processor clock
    T0CONbits.T0SE=0; //MORE ACCURATE on low - to high trans
    T0CONbits.PSA=0; //prescaler assgined
    INTCON1bits.TMR0IF=0;  //flag cleared before enabling intp
    INTCON1bits.TMR0IE=1; //ENABLE INTERRUPT
    MCAL_PIC_Timer0SetPS(prescaler);
    break;
case sys_clk:
    T0CONbits.T08BIT=1; //8bit operation
    T0CONbits.T0CS=0; //same processor clock
    T0CONbits.T0SE=0; //MORE ACCURATE on low - to high trans
    T0CONbits.PSA=0; //prescaler assgined
    INTCON1bits.TMR0IF=0;  //flag cleared before enabling intp
    INTCON1bits.TMR0IE=1; //ENABLE INTERRUPT
    MCAL_PIC_Timer0SetPS(256); //based on 8 MHZ freq every 8 ticks generates 1 MS
    MCAL_PIC_Timer0_GetTick();
    MCAL_PIC_Timer0OVredirect(MCAL_PIC_Timer0SysClkHandler); //setting interrupt call back
    MCAL_PIC_SysClkredirect(MCAL_PIC_SysClkDef); //default
    break;
default:    break;}

return;}
void MCAL_PIC_Timer0SetPS(u16_t prescaler){
global_prescaler=prescaler;
switch(prescaler){
case 256:
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS2=1;
    break;
case 128:
    T0CONbits.T0PS0=0;
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS2=1;
    break;
case 64:
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    break;
case 32:
    T0CONbits.T0PS0=0;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    break;
case 16:
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS2=0;
    break;
case 8:
    T0CONbits.T0PS0=0;
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS2=0;
    break;
case 4:
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=0;
    break;
case 2:
    T0CONbits.T0PS0=0;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=0;
    break;
default:
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS2=1;}
return;}
void MCAL_PIC_Timer0_GetTick(void){
u32_t freq=0 ;
if(get_bit(OSCCON,6)){freq+=1;}
if(get_bit(OSCCON,5)){freq+=3;}
if(get_bit(OSCCON,4)){freq+=5;}
switch(freq){
    case 9:freq=8*1000;SysTime.ticks=8; break;
    case 4:freq=4*1000;SysTime.ticks=4;break;
    case 6:freq=2*1000;SysTime.ticks=2;break;
    case 1:freq=1*1000;SysTime.ticks=1;break;
    case 8:freq=500*1;SysTime.ticks=0.5;break;
    case 3:freq=250*1;SysTime.ticks=0.25;break;
    case 5:freq=125*1;SysTime.ticks=0.125;break;
    case 0:freq=31*1;SysTime.ticks=0.031;break;
}
if (SysTime.ticks<1){ //error -0.064
    global_prescaler=(u16_t)ceilf(((float)global_prescaler)*SysTime.ticks );
    MCAL_PIC_Timer0SetPS(global_prescaler);
    SysTime.ticks=1; //corrseponds to 1 ms tick
}
if (SysTime.ticks>1){ //error -0.064
global_prescaler=(u16_t)ceilf(((float)global_prescaler)/SysTime.ticks );
    MCAL_PIC_Timer0SetPS(global_prescaler);
    SysTime.ticks=1; //corrseponds to 1 ms tick
}
return;}
void MCAL_PIC_Timer0SysClkHandler(void){
if (SysTime.ticks==1){
    if(SysTime.milliseconds==999){
        if(SysTime.seconds==59){SysTime.minutes++;SysTime.seconds=0;}
        else {SysTime.seconds++;}
        SysTime.milliseconds=0;}
    else { SysTime.milliseconds++;}
    MCAL_PIC_SysClkHandler();} //provides further functionality to the user
}
void MCAL_PIC_Timer0_SetCM(u8_t OVT0){
TMR0=OVT0 ;
return;}
Time* MCAL_PIC_GetTime(void){return &SysTime;}
void MCAL_PIC_ResetTime(void){SysTime.milliseconds=0;SysTime.seconds=0;SysTime.minutes=0;}

/*function to set call back for desired function to happen in every case of timer-related interrupts
OUTPUTS: NONE
INPUTS: Signal ID,pointer to the desired function
SIGNALS: OVERFLOW ,COMPARE MATCH
NOTES: */
void MCAL_PIC_SysClkredirect(void (*ptr) (void)){MCAL_PIC_SysClkHandler=ptr;}
void MCAL_PIC_SysClkDef(void){return;}
