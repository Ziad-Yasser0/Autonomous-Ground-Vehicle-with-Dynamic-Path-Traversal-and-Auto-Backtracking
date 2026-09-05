#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

#define DCMOTOR_u8_CW               1u
#define DCMOTOR_u8_CCW              2u



void DCMOTOR_voidInit(void);
void DCMOTOR_voidMove(uint8 Copy_u8Direction);
void DCMOTOR_voidStop(void);

#endif