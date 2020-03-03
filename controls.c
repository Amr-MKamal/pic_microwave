#include "Controls.h"
#include "DIO.h"
#define ON 1
#define OFF 0
#define No_Read 11
#define 7SEG_Port PORTd //all port
#define 7SEG_EnPort PORTa //RA2 ..5
#define columnPort PORTb // RB0..2
#define rowPort PORTd //RD0..3
#define DoorPort PORTb
#define DoorPin 6
#define CancelButPort PORTb
#define CancelPin 5
#define MotorPort PORTc
#define MOTORPin 2
#define LampPort PORTb
#define LampPin 3
#define HeaterPort PORTb
#define HeaterPin 4




void Cont_Init (void){
        7SEG_init(0); //0 for default port
        Keypad_init(0);
}
/*
u8_t Cont_read_keypad(void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
void Cont_Flash_7SEG(void){
}
u8_t Cont_read_keypad(u8_t* Keypad_counter){
u8_t temp_read;
temp_read=Keypad_read();
if(*Keypad_counter==0){
    if(temp_read==NOT_PRESSED){
        *Keypad_counter=0
        return No_Read;}
    else {*Keypad_counter++}}
    return temp_read;
} //wrapping
u8_t Cont_read_startbutton(void){
}
/*

Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
u8_t Cont_read_door(void){ return MPIC_GetBitVal(DoorPORT,DoorPin);}
/*
u8_t Cont_read_cancelbut(void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
u8_t Cont_read_weight(void){return MPIC_GetBitVal(WeightPORT,WeightPin);}
/*
u8_t Cont_motor(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
void Cont_Motor(u8_t mode){
switch (mode){
case ON:
    MPIC_SetBitVal(MotorPort,MOTORPin,1);
    break;
case OFF:
    MPIC_SetBitVal(MotorPort,MOTORPin,0);
    break;}
}

/*
u8_t Cont_Lamp(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
void Cont_Lamp(u8_t mode){
switch (mode){
case ON:
    MPIC_SetBitVal(LampPort,LampPin,1);
    break;
case OFF:
    MPIC_SetBitVal(LampPort,LampPin,0);
    break;}
}
/*
u8_t Cont_Heater(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
void Cont_Heater(u8_t mode){
switch (mode){
case ON:
    MPIC_SetBitVal(HeaterPort,HeaterPin,1);
    break;
case OFF:
    MPIC_SetBitVal(HeaterPort,HeaterPin,0);
    break;}
}
