#ifndef US_PRIVATE_H
#define US_PRIVATE_H

/* Round-Robin State Machine Definitions */
typedef enum {
    TRIG_FWD = 0,
    WAIT_FWD,
    DELAY_FWD,
    TRIG_RIGHT,
    WAIT_RIGHT,
    DELAY_RIGHT,
    TRIG_LEFT,
    WAIT_LEFT,
    DELAY_LEFT
} Ultrasonic_State_t;

/* Conversion Constant: 1 tick = 1us. distance(cm) = time(us) / 58 */
#define ULT_DISTANCE_DIVISOR 58u

/* Private ISR Callback */
static void ULTRASONIC_voidICUCallback(void);

#endif
