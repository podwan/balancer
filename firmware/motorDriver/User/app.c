
#include "app.h"
#include "led.h"
// #include "key.h"
#include "comm.h"
#include "mt6701.h"
#include "bldcMotor.h"
#include "encoder.h"
#include "pid.h"
#include "lowpass_filter.h"
#include "current.h"
#include "userTimer.h"
#include "voltage.h"

static DevState devState = WORK;
static KeyState keyState;
static uchar flashCnt;
float load_data[8];
uint8_t tempData[36] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x7F};

float txA, txB, txC;
static BldcMotor motor1;

static void standingBy();
static void working(void);
static void updatePwm1(unsigned short int a, unsigned short int b, unsigned short int c);
static void startPwm1()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    // HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
    // HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
    // HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
}
static void stopPwm1()
{
    HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
    // HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
    // HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
    // HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
}
static void updatePwm1(unsigned short int a, unsigned short int b, unsigned short int c)
{
    TIM8->CCR1 = a;
    TIM8->CCR2 = b;
    TIM8->CCR3 = c;
}
// should be called before interruption enabled

static void motorInit()
{
    motor1.pole_pairs = 7;

    motor1.updatePwm = updatePwm1;
    motor1.startPwm = startPwm1;
    motor1.stopPwm = stopPwm1;
    motor1.zeroElectricAngleOffSet = 0;
    motor1.Ts = 100 * 1e-6f;
    motor1.torqueType = CURRENT;

    motor1.controlType = VELOCITY;

    motor1.state = MOTOR_CALIBRATE;
    encoderInit(&motor1.magEncoder, motor1.Ts, MT6701_GetRawAngle, UNKNOWN);

    if (motor1.controlType == TORQUE && motor1.torqueType == CURRENT)
    {
        float kp, ki;
        kp = 500.0f;
        ki = 50.0f;
        pidInit(&motor1.pidId, kp, ki, 0, 0, UqMAX, motor1.Ts);
        pidInit(&motor1.pidIq, kp, ki, 0, 0, UqMAX, motor1.Ts);
    }
    else if (motor1.controlType == VELOCITY)
    {
        if (motor1.torqueType == CURRENT)
        {
            pidInit(&motor1.velocityPID, 0.02, 0.01, 0, 0, CURRENT_MAX, motor1.Ts);

            float kp, ki;
            kp = 500.0f;
            ki = 50.0f;
            pidInit(&motor1.pidId, kp, ki, 0, 0, UqMAX, motor1.Ts);
            pidInit(&motor1.pidIq, kp, ki, 0, 0, UqMAX, motor1.Ts);
        }
        else
        {
            pidInit(&motor1.velocityPID, 0.15, 0.05, 0, 0, UqMAX, motor1.Ts);
        }
    }
    else if (motor1.controlType == ANGLE)
    {
        if (motor1.torqueType == CURRENT)
        {
            pidInit(&motor1.anglePID, 2, 0, 0, 0, MAX_VELOCITY, motor1.Ts);

            pidInit(&motor1.velocityPID, -0.02, -0.01, 0, 0, CURRENT_MAX, motor1.Ts);

            // pidInit(&motor1.anglePID, -0.001, -0.0001, 0, 0, CURRENT_MAX / 2, motor1.Ts);

            float kp, ki;
            kp = -200;
            ki = -20;
            pidInit(&motor1.pidId, kp, ki, 0, 0, UqMAX, motor1.Ts);
            pidInit(&motor1.pidIq, kp, ki, 0, 0, UqMAX, motor1.Ts);
        }
        else
        {
            pidInit(&motor1.anglePID, 0.3, 0.001, 0, 0, UqMAX / 2, motor1.Ts);
        }
    }

    lpfInit(&motor1.IqFilter, 0.05, motor1.Ts);
    lpfInit(&motor1.IdFilter, 0.05, motor1.Ts);
    lpfInit(&motor1.velocityFilter, 0.01, motor1.Ts);
}
void appInit()
{
    motorInit();
    devState = WORK;
    //    MPU6050_Init(); // MPU6050初始化
}
static bool zeroReset;
void appRunning()
{

    //  getKeyState(&keyState);
    commander_run(&motor1);
    if (++flashCnt >= 10)
        flashCnt = 0;

    ledOn = 0;

#if USE_COMM_TARGET == 0
    uint32_t Vpoten, adc_vbus;
    float Vbus, goalVelocity;
    HAL_ADC_Start(&hadc1);
    HAL_ADC_Start(&hadc2);
    Vpoten = HAL_ADC_GetValue(&hadc1);

    // goalVelocity = map(Vpoten, 0, 4095, -MAX_VELOCITY, MAX_VELOCITY);

    // goalVelocity = Vpoten / 4095.0f * MAX_VELOCITY;
    // float goalTorqueV = map(Vpoten, 0, 4095, -UqMAX, UqMAX);
    // float goalTorqueC = map(Vpoten, 0, 4095, -CURRENT_MAX, CURRENT_MAX);

    // adc_vbus = HAL_ADC_GetValue(&hadc2);

    // Vbus = adc_vbus * 3.3f / 4096 * 26;

    // if (motor1.controlType == VELOCITY || motor1.controlType == VELOCITY_OPEN_LOOP)
    // {
    //     motor1.target = goalVelocity;
    // }

    else if (motor1.controlType == ANGLE)
    {
        motor1.target = goalVelocity / 3;
    }
    else if (motor1.controlType == TORQUE)
    {
        if (motor1.torqueType == VOLTAGE)
            motor1.target = goalTorqueV;
        else
            motor1.target = goalTorqueC;
    }
#endif

    // else if (motor1.controlType == ANGLE)
    // {
    //     motor1.target = goalVelocity / 3;
    // }
    // else if (motor1.controlType == TORQUE)
    // {
    //     if (motor1.torqueType == VOLTAGE)
    //         motor1.target = goalTorqueV;
    //     else
    //         motor1.target = goalTorqueC;
    // }

    switch (devState)
    {
    case STANDBY:
        standingBy();
        break;

    case WORK:
        working();
        break;
    }

    LED_drive();
}
static void standingBy()
{
    static uchar cnt;

    ledOn = 1;
    // setTorque(&motor1, 0, OPEN_LOOP_TORQUE, 0);
    if (zeroReset == 0)
    {
        goToZeroElecAngle(&motor1);
        zeroReset = 1;
    }
    else
        motor1.stopPwm();

    if (++cnt >= 10)
    {
        WORK_INIT;
    }
}

static void working(void)
{
    zeroReset = 0;
    if (flashCnt < 5)
        ledOn = 1;

    //    if (keyState == USER3_SHORT)
    //    {
    //        STANDBY_INIT;
    //    }
    //    else if (keyState == USER2_SHORT)
    //    {
    //        //  if (bldcMotor.controlMode == VELOCITY)
    //        // {
    //        //     if (bldcMotor.focTarget == 0)
    //        //     {
    //        //         bldcMotor.focTarget = 23;
    //        //     }
    //        //     else if (bldcMotor.focTarget == 23)
    //        //     {
    //        //         bldcMotor.focTarget = -23;
    //        //     }
    //        //     else if (bldcMotor.focTarget == -23)
    //        //     {
    //        //         bldcMotor.focTarget = 23;
    //        //     }
    //        // }
    //    }
}

void txDataProcess()
{

    // sprintf(txBuffer, "target:%.2f fullAngle:%.2f velocity:%.2f Uq:%.2f Ud:%.2f Iq:%.2f Id:%.2f elec_angle:%.2f\n", motor1.target, motor1.magEncoder.fullAngle, motor1.magEncoder.velocity, motor1.Uq, motor1.Ud, motor1.Iq, motor1.Id, motor1.angle_el);

    // sprintf(txBuffer, "target:%.2f  velocity:%.2f  Uq:%.2f\n", motor1.target, motor1.magEncoder.velocity, motor1.Uq);
    sprintf(txBuffer, "target:%.2f,velocity:%.2f,Uq%.2f,Ud%.2f,Iq:%.2f,Id:%.2f\n", motor1.target, motor1.magEncoder.velocity, motor1.Uq, motor1.Ud, motor1.Iq, motor1.Id);
    // sprintf(txBuffer, "offset_ia:%f offset_ib:%f, Ia:%f, Ib:%f\n", motor1.offset_ia, motor1.offset_ib, motor1.Ia, motor1.Ib);
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    HAL_GPIO_WritePin(TEST_GPIO_Port, TEST_Pin, GPIO_PIN_SET);
    if (hadc == &hadc1)
    {

        foc(&motor1, hadc1.Instance->JDR1, hadc2.Instance->JDR1);

        dealPer100us();

#if SHOW_WAVE
        // #if SHOW_SVPWM
        // load_data[0] = motor1.Ta;
        // load_data[1] = motor1.Tb;
        // load_data[2] = motor1.Tc;
        //         load_data[3] = motor1.Id;
        //         load_data[4] = motor1.Iq;
        //         load_data[5] = motor1.angle_el;
        //         load_data[6] = motor1.Uq;
        //         load_data[7] = motor1.target;
        // #elif CALI_PID

        //         load_data[0] = motor1.target;
        //         if (motor1.controlType == VELOCITY || motor1.controlType == VELOCITY_OPEN_LOOP)
        //             load_data[1] = motor1.magEncoder.velocity;
        //         else if (motor1.controlType == ANGLE)
        //             load_data[1] = motor1.magEncoder.fullAngle;

        //         load_data[2] = motor1.Uq;

        // show current

        load_data[0] = motor1.Ia;
        load_data[1] = motor1.Ib;
        load_data[2] = motor1.Ic;

        load_data[3] = motor1.Ialpha;
        load_data[4] = motor1.Ibeta;

        load_data[5] = motor1.Id;
        load_data[6] = motor1.Iq;

        memcpy(tempData, (uint8_t *)&load_data, sizeof(load_data));
        HAL_UART_Transmit_DMA(&huart3, (uint8_t *)tempData, sizeof(tempData));
#endif
    }
    HAL_GPIO_WritePin(TEST_GPIO_Port, TEST_Pin, GPIO_PIN_RESET);
}