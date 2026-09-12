/*
 * CAR_cfg.h
 *
 *  Created on: Sep 4, 2026
 *      Author: ziady
 */
#ifndef CAR_CFG_H_
#define CAR_CFG_H_

#define CAR_u8WHEELSPORT        DIO_u8PORTB
#define CAR_u8RIGHTWHEELPIN1    DIO_u8PIN0
#define CAR_u8RIGHTWHEELPIN2    DIO_u8PIN1
#define CAR_u8LEFTWHEELPIN1     DIO_u8PIN2
#define CAR_u8LEFTWHEELPIN2     DIO_u8PIN3

/* --- Tuning & Adjustment Macros --- */
#define CAR_OBSTACLE_DIST_CM       15u   // Distance threshold to trigger obstacle avoidance
#define CAR_MOMENTUM_STOP_MS       200u  // Pause duration to kill physical momentum
#define CAR_TURN_90_DURATION_MS    400u  // Time to complete a 90-degree turn
#define CAR_TURN_180_DURATION_MS   800u  // Time to complete a 180-degree turn
#define CAR_CENTERING_TOLERANCE_CM   3u  // Centering deadband in cm

#endif /* CAR_CFG_H_ */
