#include <robal.h>
#ifdef AUSBEE_SIM
#include <robal/vrep.h>
#else
#include <robal/real.h>
#endif

#ifdef AUSBEE_SIM
static int fake_vrep = 0;
#endif

void robal_init(void)
{
#ifdef AUSBEE_SIM
  char * fvrep = getenv("FAKE_VREP");
  if(fvrep != NULL)
  {
    if(strcmp(getenv("FAKE_VREP"), "1") == 0)
    {
      fake_vrep = 1;
    }
  }
  if(!fake_vrep)
  {
    robal_vrep_init();
  }
#endif //AUSBEE_SIM

}

void robal_starter_wait_until_is_removed(void)
{
#ifdef AUSBEE_SIM
  robal_vrep_starter_wait_until_is_removed();
#else
  robal_real_starter_wait_until_is_removed();
#endif
}

robal_starting_color_t robal_starting_color_get(void)
{
#ifdef AUSBEE_SIM
  return robal_vrep_starting_color_get();
#else
  return robal_real_starting_color_get();
#endif
}

void robal_motor_get_position(int32_t motor_position[2])
{
#ifdef AUSBEE_SIM
  if(!fake_vrep)
  {
    robal_vrep_motor_get_position(motor_position);
  }
#else
  robal_real_motor_get_position(motor_position);
#endif //AUSBEE_SIM
}

void robal_motor_set_command(float left_motor_speed, float right_motor_speed)
{
  if(left_motor_speed > 0xffff)
  {
    left_motor_speed = 0xffff;
  }
  if(left_motor_speed < -0xffff)
  {
    left_motor_speed = -0xffff;
  }
  if(right_motor_speed > 0xffff)
  {
    right_motor_speed = 0xffff;
  }
  if(right_motor_speed < -0xffff)
  {
    right_motor_speed = -0xffff;
  }

#ifdef AUSBEE_SIM
  if(!fake_vrep)
  {
    robal_vrep_motor_set_command(left_motor_speed, right_motor_speed);
  }
  else
  {
  // TODO: handle fake_vrep differently
    //motor_position[0] += right_motor_speed / 100.0f;
    //motor_position[1] += left_motor_speed / 100.0f;
  }
#else
  robal_real_motor_set_command(left_motor_speed, right_motor_speed);
#endif //AUSBEE_SIM
}
