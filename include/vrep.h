#ifndef ROBAL_VREP_H
#define ROBAL_VREP_H

#include <stdint.h>

/* Initialization of vrep communication module. Has to be called before any other action
 */
void robal_vrep_init(void);

/* Get the position of virtual robot's motors
 * Argument:
 *  - motor_position: pointer to store motor position, where
 *     motor_position[0] corresponds to the left motor and
 *     motor_position[1] corresponds to the right motor
 */
void robal_vrep_motor_get_position(int32_t motor_position[2]);

/* Set the speed of virtual robot's motors
 * Argument:
 *  - left_motor_speed: VREP joint velocity for the left motor
 *  - right_motor_speed: VREP joint velocity for the right motor
 */
void robal_vrep_motor_set_command(float left_motor_speed, float right_motor_speed);

/* Set the x position of the virtual robot
 * Argument:
 *  - x: robot position in mm
 */
void robal_vrep_position_set_x(float x);

/* Set the y position of the virtual robot
 * Argument:
 *  - y: robot position in mm
 */
void robal_vrep_position_set_y(float y);

/* Set the orientation of the virtual robot
 * Argument:
 *  - angle: robot orientation in deg
 */
void robal_vrep_position_set_angle(float angle);

#endif // ROBAL_VREP_H
