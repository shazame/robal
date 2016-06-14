#include <cocobot/encoders.h>
#include <platform.h>

static int32_t _enc_value[2];
static uint16_t _enc_last_angle[2];

void robal_real_starter_wait_until_is_removed(void)
{
  while(!platform_gpio_get(PLATFORM_GPIO_STARTER))
  {
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

static void robal_real_encoders_update(int id)
{
  uint16_t raw;

  if(id == 0)
  {
    platform_spi_position_select(PLATFORM_SPI_ENCR_SELECT);
  }
  else
  {
    platform_spi_position_select(PLATFORM_SPI_ENCL_SELECT);
  }

  raw = platform_spi_position_transfert(0xff) & 0xFF;
  raw |= (platform_spi_position_transfert(0xff) << 8) & 0xFF00;

  platform_spi_position_select(PLATFORM_SPI_CS_UNSELECT);

  //swap octets + delete MSB
  raw = ((raw & 0xff) << 8) | (raw >> 8);
  raw <<= 1;

  //compute new angle by abusing 16 bits integer overflow
  int16_t delta = raw - _enc_last_angle[id];
  _enc_last_angle[id] = raw;
  if(id == 0)
  {
    _enc_value[id] += delta;
  }
  else
  {
    _enc_value[id] -= delta;
  }
}

void robal_real_motor_get_position(int32_t motor_position[2])
{
  robal_real_encoders_update(0);
  robal_real_encoders_update(1);
  motor_position[0] = _enc_value[0];
  motor_position[1] = _enc_value[1];
}

void robal_real_motor_set_command(float left_motor_speed, float right_motor_speed)
{
#ifdef COCOBOT_INVERT_LEFT_MOTOR
  left_motor_speed = -left_motor_speed;
#endif
#ifdef COCOBOT_INVERT_RIGHT_MOTOR
  right_motor_speed = -right_motor_speed;
#endif

  if(left_motor_speed >= 0)
  {
#ifdef COCOBOT_LMD18200T
    left_motor_speed = 0xFFFF - left_motor_speed;
#endif
    platform_gpio_clear(PLATFORM_GPIO_MOTOR_DIR_LEFT);
    platform_motor_set_left_duty_cycle(left_motor_speed);
  }
  else
  {
    left_motor_speed = -left_motor_speed;

#ifdef COCOBOT_LMD18200T
    left_motor_speed = 0xFFFF - left_motor_speed;
#endif
    platform_gpio_set(PLATFORM_GPIO_MOTOR_DIR_LEFT);
    platform_motor_set_left_duty_cycle(left_motor_speed);
  }

  if(right_motor_speed >= 0)
  {
#ifdef COCOBOT_LMD18200T
    right_motor_speed = 0xFFFF - right_motor_speed;
#endif
    platform_gpio_clear(PLATFORM_GPIO_MOTOR_DIR_RIGHT);
    platform_motor_set_right_duty_cycle(right_motor_speed);
  }
  else
  {
    right_motor_speed = -right_motor_speed;

#ifdef COCOBOT_LMD18200T
    right_motor_speed = 0xFFFF - right_motor_speed;
#endif

    platform_gpio_set(PLATFORM_GPIO_MOTOR_DIR_RIGHT);
    platform_motor_set_right_duty_cycle(right_motor_speed);
  }
}
