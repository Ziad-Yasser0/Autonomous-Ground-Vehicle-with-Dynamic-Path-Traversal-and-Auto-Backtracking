/*
 * CAR_program.c
 *
 *  Created on: Sep 4, 2026
 *      Author: ziady
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"

#include "DIO_interfce.h"

#include "DCMOTOR_interface.h"
#include "CAR_cfg.h"
#include "CAR_interface.h"

void AddNodeToLast(uint8 Copy_newDirection){
		DLL_Node* newNode = (DLL_Node*) malloc(sizeof(DLL_Node));
	    if(newNode == NULL){
		printf("Adding Node failed\n");
		return;
	    }
	    newNode->data = Copy_newDirection;
	    newNode->next = NULL;
	    newNode->previous = NULL;
	    if(head == NULL){
	        head = newNode;
	        tail = newNode;
	        return;
	    }
	    tail->next = newNode;
	    newNode->previous = tail;
	    tail = newNode;
}


void CAR_voidInit(void){
	DCMOTOR_voidInit(CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
	DCMOTOR_voidInit(CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
}

void CAR_voidMoveForward(void){
	DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
	DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
}

void CAR_voidRotateRightInPlace(void){
	DCMOTOR_voidMove(DCMOTOR_u8_CCW, CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
	DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
}

void CAR_voidRotateLefttInPlace(void){
	DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
	DCMOTOR_voidMove(DCMOTOR_u8_CCW, CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
}

