/*
 * main.c
 *
 *  Created on: Sep 5, 2026
 *      Author: sayba
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interfce.h"
#include "DIO_Cfg.h"
#include "DCMOTOR_cfg.h"
#include "CAR_cfg.h"
#include "CAR_interface.h"
#include <util/delay.h>


int main(){
	CAR_voidInit();
	while(1){
		CAR_voidMoveForward();
		_delay_ms(2000);
		CAR_voidRotateRightInPlace();
		_delay_ms(2000);
		CAR_voidRotateLefttInPlace();
		_delay_ms(2000);
	}
}
