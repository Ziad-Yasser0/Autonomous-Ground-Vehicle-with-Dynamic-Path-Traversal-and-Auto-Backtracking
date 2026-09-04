/*
 * GIE_prog.c
 *
 *  Created on: Aug 17, 2026
 *      Author: DeLL
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "GIE_Interface.h"
#include "GIE_Reg.h"

void GIE_voidEnabled(void)
{
//	SET_BIT(SREG,SREG_I);// 4clk cyc ==> cut
	__asm __volatile ("SEI"); /* Inline assembly instruction to set I bit */ // 1clk
}

void GIE_voidDisabled(void)
{
//	CLR_BIT(SREG,SREG_I);
	__asm __volatile ("CLI"); /* Inline assembly instruction to clr I bit */
}
