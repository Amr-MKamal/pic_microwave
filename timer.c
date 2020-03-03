#include "DIO.h"
#include <stdio.h>
#include <math.h>
struct time{
double ticks;
u16_t milliseconds;
u8_t seconds;
u32_t minutes;
};
typedef struct time Time;
#define MTIMERS_H_
#define 8bit_OV 0
#define sys_clk 1
#define CTC 1
#define FASTPWM 2
#define PWM 3
#define TIMER0 0
#define TIMER1 1
#define TIMER2 2
#define en_us 0
#define en_ms 1
#define en_s  2
#define CTC_OCDIS 0
#define CTC_TOCM  1
#define CTC_SOCM  2
#define CTC_COCM  3
Time SysTime; u8_t global_prescaler;
void MCAL_PIC_InitTimer0(u8_t mode,u16_t prescaler){
SysTime.ticks=1;SysTime.milliseconds=0; SysTime.seconds=0; SysTime.minutes=0;
TMR0H = 0;           TMR0L = 0; //resetting
T0CONbits.TMR0ON=1; //enable
switch(mode){
case 8bit_OV:
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
    MCAL_PIC_Timer0SetPS(256);
    MCAL_PIC_Timer0SetOV(255);  //based on 8 MHZ freq every 8 ticks generates 1 MS
    MCAL_PIC_Timer0_GetTick();
    MCAL_PIC_Timer0OVISRCB(MCAL_PIC_Timer0IntpSysClk); //setting interrupt call back
    break;
case default:
    break;}
//register TMR0

return;}
void (* MCAL_PIC_Timer0OVDefINTP) (void);
void MCAL_PIC_Timer0_SetOV(u8_t OVT0){
TMR0=OVT0 ;
return;}
void MCAL_PIC_Timer0SetPS(u16_t prescaler){
global_prescaler=prescaler
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
case default:
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS2=1;
    break;}
return;}
void MCAL_PIC_Timer0_GetTick(void){
u32_t freq=0 ;
if(get_bit(OSCCON,6)){freq+=1;}
if(get_bit(OSCCON,5)){freq+=3;}
if(get_bit(OSCCON,4)){freq+=5;}
switch(freq){
    case 9:freq=8*1000000;SysTime.ticks=8; break;
    case 4:freq=4*1000000;SysTime.ticks=4;break;
    case 6:freq=2*1000000;SysTime.ticks=2;break;
    case 1:freq=1*1000000;SysTime.ticks=1;break;
    case 8:freq=500*1000;SysTime.ticks=0.5;break;
    case 3:freq=250*1000;SysTime.ticks=0.25;break;
    case 5:freq=125*1000;SysTime.ticks=0.125;break;
    case 0:freq=31*1000;SysTime.ticks=0.031;break;
}
if (SysTime.ticks<1){ //error -0.064
(u16_t)global_prescaler=ceilf(((float)global_prescaler)*SysTime.ticks );
    void MCAL_PIC_Timer0SetPS(global_prescaler);
    SysTime.ticks=1; //corrseponds to 1 ms tick
}
if (SysTime.ticks>1){ //error -0.064
(u16_t)global_prescaler=ceilf(((float)global_prescaler)/SysTime.ticks );
    void MCAL_PIC_Timer0SetPS(global_prescaler);
    SysTime.ticks=1; //corrseponds to 1 ms tick
}
return;}
void MCAL_PIC_Timer0IntpSysClk(void){
if (SysTime.ticks==1){
    if(SysTime.milliseconds==999){
        if(SysTime.seconds==59){SysTime.minutes++;SysTime.seconds=0}
        else {SysTime.seconds++;}
        SysTime.milliseconds=0;}
    else { SysTime.milliseconds++;}}

}
void  MCAL_PIC_Timer0OVISRCB(void (*P) (void)){
MCAL_PIC_Timer0OVDefINTP=P;return;}


/*function to set call back for desired function to happen in every case of timer-related interrupts
OUTPUTS: NONE
INPUTS: Signal ID,pointer to the desired function
SIGNALS: OVERFLOW ,COMPARE MATCH
NOTES: */
void Set_PWMDUTY(u8_t MTimer_ID ,u8_t duty_cycle){
	switch(MTimer_ID){
	case TIMER0: OCR0=(u8_t)(duty_cycle*2.55);
	break;
	}
}


