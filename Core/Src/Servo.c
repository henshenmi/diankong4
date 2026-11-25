#include "Servo.h"
#include "tim.h"

/*
 * TIM2 配置为：
 * 计数时钟 1 MHz，即一个计数对应 1 us
 * ARR = 19999，即一个 PWM 周期为 20 ms、50 Hz
 *
 * SG90 的机械安全脉宽范围为 550 us至2450 us。
 * 将 0°至180°映射到这个安全范围，避免舵机顶到机械限位。
 */
uint16_t Servo_AngleToCCR(float angle)
{
    if (angle < SERVO_ANGLE_MIN)
    {
        angle = SERVO_ANGLE_MIN;
    }

    if (angle > SERVO_ANGLE_MAX)
    {
        angle = SERVO_ANGLE_MAX;
    }

    return (uint16_t)(
        SERVO_PULSE_MIN_US +
        (angle - SERVO_ANGLE_MIN) /
        (SERVO_ANGLE_MAX - SERVO_ANGLE_MIN) *
        (SERVO_PULSE_MAX_US - SERVO_PULSE_MIN_US) +
        0.5f
    );
}

void Servo_SetAngle(float angle)
{
    uint16_t ccr = Servo_AngleToCCR(angle);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr);
}

void Servo_Start(void)
{
    /* 先回中位，再启动 PWM，避免首次输出脉宽为0 */
    Servo_SetAngle(90.0f);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}
