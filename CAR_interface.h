/*
 * CAR_interface.h
 *
 *  Created on: Sep 4, 2026
 *      Author: ziady
 */

#ifndef CAR_INTERFACE_H_
#define CAR_INTERFACE_H_

/*
typedef struct LinkedList_Node DLL_Node;

struct LinkedList_Node{
uint8 data;
DLL_Node* next;
DLL_Node* previous;
};

DLL_Node* head = NULL;
DLL_Node* tail = NULL;
*/

void CAR_voidInit(void);
void CAR_voidMoveForward(void);
void CAR_voidRotateRightInPlace(void);
void CAR_voidRotateLefttInPlace(void);
void AddNodeToLast(uint8 Copy_newDirection);
#endif /* CAR_INTERFACE_H_ */
