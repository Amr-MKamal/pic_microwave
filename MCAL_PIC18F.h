
#ifndef MCAL_PIC18F_H_
#define MCAL_PIC18F_H_
#include "stdtypes.h"
#include <pic16/pic18f452.h>
#define ris_edge 	0
#define fal_edge 	1
#define log_change	2
#define low_lev		3
#define INT0		6
#define INT1		7
#define INT2		5
#define PORTa 0
#define PORTb 1
#define PORTc 2
#define PORTd 3
#define PORTe 4
#define DDRa 10
#define DDRb 11
#define DDRc 12
#define DDRd 13
#define PINa 20
#define PINb 21
#define PINc 22
#define PINd 23
#define INPUT 0
#define OUTPUT 1
#define INPUT_FLOAT 2
#define PORT_OUT 0xff
#define PORT_IN 0x00
#define High 1
#define Low 0
#define M_delay_s(var) _delay_ms(1000*var)
#define M_delay_ms(var) _delay_ms(var)
#define M_delay_us(var) _delay_us(var)
#define bit8_OV 0
#define sys_clk 1
#define TIMER0 0

/* ===============DIO.C Functions ===================================*/

/*Description: a structure for the PIC18F related port registers
Elements : volatile unsigned 8bit char pointer PORTX contains real address for PORTx that is used for reading the port (INPUT)
           volatile unsigned 8bit char pointer TRISX contains real address for data direction register that is used to determine port config (INPUT or OUPUT)
           volatile unsigned 8bit char pointer LATX contains real address for PORTx latch(output) register for writing the port (OUPUT)
 */
typedef struct GPIOX {
	volatile u8_t* PORTX;
	volatile u8_t* TRISX;
	volatile u8_t* LATX;
};typedef struct GPIOX GPIOXX;

/*Description: resolves dummy port names to an actual address for further control
Input Value: unsigned 8bit char for the predefined dummy port names
Return Value:a volatile pointer to structure of type GPIO  */
volatile GPIOXX* MCAL_PIC_getgpio(u8_t PORTxx);
/*Description: sets a PINx (bitx) in PORTx as INPUT/OUTPUT (dir)
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for bitx location ,
             unsigned 8bit char for direction (0 or 1)
Return Value:void */
void MCAL_PIC_SetBitDir( u8_t  PORTxx , u8_t bitx , u8_t dir);
/*Description: sets a PINx (bitx)s in PORTx as INPUT/OUTPUT (dir)
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for bitx start location ,
             unsigned 8bit char for number of bits starting bitx location ,
             unsigned 8bit char for direction (0 or 1)
Return Value:void */
void MCAL_PIC_SetBitsDir( u8_t  PORTxx , u8_t bitx , u8_t bit_counuter , u8_t dir);
/*Description: sets PORTx as INPUT/OUTPUT (dir)
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for direction (0 or 1)
Return Value:void */
void MCAL_PIC_SetPORTDir(u8_t  PORTxx ,u8_t dir);
/*Description: sets a PINx (bitx) in PORTx value.
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for bitx location ,
             unsigned 8bit char for bit value
Return Value:void */
void MCAL_PIC_SetBitVal( u8_t  PORTxx , u8_t bitx , u8_t val);
/*Description: sets a PINx (bitx)s in PORTx values.
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for bitx location ,
             unsigned 8bit char for bitx number of bits to be changed  ,
             unsigned 8bit char for bits common value
Return Value:void */
void MCAL_PIC_SetBitSVal( u8_t  PORTxx , u8_t bitx , u8_t val,u8_t bit_counuter);
/*Description: sets PORTx values
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for bits common value
Return Value:void */
void MCAL_PIC_SetPORTVal( u8_t  PORTxx , u8_t val );
/*Description: reads the value of PINx (bitx) in PORTx .
Input Value: unsigned 8bit char for the predefined dummy port names ,
             unsigned 8bit char for bitx location .
Return Value:unsigned 8bit char holding the value of PORTx input register PINx bit */
u8_t MCAL_PIC_GetBitVal ( u8_t  PORTxx , u8_t bitx);
/*Description: reads the value of PORTx .
Input Value: unsigned 8bit char for the predefined dummy port names .
Return Value:unsigned 8bit char holding the value of PORTx input register */
u8_t MCAL_PIC_GetPINVal( u8_t  PORTxx );

void MCAL_PIC_Init_Port(u8_t PORTxx);
/*========================= InterruptManager.c Functions ========================= */
enum _Mode {OnChange,Ris_edge,Fal_edge};
extern void (* MCAL_PIC_Timer0OVHandler)       (void);
extern void (* MCAL_PIC_HighPriINTPHandler)    (void);
extern void (* MCAL_PIC_LowPriINTPHandler)     (void);
extern void (* MCAL_PIC_INTP0Handler)          (void);
extern void (* MCAL_PIC_INTP1Handler)          (void);
extern void (* MCAL_PIC_INTP2Handler)          (void);
extern void (* MCAL_PIC_INTPRBHandler)         (void);
extern void (* MCAL_PIC_SysClkHandler)         (void);
/*Description: return interrupt source in case get & serve are used
Input Value: void
Return Value:a predefined interrupt source signal mentioned in the header file*/
u8_t MCAL_PIC_GetINTSource(void);
/*Description: enables an interrupt source to send an interrupt signal and sets it's configuration mode
Input Value: Interrupt id , interrupt source if id have more then one interrupt source ,
             interrupt mode , specific to interrupt source and system basis
Return Value: void
Note:function not complete due it's not needed for the current application yet it's importing for porting */
void MCAL_PIC_INTPEn (u8_t id, u8_t source ,enum _Mode Mode);
/*Description: enables external interrupt sources on PORTB it also unmasks the interrupt & configures it
Input Value: interrupt sources as unsigned 8bit char:
             INTx0 : high priority external interrupt on PORTB RB0
             INTx1 : low priority external interrupt on PORTB RB1
             INTx2 : low priority external interrupt on PORTB RB2
             INTx5..7 : low priority external interrupt onchange  PORTB RB6 RB6 RB5
             interrupt modes as unsigned 8bit char :
             OnChange: for RB7 through RB5 only
             Rise_edge: for INTx0..2 interrupt is triggered on rising edge of the signal
             fall_edge:for INTx0..2 interrupt is triggered on fall edge of the signal
Return Value: void
Note:calls MCAL_PIC_EnGINTP() :  */
void MCAL_PIC_EnINTPx(u8_t source , enum _Mode mode);
/*Description: rewraps general interrupt enable
Input Value: void
Return Value:void*/
void MCAL_PIC_EnGINTP(void);
/*Description: rewraps general interrupt disable
Input Value: void
Return Value:void*/
void MCAL_PIC_DisGINT(void);
/*Description: serve an interrupt for it's source by calling their default handler
Input Value: interrupt source as unsigned 8bit char
Return Value:void
Note: handlers are pointers to function's of type void and input void
Note2: calling this function can serve an interrupt handler without knowing if interrupt signal actually happened in hardware */
void MCAL_PIC_IntpServe(u8_t source);
/*Description: Serves the reason of interrupt by searching for it and assigning the default
               high priority interrupt handler to it's handler then clears the interrupt flag.
Input Value: void
Return Value:void*/
void MCAL_PIC_DirectHighISR(void);
/*Description: not needed for current application yet it should disable an Interrupt by it's id
Input Value: void
Return Value: void*/
void MCAL_PIC_DisINT(u8_t INTID);
/*Description: these functions are used for interfacing with files that need to use an external interrupt
               the function links the interrupt handler to the inputed function location
               interrupt handler are always called interrupt functions should not be called directly
Input Value: a pointer to a function that takes void and returns void
Return Value:void*/
void MCAL_PIC_INTP0redirect(void (*ptr) (void));
void MCAL_PIC_INTP1redirect(void (*ptr) (void));
void MCAL_PIC_INTP2redirect(void (*ptr) (void));
void MCAL_PIC_INTPRBredirect(void (*ptr) (void));
void MCAL_PIC_Timer0OVredirect(void (*P) (void));
void MCAL_PIC_SysClkredirect(void (*P) (void));

/*========================= Timer0Module.C Functions ========================= */
/*Description: a structure for a simple concept of time
Elements : double ticks : used as the number of overflows needed to generate 1 ms and sysclk overrides it to 1
           unsigned long integer  minutes: to hold the value of counted minutes since sysclk has been enabled
           unsigned short integer milliseconds: to hold the value of counted milliseconds relative to seconds since sysclk has been enabled
           unsigned 8bit char     seconds: to hold the value of counted seconds relative to minutes since sysclk has been enabled*/
struct time{
float ticks;
u32_t minutes;
u16_t milliseconds;
u8_t seconds;
};
typedef struct time Time;
Time SysTime;
/*Description: initialize Timer0 in predefined mode that has different levels of configuration
Input Value: 1-unsigned 8bit char for possible modes :
               bit8_OV: configures timer0 to work as 8bit timer that generates an interrupt on Overflow (256)
               sys_clk: configures timer0 to work an bit8_OV and configures that to provide system time functionality through time structure global SysTime
Return Value:void*/
void MCAL_PIC_InitTimer0(u8_t mode,u16_t prescaler);
/*Description: sets the prescale value of Timer0
Input Value: void
Return Value:void*/
void MCAL_PIC_Timer0SetPS(u16_t prescaler);
/*Description: optimizes timer0 prescaler to generate an interrupt every 1 ms based on frequency settings & and prescaler old values uses MATH.c for rounding
Input Value: void
Return Value:void*/
void MCAL_PIC_Timer0_GetTick(void);
/*Description: default function to be called for SysClk interrupt handling , just increases time
Input Value: void
Return Value:void
Note : systime is a global value and it's alive form the start of the PIC till the end of the program
       it's a local systime for the purpose of the application , do not mix with the concept of unix systime */
void MCAL_PIC_Timer0SysClkHandler(void);
/*Description: a getter to access systime
Input Value: void
Return Value: copy of Systime structure is returned */
Time* MCAL_PIC_GetTime(void);
/*Description: resets SysTime global to 0
Input Value: void
Return Value: copy of Systime structure is returned */
void MCAL_PIC_ResetTime(void);
void MCAL_PIC_SysClkDef(void);
#endif /* MCAL_PIC18F_H_ */
