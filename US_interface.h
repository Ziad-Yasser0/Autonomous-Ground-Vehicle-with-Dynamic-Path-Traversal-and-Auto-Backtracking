/*
 * US_interface.h
 *
 *  Created on: Sep 7, 2026
 *      Author: ziady
 */

#ifndef US_INTERFACE_H
#define US_INTERFACE_H

void ULTRASONIC_voidInit(void);
void ULTRASONIC_voidRoutine(void);
void ULTRASONIC_voidIcuCallback(void);

uint16 ULTRASONIC_u16GetDistanceFwd(void);
uint16 ULTRASONIC_u16GetDistanceRight(void);
uint16 ULTRASONIC_u16GetDistanceLeft(void);

#endif
