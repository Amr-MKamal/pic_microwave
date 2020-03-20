#ifndef STDTYPES_H_INCLUDED
#define STDTYPES_H_INCLUDED

#define clr_bit(var,bit) var&=~(1<<bit)
#define get_bit(var,bit) (((var) >> (bit)) & 0x01)
#define toogle_bit(var,bit) var^=(1<<bit)
#define set_bit(var,bit)  var|=(1<<bit)
#define set_bits(var,bit,val)  var|=(val<<bit)
#define clr_bits(var,bit,val)  var&=~(!val<<bit)

typedef unsigned char u8_t;
typedef signed char s8_t;
typedef unsigned short int  u16_t;
typedef signed short int s16_t;
typedef unsigned long int u32_t;
typedef signed long int  s32_t;
typedef struct {u8_t bit:1;}virtualbool;



#endif // STDTYPES_H_INCLUDED
