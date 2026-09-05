#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

#define DCMOTOR_u8_CW               1u
#define DCMOTOR_u8_CCW              2u



void DCMOTOR_voidInit(uint8 Copy_u8_MOTORPIN0,uint8 Copy_u8_MOTORPIN1);
void DCMOTOR_voidMove(uint8 Copy_u8Direction,uint8 Copy_u8_MOTORPIN0,uint8 Copy_u8_MOTORPIN1);
void DCMOTOR_voidStop(uint8 Copy_u8_MOTORPIN0,uint8 Copy_u8_MOTORPIN1);

#endif
