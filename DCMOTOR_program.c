#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"

#include "DIO_interfce.h"

#include "DCMOTOR_cfg.h"
#include "DCMOTOR_private.h"
#include "DCMOTOR_interface.h"


void DCMOTOR_voidInit(void)
{
	DIO_u8SetPinDirection(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN2,DIO_u8PIN_OUTPUT);
}

void DCMOTOR_voidMove(uint8 Copy_u8Direction)
{
	if(Copy_u8Direction == DCMOTOR_u8_CW)
	{
		DIO_u8SetPinValue(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN1,DIO_u8PIN_HIGH);
		
	}
	else if(Copy_u8Direction == DCMOTOR_u8_CCW)
	{
		DIO_u8SetPinValue(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN2,DIO_u8PIN_HIGH);
	}
}


void DCMOTOR_voidStop(void)
{
	DIO_u8SetPinValue(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCMOTOR_u8_PORT,DCMOTOR_u8_PIN2,DIO_u8PIN_LOW);
}








