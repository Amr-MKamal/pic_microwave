#include "HAL_PicGenios.h"
#include <pic16/delay.h>
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
 {0x0A,0x00,0x0B}};

void Keypad_init (void){
MCAL_PIC_SetBitsDir(columnPort,0,3,OUTPUT);
MCAL_PIC_SetBitSVal(columnPort,0,High,3);
MCAL_PIC_SetBitsDir(rowPort,0,4,INPUT);
MCAL_PIC_SetBitSVal(rowPort,0,High,4);
return;}

u8_t Keypad_read (void){
  u8_t Column ,Row;
  u8_t current_press = 0x0C;
  /* Looping on columns of the Key Pad                                                                               */
  Keypad_init(); //only because port D is multiplexed on picgenuis
  for (Column = 0+COL_INIT ;Column <COL_FIN; Column++){
    MCAL_PIC_SetBitVal(KeyPort,Column,0);
    for (Row = 0+ROW_INIT;Row <ROW_FIN;Row++){
      /* Check the status of the switch                                                                              */
      if (!MCAL_PIC_GetBitVal(KeyPort,Row)){
       current_press= Keypad_Values[Column-COL_INIT][Row-ROW_INIT];
        /* Wait until the switch is released (Single Press)                                                          */
        /* Delay to avoid bouncing                                                                                   */
        delay1ktcy(5);}}
    /* Deactivate the Column                                                                                         */
    MCAL_PIC_SetBitVal(KeyPort,Column,1);}
  return current_press;
}



