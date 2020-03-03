
#include "Controls.h"
#include "DIO.h"
#include "timer.h"
#define columnPort PORTb
#define rowPort PORTd
#define COL_INIT   0
#define COL_FIN    3
#define ROW_INIT   0
#define ROW_FIN    4
#define NOT_PRESSED 0x0C

/*           Col_2   Col_1   Col_0     */
/*	                                          */
/* row_0      1       2       3      */
/*	                                          */
/* row_1      4       5       6      */
/*	                                          */
/* row_2	  7      8        9     */
/*	                                          */
/* row_3     weight    0      start     */

const u8_t Keypad_Values[3][4] =
{{0x01,0x04,0x07,},
 {0x02,0x05,0x08,},
 {0x03,0x06,0x09,},
 {0x0A,0x00,0x0B,}};
/*
Void Keypad_init (u8_t pin)
Description: initializes the keypad ports and pins on start up or any read since the pins is multiplexed with 7SEG
Input Value: void
Return Value: void
*/
void Keypad_init (void){
MPIC_SetBitsDir(columnPort,0,3,OUTPUT);
MPIC_SetBitSVal(columnPort,0,High,3);
MPIC_SetBitsDir(rowPort,0,4,INPUT);
MPIC_SetBitSVal(rowPort,0,High,4);
return;}

/* Description: Interface to get the ID of the pressed key, return 12 no key
is pressed, this function doesn't handle if 2 keys are
pressed at the same time
Input Value: Nothing
Return Value: pressed key as hexadecimal
*/
u8_t Keypad_read (void){
  u8_t Column ,Row;
  u8_t current_press = 0x0C;
  /* Looping on columns of the Key Pad                                                                               */
  Keypad_init(); //only because port D is multiplexed on picgenuis
  for (Column = 0+COL_INIT ;Column <COL_FIN; Column++){
    MPIC_SetBitVal(KeyPort,Column,0);
    for (Row = 0+ROW_INIT;Row <ROW_FIN;Row++){
      /* Check the status of the switch                                                                              */
      if (!MPIC_GetBitVal(KeyPort,Row)){
       current_press= Keypad_Values[Column-COL_INIT][Row-ROW_INIT];
        /* Wait until the switch is released (Single Press)                                                          */
        while (!Dio_u8GetPinValue(PORT, LOC_u8Row))
          ;
        /* Delay to avoid bouncing                                                                                   */
        wait_delay_ms(1);}}
    /* Deactivate the Column                                                                                         */
    MPIC_SetBitVal(KeyPort,Column,1);}
  return current_press;
}



