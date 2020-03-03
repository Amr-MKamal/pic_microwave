#ifndef CONTROLS_H_INCLUDED
#define CONTROLS_H_INCLUDED
//keypad to enter time
//fan as a motor
//puch buttons to start
// (default 30 seconds from weight sensor & door closed)
//motor & Lamp & heater & time decrease
//cancel button
// (interrupt,cancel heating or time)
//weight sensor as puch button
//empty pin as heater
//7Seg Display to show time
//sensors
//naming u8 MOD_GetValue(...)


#endif // CONTROLS_H_INCLUDED

/*
u8_t Cont_read_keypad(void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/

/*
u8_t Cont_read_startbut(void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
/*
u8_t Cont_read_cancelbut(void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
/*
u8_t Cont_motor(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/

/*
u8_t Cont_Lamp(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
/*
u8_t Cont_Heater(u8_t mode)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
/*
Void 7SEG_init (u8_t pin)
Description: initializes the 7SEG with 00:00 on start up
Input Value: selected pin mode
Return Value: void
*/
/*
u8_t 7SEG_change_time (u8_t ktime)
Description: shows the inputed time setting & then change time count value
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
/*
u8_t 7SEG_start_count (void)
Description: gives signal to the timer to start decreasing
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
/*
void 7SEG_cancel(void)
Description: shows 00:00
Input Value: void
Return Value: void

*/
