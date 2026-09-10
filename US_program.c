#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interfce.h"
#include "US_config.h"
#include "US_interface.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* States and Sensor IDs */
#define TRIG_PHASE   0
#define WAIT_PHASE   1
#define DELAY_PHASE  2

#define SENSOR_FWD   0
#define SENSOR_RIGHT 1
#define SENSOR_LEFT  2

/* Global Variables */
extern volatile uint32 system_tick; // Imported from main.c

static uint8 current_state = TRIG_PHASE;
static uint8 active_sensor = SENSOR_FWD;
static uint32 g_last_tick = 0;

static uint16 dist_fwd = 999;
static uint16 dist_right = 999;
static uint16 dist_left = 999;

/* ICU Variables */
volatile uint8 g_icu_ready = 0;
volatile uint16 g_pulse_ticks = 0;
volatile uint8 g_edge_state = 0; // 0 = waiting for rising, 1 = waiting for falling

void ULTRASONIC_voidInit(void){
    /* Configure Trigger Pins as Output */
    DIO_u8SetPinDirection(ULT_FWD_TRIG_PORT, ULT_FWD_TRIG_PIN, DIO_u8PIN_OUTPUT);
    DIO_u8SetPinDirection(ULT_RIGHT_TRIG_PORT, ULT_RIGHT_TRIG_PIN, DIO_u8PIN_OUTPUT);
    DIO_u8SetPinDirection(ULT_LEFT_TRIG_PORT, ULT_LEFT_TRIG_PIN, DIO_u8PIN_OUTPUT);

    /* Configure Echo Pin (ICP1) as Input */
    DIO_u8SetPinDirection(ULT_ECHO_PORT, ULT_ECHO_PIN, DIO_u8PIN_INPUT);

    /* Timer1 ICU Setup (Prescaler = 8, 1 tick = 1us at 8MHz) */
    TCCR1A = 0;
    TCCR1B = (1 << ICES1) | (1 << CS11); // Rising edge detection, Prescaler 8
    TIMSK |= (1 << TICIE1); // Enable Input Capture Interrupt
}

void ULTRASONIC_voidRoutine(void) {
    switch (current_state) {

        case TRIG_PHASE:
            g_icu_ready = 0;
            g_edge_state = 0;
            TCCR1B |= (1 << ICES1); // Reset to detect Rising Edge

            // Fire active sensor
            if (active_sensor == SENSOR_FWD)        DIO_u8SetPinValue(ULT_FWD_TRIG_PORT, ULT_FWD_TRIG_PIN, DIO_u8PIN_HIGH);
            else if (active_sensor == SENSOR_RIGHT) DIO_u8SetPinValue(ULT_RIGHT_TRIG_PORT, ULT_RIGHT_TRIG_PIN, DIO_u8PIN_HIGH);
            else if (active_sensor == SENSOR_LEFT)  DIO_u8SetPinValue(ULT_LEFT_TRIG_PORT, ULT_LEFT_TRIG_PIN, DIO_u8PIN_HIGH);

            _delay_us(10);

            // Turn off
            DIO_u8SetPinValue(ULT_FWD_TRIG_PORT, ULT_FWD_TRIG_PIN, DIO_u8PIN_LOW);
            DIO_u8SetPinValue(ULT_RIGHT_TRIG_PORT, ULT_RIGHT_TRIG_PIN, DIO_u8PIN_LOW);
            DIO_u8SetPinValue(ULT_LEFT_TRIG_PORT, ULT_LEFT_TRIG_PIN, DIO_u8PIN_LOW);

            g_last_tick = system_tick;
            current_state = WAIT_PHASE;
            break;

        case WAIT_PHASE:
            if (g_icu_ready == 1) {
                uint16 calc_dist = g_pulse_ticks / ULT_DISTANCE_DIVISOR;

                if (active_sensor == SENSOR_FWD)        dist_fwd = calc_dist;
                else if (active_sensor == SENSOR_RIGHT) dist_right = calc_dist;
                else if (active_sensor == SENSOR_LEFT)  dist_left = calc_dist;

                g_last_tick = system_tick;
                current_state = DELAY_PHASE;
            }
            else if ((system_tick - g_last_tick) > ULT_TIMEOUT) {
                if (active_sensor == SENSOR_FWD)        dist_fwd = 999;
                else if (active_sensor == SENSOR_RIGHT) dist_right = 999;
                else if (active_sensor == SENSOR_LEFT)  dist_left = 999;

                g_last_tick = system_tick;
                current_state = DELAY_PHASE;
            }
            break;

        case DELAY_PHASE:
            if ((system_tick - g_last_tick) >= ULT_ACOUSTIC_DELAY) {
                active_sensor++;
                if (active_sensor > SENSOR_LEFT) active_sensor = SENSOR_FWD;
                current_state = TRIG_PHASE;
            }
            break;
    }
}

uint16 ULTRASONIC_u16GetDistanceFwd(void)   { return dist_fwd; }
uint16 ULTRASONIC_u16GetDistanceRight(void) { return dist_right; }
uint16 ULTRASONIC_u16GetDistanceLeft(void)  { return dist_left; }

/* Standard function instead of an ISR */
void ULTRASONIC_voidIcuCallback(void) {
    if (g_edge_state == 0) {
        // Rising edge caught: Echo pulse just started
        TCNT1 = 0;
        TCCR1B &= ~(1 << ICES1); // Switch to detect Falling Edge
        g_edge_state = 1;
    }
    else {
        // Falling edge caught: Echo pulse ended
        g_pulse_ticks = ICR1;
        g_icu_ready = 1;
    }
}
