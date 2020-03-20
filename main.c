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

#include"HAL_PicGenios.h"
#include "MCAL_PIC18F.h"
#define DoorOpen 0
#define DoorClossed 1
#define FoodIn 1
#define empty  0
#define working 1
void PCancel(void);
enum State{Unintialized,Intialized,Time_Setting,Working,Finished,Cancel};
u8_t current_interrupt_source ;
enum State Cur_State=Unintialized;
Time start_time,remaining_time,end_time;
u8_t Door_Status, Weight_Status ,Temp_Input,Start_status, Keypad_counter=0;
u8_t Time_Input[4]={0};

void main(void)
{

    //intialize SEG
    // read door & weight status & start & cancel & keypad status in a loop or state machine WHERE EVERY STATE IS A loOP
    while(1){
        switch(Cur_State){
    case Unintialized:
        MCAL_PIC_DisGINT();
        Cont_Init();
        MCAL_PIC_INTPRBredirect(PCancel);//implement cancel functionallity as interrupt handler
        Door_Status=DoorClossed;
        Weight_Status=empty;
        Start_status=0;
        Cur_State=Intialized;
        break;
    case Intialized:
            Temp_Input=Cont_read_keypad(&Keypad_counter);
            if(Temp_Input==WeightPressed){
                    if(Weight_Status){Weight_Status=empty;}
                    else           {Weight_Status=FoodIn;}}
            else if(Temp_Input!=No_Read){
            Time_Input[0]=Temp_Input;
            Cur_State=Time_Setting;
            MCAL_PIC_EnGINTP();}
            Cont_Flash_SEG(Time_Input,4);
        break;
    case Time_Setting:
            Temp_Input=Cont_read_keypad(&Keypad_counter);
            if(Temp_Input==StartPressed){
                    if(!Start_status){Start_status=working;}}
            else if(Temp_Input==WeightPressed){
                    if(Weight_Status){Weight_Status=empty;}
                    else           {Weight_Status=FoodIn;}}
            else if(Temp_Input!=No_Read){
                if(Keypad_counter==4){Keypad_counter=3;}
                Time_Input[Keypad_counter]=Temp_Input;
                Cur_State=Time_Setting;

 }
            if (Start_status){
                if(Weight_Status){
                    if(Door_Status){
                        Cur_State=working;
                        //start lamp //start heater //start motor
                        Cont_Flash_SEG(Time_Input,4);
                        Cont_Motor(ON);
                        Cont_Lamp(ON);
                        Cont_Heater(ON);
                        start_time.milliseconds=SysTime.milliseconds;start_time.seconds=SysTime.seconds;start_time.minutes=SysTime.minutes;
                        end_time.minutes=start_time.minutes+Time_Input[0]*10+Time_Input[1];
                        end_time.seconds=start_time.seconds+Time_Input[2]*10+Time_Input[3];
                        end_time.milliseconds=start_time.milliseconds;
                    }}}
        //start to go to working , cancel to go to intialize

        break;
    case Working:
        remaining_time.minutes=end_time.minutes-SysTime.minutes; //time update
        remaining_time.seconds=end_time.seconds-SysTime.seconds;
        remaining_time.milliseconds=end_time.milliseconds-SysTime.milliseconds;
        if(remaining_time.minutes==0){
            if(remaining_time.seconds==0){
                if(remaining_time.milliseconds==0){
                   Cur_State=Finished; }} }
        Time_Input[0]=(u8_t)(remaining_time.minutes/10);
        Time_Input[1]=Time_Input[0]*10-(u8_t)remaining_time.minutes;
        Time_Input[2]=(u8_t)remaining_time.seconds/10;
        Time_Input[3]=Time_Input[2]*10-(u8_t)remaining_time.seconds;
        Cont_Flash_SEG(Time_Input,4);
        Cont_Motor(ON);
        Cont_Lamp(ON);
        Cont_Heater(ON);
        break;
    case Finished:
        Cont_Motor(OFF);
        Cont_Lamp(OFF);
        Cont_Heater(OFF);
        Time_Input[0]=0;
        Time_Input[1]=0;
        Time_Input[2]=0;
        Time_Input[3]=0;
        Cont_Flash_SEG(Time_Input,4);
        Cur_State=Intialized;
        Start_status=0;
        break;
    case Cancel:Cur_State=Finished;break;}
        }

}

void PCancel(void){
if(Door_Status){
        Door_Status=DoorOpen;
        Cur_State=Cancel;}
else{Door_Status=DoorClossed;}
return;}

#pragma code isr=0x08
#pragma interrupt isr

void    isr(void){// serve interrupt source
MCAL_PIC_DirectHighISR(); // get interrupt source & assign HighPriINTPHandler pointer to it's handler function
MCAL_PIC_DisGINT();
MCAL_PIC_HighPriINTPHandler();
MCAL_PIC_EnGINTP();}
#pragma code
