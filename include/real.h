#ifndef ROBAL_REAL_H
#define ROBAL_REAL_H

#include <stdint.h>

/* Get the position of robot's motors
 * Argument:
 *  - motor_position: pointer to store motor position, where
 *     motor_position[0] corresponds to the left motor and
 *     motor_position[1] corresponds to the right motor
 */
void robal_real_motor_get_position(int32_t motor_position[2]);

/* Set the speed of robot's motors
 * Argument:
 *  - left_motor_speed: duty cycle for the left motor
 *  - right_motor_speed: duty cycle for the right motor
 */
void robal_real_motor_set_command(float left_motor_speed, float right_motor_speed);

#endif // ROBAL_REAL_H