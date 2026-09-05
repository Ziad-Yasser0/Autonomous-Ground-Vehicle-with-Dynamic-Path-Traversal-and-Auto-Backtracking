#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"
#include "DIO_interfce.h"
#include "CAR_cfg.h"
#include "DCMOTOR_cfg.h"
#include "DCMOTOR_private.h"
#include "DCMOTOR_interface.h"


void DCMOTOR_voidInit(uint8 Copy_u8_MOTORPIN0,uint8 Copy_u8_MOTORPIN1)
{
	DIO_u8SetPinDirection(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN1,DIO_u8PIN_OUTPUT);
}

void DCMOTOR_voidMove(uint8 Copy_u8Direction,uint8 Copy_u8_MOTORPIN0,uint8 Copy_u8_MOTORPIN1)
{
	if(Copy_u8Direction == DCMOTOR_u8_CW)
	{
		DIO_u8SetPinValue(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN0,DIO_u8PIN_HIGH);
		
	}
	else if(Copy_u8Direction == DCMOTOR_u8_CCW)
	{
		DIO_u8SetPinValue(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN1,DIO_u8PIN_HIGH);
	}
}


void DCMOTOR_voidStop(uint8 Copy_u8_MOTORPIN0,uint8 Copy_u8_MOTORPIN1)
{
	DIO_u8SetPinValue(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CAR_u8WHEELSPORT,Copy_u8_MOTORPIN1,DIO_u8PIN_LOW);
}








