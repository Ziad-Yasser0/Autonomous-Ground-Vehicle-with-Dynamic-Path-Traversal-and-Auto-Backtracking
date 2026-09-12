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
static uint8 is_returning = 0;

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
		//printf("Adding Node failed\n");
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

void CAR_voidRotate180(void) {
    DCMOTOR_voidMove(DCMOTOR_u8_CCW, CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
    DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);

    uint32 turn_180_start = system_tick;
    while ((system_tick - turn_180_start) < CAR_TURN_180_DURATION_MS) {
        ULTRASONIC_voidRoutine();
    }
    CAR_voidStop();
}

void CAR_voidDriveCentered(void) {
    uint16 current_rgt_dist = ULTRASONIC_u16GetDistanceRight();
    uint16 current_lft_dist = ULTRASONIC_u16GetDistanceLeft();

    if ((current_rgt_dist != 999) && (current_lft_dist != 999)) {
        if (current_rgt_dist < (current_lft_dist - CAR_CENTERING_TOLERANCE_CM)) {
            DCMOTOR_voidStop(CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
            DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
        }
        else if (current_lft_dist < (current_rgt_dist - CAR_CENTERING_TOLERANCE_CM)) {
            DCMOTOR_voidMove(DCMOTOR_u8_CW, CAR_u8RIGHTWHEELPIN1, CAR_u8RIGHTWHEELPIN2);
            DCMOTOR_voidStop(CAR_u8LEFTWHEELPIN1, CAR_u8LEFTWHEELPIN2);
        }
        else {
            CAR_voidMoveForward();
        }
    } else {
        CAR_voidMoveForward();
    }
}

void CAR_voidNavigateStep(void) {
    uint16 current_fwd_dist = ULTRASONIC_u16GetDistanceFwd();
    uint16 current_rgt_dist = 0;
    uint16 current_lft_dist = 0;

    if (current_fwd_dist != 999 && current_fwd_dist < CAR_OBSTACLE_DIST_CM) {
        CAR_voidStop();

        if (is_returning == 1) {
              while (1) {
               // CPU is trapped. Motors remain off. Car sits at the start line.
             }
        }

        uint32 stop_start = system_tick;
        while ((system_tick - stop_start) < CAR_MOMENTUM_STOP_MS) {
            ULTRASONIC_voidRoutine();
        }

        current_rgt_dist = ULTRASONIC_u16GetDistanceRight();
        current_lft_dist = ULTRASONIC_u16GetDistanceLeft();

        if (current_rgt_dist != 999 && current_rgt_dist >= CAR_OBSTACLE_DIST_CM) {
            CAR_voidRotateRightInPlace();
        }
        else if (current_lft_dist != 999 && current_lft_dist >= CAR_OBSTACLE_DIST_CM) {
            CAR_voidRotateLefttInPlace();
        }
        else {
            CAR_voidBacktrack();
            return;
        }

        uint32 turn_start = system_tick;
        while ((system_tick - turn_start) < CAR_TURN_90_DURATION_MS) {
            ULTRASONIC_voidRoutine();
        }
    } else {
    	CAR_voidDriveCentered();
    }
}

void CAR_voidBacktrack(void) {
    CAR_voidStop();

    uint32 stop_start = system_tick;
    while ((system_tick - stop_start) < CAR_MOMENTUM_STOP_MS) {
        ULTRASONIC_voidRoutine();
    }

    /* 1. Turn 180 degrees to face out of the dead end */
    CAR_voidRotate180();

    stop_start = system_tick;
    while ((system_tick - stop_start) < CAR_MOMENTUM_STOP_MS) {
        ULTRASONIC_voidRoutine();
    }

    /* 2. Traverse backward from tail to head */
    DLL_Node* current = tail;
    while (current != NULL) {

        /* A. Drive forward down the corridor FIRST until hitting the intersection wall */
        CAR_voidMoveForward();

        while (1) {
            ULTRASONIC_voidRoutine();
            uint16 fwd_dist = ULTRASONIC_u16GetDistanceFwd();
            if (fwd_dist != 999 && fwd_dist < CAR_OBSTACLE_DIST_CM) {
                CAR_voidStop();
                break;
            }
            /* Actively center the car while returning */
            CAR_voidDriveCentered();
        }

        stop_start = system_tick;
        while ((system_tick - stop_start) < CAR_MOMENTUM_STOP_MS) {
            ULTRASONIC_voidRoutine();
        }

        /* B. NOW execute the inverse turn at the intersection */
        if (current->data == CAR_DIR_RIGHT) {
            CAR_voidRotateLefttInPlace();
        } else if (current->data == CAR_DIR_LEFT) {
            CAR_voidRotateRightInPlace();
        }

        uint32 turn_time = system_tick;
        while ((system_tick - turn_time) < CAR_TURN_90_DURATION_MS) {
            ULTRASONIC_voidRoutine();
        }

        /* C. Safely free memory and move to the previous node */
        DLL_Node* next_node_to_free = current->previous;
        free(current);
        current = next_node_to_free;
    }

    /* Reset list anchors */
    tail = NULL;
    head = NULL;

    /* Mission accomplished, now on the final stretch */
    is_returning = 1;
}

