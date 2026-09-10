#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_interface.h"
#include "DIO_interfce.h"
#include "GIE_interface.h"
#include "US_interface.h"
#include "CAR_interface.h"

volatile uint32 system_tick = 0;

void IncrementSystemTick(void) {
    system_tick++;
}

int main(void) {
    TIMER_voidTimer0Init();
    TIMER_voidTimer0SetCompareValue(124);
    TIMER_voidTimer0SetCallBack(IncrementSystemTick);

    ULTRASONIC_voidInit();
    ICU_voidSetCallBack(ULTRASONIC_voidIcuCallback);

    CAR_voidInit();
    GIE_voidEnabled();

    while (1) {
        ULTRASONIC_voidRoutine();
        CAR_voidNavigateStep();
    }
}
