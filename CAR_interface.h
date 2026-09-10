/*
 * CAR_interface.h
 *
 *  Created on: Sep 4, 2026
 *      Author: ziady
 */

#ifndef CAR_INTERFACE_H_
#define CAR_INTERFACE_H_

#include "STD_TYPES.h"

#define CAR_DIR_RIGHT   1u
#define CAR_DIR_LEFT    2u


typedef struct LinkedList_Node DLL_Node;

struct LinkedList_Node{
uint8 data;
DLL_Node* next;
DLL_Node* previous;
};


void CAR_voidInit(void);
void CAR_voidMoveForward(void);
void CAR_voidRotateRightInPlace(void);
void CAR_voidRotateLefttInPlace(void);
void AddNodeToLast(uint8 Copy_newDirection);
void CAR_voidStop(void);

void CAR_voidNavigateStep(void);
void CAR_voidBacktrack(void);
void AddNodeToLast(uint8 Copy_newDirection);
void CAR_voidRotate180(void);


#endif /* CAR_INTERFACE_H_ */
