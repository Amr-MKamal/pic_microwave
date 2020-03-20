#include <pic16/delay.h>
#include "Controls.h"
#include "HAL_PicGenios.h"

/*
u8_t Cont_read_keypad(void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
u8_t SEG_Isinit ,Keypad_Isinit;
void Cont_Init (void){
        Cont_SEGInit();
        MCAL_PIC_EnINTPx(RB6,OnChange);
        MCAL_PIC_EnINTPx(RB5,OnChange);
        MCAL_PIC_InitTimer0(sys_clk,256);
        MCAL_PIC_SetBitDir(MotorPort,MOTORPin,OUTPUT);
        MCAL_PIC_SetBitDir(LampPort,LampPin,OUTPUT);
        MCAL_PIC_SetBitDir(HeaterPort,HeaterPin,OUTPUT);

}

void Cont_Flash_SEG(u8_t*  _tim_,u8_t cnt){
    if(!SEG_Isinit){Cont_SEGInit();}
    SEG_SetValues(_tim_);
    SEG_toogle(1);delay1ktcy(5);
    SEG_toogle(2);delay1ktcy(5);
    SEG_toogle(3);delay1ktcy(5);
    SEG_toogle(4);delay1ktcy(5);
return;}
u8_t Cont_read_keypad(u8_t* Keypad_counter){
u8_t temp_read;
if(!Keypad_Isinit){ Keypad_init();Keypad_Isinit=1;SEG_Isinit=0;}
temp_read=Keypad_read();
    if(temp_read==NOT_PRESSED){return No_Read;}
    else if(temp_read!=StartPressed) {if(temp_read!=WeightPressed){(*Keypad_counter)++;}}
    return temp_read;} //wrapping

void Cont_SEGInit(void){
        SEG_init(SEG_Port,SEG_EnPort,SEG01_En);
        SEG_init(SEG_Port,SEG_EnPort,SEG02_En);
        SEG_init(SEG_Port,SEG_EnPort,SEG03_En);
        SEG_init(SEG_Port,SEG_EnPort,SEG04_En);
        SEG_Isinit=1;Keypad_Isinit=0;
return;}
void Cont_Motor(u8_t mode){
switch (mode){
case ON:
    MCAL_PIC_SetBitVal(MotorPort,MOTORPin,1);
    break;
case OFF:
    MCAL_PIC_SetBitVal(MotorPort,MOTORPin,0);
    break;}
}


void Cont_Lamp(u8_t mode){
switch (mode){
case ON:
    MCAL_PIC_SetBitVal(LampPort,LampPin,1);
    break;
case OFF:
    MCAL_PIC_SetBitVal(LampPort,LampPin,0);
    break;}
return;}
/*
u8_t Cont_Heater(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
void Cont_Heater(u8_t mode){
switch (mode){
case ON:
    MCAL_PIC_SetBitVal(HeaterPort,HeaterPin,1);
    break;
case OFF:
    MCAL_PIC_SetBitVal(HeaterPort,HeaterPin,0);
    break;}
}
