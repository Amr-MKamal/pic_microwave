#ifndef HAL_PICGENIOS_H_INCLUDED
#define HAL_PICGENIOS_H_INCLUDED
#include "MCAL_PIC18F.h"
#include "stdtypes.h"
#define ON 1
#define OFF 0
#define No_Read 11
#define KeyPort PORTb
#define SEG_Port PORTd //all port
#define SEG_EnPort PORTa //RA2 ..5
#define SEG01_En  3  //RA2 ..5
#define SEG02_En  4 //RA2 ..5
#define SEG03_En  5 //RA2 ..5
#define SEG04_En  7 //RA2 ..5
#define RB6 6
#define RB5 5
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
#define columnPort PORTb
#define rowPort PORTd
#define COL_INIT   0
#define COL_FIN    3
#define ROW_INIT   0
#define ROW_FIN    4
#define NOT_PRESSED 0x0C
#define StartPressed   0x0B
#define WeightPressed  0x0A

void Cont_Init (void);
void Cont_Flash_SEG(u8_t* _tim_,u8_t cnt);
u8_t Cont_read_keypad(u8_t* Keypad_counter);
void Cont_SEGInit(void);
void Cont_Motor(u8_t mode);
void Cont_Lamp(u8_t mode);
/*u8_t Cont_Heater(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void*/
void Cont_Heater(u8_t mode);
/*Description: initializes the keypad ports and pins on start up or any read since the pins is multiplexed with 7SEG
Input Value: void
Return Value: void*/
void Keypad_init (void);
/* Description: Interface to get the ID of the pressed key, return 12 no key
is pressed, this function doesn't handle if 2 keys are
pressed at the same time
Input Value: Nothing
Return Value: pressed key as hexadecimal*/
u8_t Keypad_read (void);
/*Description: initializes the SEG with 00:00 on start up
Input Value: selected pin mode which is port D from the simulator
Return Value: void*/
void SEG_init (u8_t pin ,u8_t contport ,u8_t contpin);
/*u8_t SEG_change_time (u8_t ktime)
Description: shows the inputed time setting & then change time count value
Input Value: inputed time as integer value
Return Value: current time (optional) or void*/
void SEG_GetValues(u8_t t);
void SEG_SetValues(u8_t* t);
void SEG_toogle (u8_t id);
void SEG_ToogleVal (u8_t id ,u8_t val);

#endif // HAL_PICGENIOS_H_INCLUDED
