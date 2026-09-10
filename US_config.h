#ifndef US_CONFIG_H
#define US_CONFIG_H

/* Trigger Pins Configuration */
#define ULT_FWD_TRIG_PORT      DIO_u8PORTA
#define ULT_FWD_TRIG_PIN       DIO_u8PIN0

#define ULT_RIGHT_TRIG_PORT    DIO_u8PORTA
#define ULT_RIGHT_TRIG_PIN     DIO_u8PIN1

#define ULT_LEFT_TRIG_PORT     DIO_u8PORTA
#define ULT_LEFT_TRIG_PIN      DIO_u8PIN2

/* Echo Pin (Multiplexed to Timer1 ICU) */
#define ULT_ECHO_PORT          DIO_u8PORTD
#define ULT_ECHO_PIN           DIO_u8PIN6

/* Timing Parameters */
// Assuming Timer1 prescaler is 8 (1 tick = 1us at 8MHz)
#define ULT_DISTANCE_DIVISOR   58
#define ULT_TIMEOUT            20   // Max wait time for echo (ms)
#define ULT_ACOUSTIC_DELAY     40   // Wait before firing next sensor (ms)

#endif
