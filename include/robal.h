#ifndef ROBAL_H
#define ROBAL_H

void robal_init(void);

void robal_starter_wait_until_is_removed(void);

void robal_motor_get_position(int32_t motor_position[2]);
void robal_motor_set_command(float left_motor_speed, float right_motor_speed);

#endif /* ROBAL_H */
