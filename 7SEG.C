#include "DIO.h"
#include "timer.h"
#include "Controls.h"
#define 7SEG_En1 2
#define 7SEG_En2 3
#define 7SEG_En3 4
#define 7SEG_En4 5
#define seg0 0b11000000 //192
#define seg1 0b11111001 //249
#define seg2 0b10100100 //164
#define seg3 0b10110000
#define seg4 0b10011001
#define seg5 0b10010010
#define seg6 0b10000010
#define seg7 0b11111000
#define seg8 0b10000000
#define seg9 0b10010000
/*
RD0 Segmento A
RD1 Segmento B
RD2 Segmento C
RD3 Segmento D
RD4 Segmento E
RD5 Segmento F
RD6 Segmento G
RD7 Segmento Ponto
RA2 Seleção do Display1 (Disp1)
RA3 Seleção do Display2 (Disp2)
RA4 Seleção do Display3 (Disp3)
RA5 Seleção do Display4 (Disp4)
Void 7SEG_init (u8_t pin)
Description: initializes the 7SEG with 00:00 on start up
Input Value: selected pin mode which is port D from the simulator
Return Value: void
*/
static u8_t values[4];
const u8_t _7SEG[10]={0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};

}
void 7SEG_init (u8_t pin){


return;}

/*
u8_t 7SEG_change_time (u8_t ktime)
Description: shows the inputed time setting & then change time count value
Input Value: inputed time as integer value
Return Value: current time (optional) or void

*/
void 7SEG_SetValues(u8_t t){
values[3]=t/1000;
values[2]=(t-values[3]*1000)/100 ;
values[1]=(t-values[3]*1000-values[2]*100)/10;
values[0]=t-values[3]*1000-values[2]*100- values[1]*10 ;
return;}
void 7SEG_toogle (u8_t id){
u8_t i;
//shut down all 7Segs first
for (i=0 ; i<4 ; i++){
 MPIC_SetBitDir(7SEG_EnPort,i+2,OUTPUT);
 MPIC_SetBitVal(7SEG_EnPort,i+2,0);}
MPIC_SetBitDir(7SEG_EnPort,id+2,OUTPUT);
MPIC_SetBitVal(7SEG_EnPort,id+2,1);
MPIC_SetPORTDir(7SEG_Port,OUTPUT);
MPIC_SetPORTVal(7SEG_Port,_7SEG[values[id]]);
return;}

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
