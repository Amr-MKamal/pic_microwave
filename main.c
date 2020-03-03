/*
 */
/*
External interrupts on the RB0/INT0, RB1/INT1 and
RB2/INT2 pins are edge-triggered. If the corresponding
INTEDGx bit in the INTCON2 register is set (= 1), the
interrupt is triggered by a rising edge; if the bit is clear,
the trigger is on the falling edge. When a valid edge
appears on the RBx/INTx pin, the corresponding flag
bit, INTxIF, is set. This interrupt can be disabled by
clearing the corresponding enable bit, INTxIE. Flag bit,
INTxIF, must be cleared in software in the Interrupt
Service Routine before re-enabling the interrupt.
All external interrupts (INT0, INT1 and INT2) can wake
//keypad on portA , buttons & leds on poartB
//read from port picgenios
*/

#include "Controls.h"
enum State{Unintialized,Intialized,Time_Setting,Working,Finished,Cancel};
int main(void)
{
u8_t Cur_State=Unintialized;
u8_t Door_Status, Weight_Status ,Temp_Input, Keypad_counter=0;
u8_t Time_Input[4];

    //intialize 7SEG
    // read door & weight status & start & cancel & keypad status in a loop or state machine WHERE EVERY STATE IS A loOP
    while(1){
        switch(Cur_State){
    case Unintialized:
        MPIC_DisGINT();
        Cont_Init();
        Cur_State=intialized;
        break;
    case Intialized:
            // read door & weight status & keypad status in a loop or state machine
            Door_Status=Cont_read_door();
            Weight_Status=Cont_read_weight();
            temp_Input=Cont_read_keypad(Keypad_counter);
            if(Temp_Input!=No_Read){
            Time_Input[0]=Temp_Input;
            Cur_State=Time_Setting;
            MPIC_EnGINTP();
            INTP_En(Cancel);}
            Cont_Flash_7SEG();
            // start & cancel should be inturrputs
            //this seduo..


        break;
    case Time_Setting:
        //read Start & Cancel
        //start to go to working , cancel to go to intialize


          INTP_En(door);
        break;
    case Working:
        //start Lamp & heater & motor
        //start count down
        break;
    case Finished:
        //reset counters
        //goto intialized
        break;
    case Cancel:
        //acknolodge interuupt
        //goto finished
        break;}
        }

    return 0;
}
void interrupt isr()
{
	_asm
		GOTO chk_isr
	_endasm
}
void interrupt My_ISR_High(void);
void interrupt low_priority My_ISR_Low(void); //try these first
