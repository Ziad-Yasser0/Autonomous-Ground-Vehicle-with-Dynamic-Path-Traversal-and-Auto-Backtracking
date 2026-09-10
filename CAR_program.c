/*
 * CAR_program.c
 *
 *  Created on: Sep 4, 2026
 *      Author: ziady
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"
#include "stdlib.h"
#include "DIO_interfce.h"
#include "DIO_Cfg.h"
#include "DIO_Reg.h"
#include "DCMOTOR_interface.h"
#include "CAR_interface.h"
#include "CAR_cfg.h"
#include "CAR_private.h"
#include "DCMOTOR_cfg.h"
#include "DCMOTOR_private.h"
#include "TIMER_Interface.h"
#include "US_interface.h"

extern volatile uint32 system_tick;
DLL_Node* head = NULL;
DLL_Node* tail = NULL;

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
	AddNodeToLast(CAR_DIR_RIGHT); // Log the turn
}

void CAR_voidRotateLefttInPlace(void){
	DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
	DCMOTOR_voidMove(DCMOTOR_u8_CCW, CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
	AddNodeToLast(CAR_DIR_LEFT);
}

void CAR_voidStop(void){
    DCMOTOR_voidStop(CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
    DCMOTOR_voidStop(CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
}


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

void CAR_voidNavigateStep(void) {
    uint16 current_fwd_dist = ULTRASONIC_u16GetDistanceFwd();
    uint16 current_rgt_dist = 0;
    uint16 current_lft_dist = 0;

    if (current_fwd_dist != 999 && current_fwd_dist < 15) {
        CAR_voidStop();

        uint32 stop_start = system_tick;
        while ((system_tick - stop_start) < 200) {
            ULTRASONIC_voidRoutine();
        }

        current_rgt_dist = ULTRASONIC_u16GetDistanceRight();
        current_lft_dist = ULTRASONIC_u16GetDistanceLeft();

        if (current_rgt_dist != 999 && current_rgt_dist >= 15) {
            CAR_voidRotateRightInPlace();
        }
        else if (current_lft_dist != 999 && current_lft_dist >= 15) {
            CAR_voidRotateLefttInPlace();
        }
        else {
            // Dead end: All directions blocked, trigger backtracking
            CAR_voidBacktrack();
            return;
        }

        uint32 turn_start = system_tick;
        while ((system_tick - turn_start) < 400) {
            ULTRASONIC_voidRoutine();
        }
    } else {
        CAR_voidMoveForward();
    }
}

void CAR_voidBacktrack(void) {
    CAR_voidStop();

    // Traverse backward from tail to head
    DLL_Node* current = tail;
    while (current != NULL) {
        // Reverse the recorded action to retrace steps
        if (current->data == CAR_DIR_RIGHT) {
            CAR_voidRotateLefttInPlace(); // Undo right turn by turning left
        } else if (current->data == CAR_DIR_LEFT) {
            CAR_voidRotateRightInPlace(); // Undo left turn by turning right
        }

        // Wait briefly to complete the reverse rotation maneuver
        uint32 step_time = system_tick;
        while ((system_tick - step_time) < 400) {
            ULTRASONIC_voidRoutine();
        }

        // Move to the previous node in the history
        current = current->previous;
    }

    // Clear list history after backtracking completes (optional reset)
    tail = NULL;
    head = NULL;
}
