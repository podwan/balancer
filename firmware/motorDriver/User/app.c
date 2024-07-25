
#include "app.h"
#include "led.h"
#include "key.h"
#include "comm.h"
#include "mt6701.h"
#include "bldcMotor.h"
#include "encoder.h"
#include "pid.h"
#include "lowpass_filter.h"
#include "current.h"
#include "userTimer.h"
#include "voltage.h"
#include "mpu6500.h"
#include "pwm.h"
#include "AHRS.h"
#include "joyStick.h"

static DevState devState = WORK;
static KeyState keyState;
static uchar flashCnt;
float load_data[8];
uint8_t tempData[36] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x7F};

float txA, txB, txC;
static BldcMotor motor1, motor2;

static void standingBy();
static void working(void);

// should be called before interruption enabled

static void motorInit()
{
#if 1
    motor1.pole_pairs = 7;

    motor1.updatePwm = updatePwm1;
    motor1.startPwm = startPwm1;
    motor1.stopPwm = stopPwm1;
    motor1.zeroElectricAngleOffSet = 0;
    motor1.Ts = 100 * 1e-6f;
    motor1.torqueType = VOLTAGE;

    motor1.controlType = VELOCITY;

    motor1.state = MOTOR_CALIBRATE;
    encoderInit(&motor1.magEncoder, motor1.Ts, _1_MT6701_GetRawAngle, UNKNOWN);

    if (motor1.controlType == TORQUE && motor1.torqueType == CURRENT)
    {
        float kp, ki;
        kp = 500.0f;
        ki = 50.0f;
        pidInit(&motor1.pidId, kp, ki, 0, 0, UqMAX, motor1.Ts);
        // pidInit(&motor1.pidIq, kp, ki, 0, 0, UqMAX, motor1.Ts);
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

#endif
    motor2.pole_pairs = 7;
    motor2.updatePwm = updatePwm2;
    motor2.startPwm = startPwm2;
    motor2.stopPwm = stopPwm2;
    motor2.zeroElectricAngleOffSet = 0;
    motor2.Ts = 100 * 1e-6f;
    motor2.torqueType = VOLTAGE;
    motor2.controlType = VELOCITY;

    motor2.state = MOTOR_CALIBRATE;
    encoderInit(&motor2.magEncoder, motor2.Ts, _2_MT6701_GetRawAngle, UNKNOWN);
    if (motor2.controlType == TORQUE && motor2.torqueType == CURRENT)
    {
        float kp, ki;
        kp = -200;
        ki = -20;
        pidInit(&motor2.pidId, kp, ki, 0, 0, UqMAX, motor2.Ts);
        pidInit(&motor2.pidIq, kp, ki, 0, 0, UqMAX, motor2.Ts);
    }
    else if (motor2.controlType == VELOCITY)
    {
        if (motor2.torqueType == CURRENT)
        {
            pidInit(&motor2.velocityPID, 0.02, 0.01, 0, 0, CURRENT_MAX, motor2.Ts);

            float kp, ki;
            kp = 500.0f;
            ki = 50.0f;
            pidInit(&motor2.pidId, kp, ki, 0, 0, UqMAX, motor2.Ts);
            pidInit(&motor2.pidIq, kp, ki, 0, 0, UqMAX, motor2.Ts);
        }
        else
        {
            pidInit(&motor2.velocityPID, 0.15, 0.05, 0, 0, UqMAX, motor2.Ts);
        }
    }
    else if (motor2.controlType == ANGLE)
    {
        if (motor2.torqueType == CURRENT)
        {
            pidInit(&motor2.anglePID, 2, 0, 0, 0, MAX_VELOCITY, motor2.Ts);

            pidInit(&motor2.velocityPID, -0.02, -0.01, 0, 0, CURRENT_MAX, motor2.Ts);

            // pidInit(&motor1.anglePID, -0.001, -0.0001, 0, 0, CURRENT_MAX / 2, motor1.Ts);

            float kp, ki;
            kp = -200;
            ki = -20;
            pidInit(&motor2.pidId, kp, ki, 0, 0, UqMAX, motor2.Ts);
            pidInit(&motor2.pidIq, kp, ki, 0, 0, UqMAX, motor2.Ts);
        }
        else
        {
            pidInit(&motor2.anglePID, 0.3, 0.001, 0, 0, UqMAX / 2, motor2.Ts);
        }
    }

    lpfInit(&motor2.IqFilter, 0.05, motor1.Ts);
    lpfInit(&motor2.IdFilter, 0.05, motor1.Ts);
    lpfInit(&motor2.velocityFilter, 0.01, motor1.Ts);
}
static float v;

// balancer
PidController pid_stb;
PidController pid_vel;
float target_pitch;
LowPassFilter lpf_pitch_cmd, lpf_throttle, lpf_steering;
// joyStick

void appInit()
{

    motorInit();
    devState = STANDBY;
    v = 2400;
    // balance
    // pidInit(&pid_stb, 0.14, 0.5, 0.01, 0, UqMAX, 100 * 1e-6f);
    pidInit(&pid_stb, 0.1, 0.4, 0.01, 0, UqMAX, 100 * 1e-6f);
    pidInit(&pid_vel, 0.01, 0.03, 0, 0, 20, 100 * 1e-6f);
    lpfInit(&lpf_pitch_cmd, 0.07, 100 * 1e-6f);
    lpfInit(&lpf_throttle, 0.5, 100 * 1e-6f);
    lpfInit(&lpf_steering, 0.1, 100 * 1e-6f);
}
static bool zeroReset, _1s;
void appRunning()
{
    _1s = getOneSecFlag();
    getKeyState(&keyState);
    commander_run(&motor1, &motor2);
    if (++flashCnt >= 10)
        flashCnt = 0;

    ledOn = 0;

#if USE_COMM_TARGET == 0
    uint32_t Vpoten;
    float goalVelocity;
    HAL_ADC_Start(&hadc1);
    // HAL_ADC_Start(&hadc2);
    Vpoten = HAL_ADC_GetValue(&hadc1);

    goalVelocity = map(Vpoten, 0, 4095, -MAX_VELOCITY, MAX_VELOCITY);

    // goalVelocity = Vpoten / 4095.0f * MAX_VELOCITY;
    float goalTorqueV = map(Vpoten, 0, 4095, -UqMAX, UqMAX);
    float goalTorqueC = map(Vpoten, 0, 4095, -CURRENT_MAX, CURRENT_MAX);

    // adc_vbus = HAL_ADC_GetValue(&hadc2);

    // Vbus = adc_vbus * 3.3f / 4096 * 26;

    if (motor1.controlType == VELOCITY || motor1.controlType == VELOCITY_OPEN_LOOP)
    {
        motor1.target = goalVelocity;
    }

    else if (motor1.controlType == ANGLE)
    {
        motor1.target = goalVelocity / 3;
    }
    else if (motor1.controlType == TORQUE)
    {
        if (motor1.torqueType == VOLTAGE)
        {
            motor1.target = goalTorqueV;
        }
        else
        {
            motor1.target = goalTorqueC;
        }
    }

    if (motor2.controlType == VELOCITY || motor2.controlType == VELOCITY_OPEN_LOOP)
    {

        motor2.target = goalVelocity;
    }

    else if (motor2.controlType == ANGLE)
    {
        motor2.target = goalVelocity / 3;
    }
    else if (motor2.controlType == TORQUE)
    {
        if (motor2.torqueType == VOLTAGE)
        {
            motor2.target = goalTorqueV;
        }
        else
        {
            motor2.target = goalTorqueC;
        }
    }
#endif

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
    if (_1s)
    {
        // v -= 20;
        // HAL_DAC_SetValue(&hdac3, DAC_CHANNEL_2, DAC_ALIGN_12B_R, v);
    }
    _1s = 0;
}
static void standingBy()
{
    static bool notFirstTime;
    static uchar cnt;
    ledOn = 1;
    // setTorque(&motor1, 0, OPEN_LOOP_TORQUE, 0);
    // if (zeroReset == 0)
    // {
    //     goToZeroElecAngle(&motor1);
    //     goToZeroElecAngle(&motor2);
    //     zeroReset = 1;
    // }
    // else
    // {
    motor1.stopPwm();
    motor2.stopPwm();
    // }

    //  if (((+cnt >= 30 && notFirstTime == 0) || keyState == USER1_SHORT) && imu.pit <= 30 && imu.pit >= -30)
    if (keyState == USER1_SHORT)
    {
        notFirstTime = 1;
        WORK_INIT;
    }
}

static void working(void)
{
    zeroReset = 0;
    if (flashCnt < 5)
        ledOn = 1;

    // if (keyState == USER1_SHORT || imu.pit > 60 || imu.pit < -60)
    if (keyState == USER1_SHORT)
    {
        STANDBY_INIT;
    }
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
    //  sprintf(txBuffer, "ok\n");
    // if (_1s)
    // {
    //     static uchar cnt;
    //     if (++cnt >= 3)
    //     {
    //         on = !on;
    //         cnt = 0;
    //     }
    // }

    // if (on)
    //     _1_MT6701_CS_Enable;
    // else
    //     _1_MT6701_CS_Disable;
    // uint16_t rawData1, rawData2;
    // rawData1 = _1_MT6701_GetRawData();
    //  rawData2 = _2_MT6701_GetRawData();
    // sprintf(txBuffer, "accAngle.y : %.2f gyroAngle.y : %.2f\n", mpu6500.accAngle.y, mpu6500.gyroAngle.y);

    //  sprintf(txBuffer, "rawData1: %d,rawData2: %d\n", rawData1, rawData2);
    //  sprintf(txBuffer, "pitch : %.2f,  P: %.4f, I:%.4f,D:%.4f \n", imu.pit, pid_stb.P, pid_stb.I, pid_stb.D);

    sprintf(txBuffer, "target_pitch %.2f, throttle %.2f, steering %.2f P: %.4f, I:%.4f,D:%.4f \n", target_pitch, throttle, steering, pid_vel.P, pid_vel.I, pid_vel.D);

    // sprintf(txBuffer, "target:%.2f  velocity1:%.2f  Iq1:%.2f Id1:%.2f  velocity2:%.2f  Iq2:%.2f Id2:%.2f\n", motor1.target, motor1.magEncoder.velocity, motor1.Iq, motor1.Id, motor2.magEncoder.velocity, motor2.Iq, motor2.Id);
    //  sprintf(txBuffer, "target:%.2f fullAngle:%.2f velocity:%.2f Uq:%.2f Ud:%.2f Iq:%.2f Id:%.2f elec_angle:%.2f\n", motor1.target, motor1.magEncoder.fullAngle, motor1.magEncoder.velocity, motor1.Uq, motor1.Ud, motor1.Iq, motor1.Id, motor1.angle_el);

    // sprintf(txBuffer, "pitch : %.2f,  P: %.2f,  I:%.2f, D:%.2f, V1:%.2f, T2:%.2f\n", imu.pit, pid_stb.P, pid_stb.I, pid_stb.D, motor1.magEncoder.velocity, motor2.target);
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    HAL_GPIO_WritePin(TEST_GPIO_Port, TEST_Pin, GPIO_PIN_SET);
    if (hadc == &hadc1)
    {
        static bool shift;
        shift = !shift;
        if (shift)
        {
             foc(&motor1, hadc1.Instance->JDR1, hadc2.Instance->JDR1);
        }
        else
        {
            //foc(&motor2, hadc1.Instance->JDR2, hadc1.Instance->JDR3);
        }

        dealPer100us();
#if USE_COMM_TARGET
        balancerControl();
#endif
        // HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
#if SHOW_WAVE
        // #if SHOW_SVPWM
        // load_data[0] = motor1.Ta;
        // load_data[1] = motor1.Tb;
        // load_data[2] = motor1.Tc;
        // load_data[3] = motor2.Ta;
        // load_data[4] = motor2.Tb;
        // load_data[5] = motor2.Tc;
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
        // load_data[0] = motor2.Ia;
        // load_data[1] = motor2.Ib;
        // load_data[2] = motor2.Ic;
        load_data[3] = motor1.Ialpha;
        load_data[4] = motor1.Ibeta;

        load_data[5] = motor1.Id;
        load_data[6] = motor1.Iq;

        // load_data[3] = motor2.Id;
        // load_data[4] = motor2.Iq;

        //  load_data[3] = motor2.Ia;
        //         load_data[4] = motor2.Ib;
        //         load_data[5] = motor2.Ic;
        // load_data[3] = motor2.Ialpha;
        // load_data[4] = motor2.Ibeta;

        // load_data[5] = motor2.Id;
        // load_data[6] = motor2.Iq;
        // // load_data[6] = motor1.magEncoder.velocity;
        // load_data[7] = motor2.magEncoder.velocity;

        // load_data[0] = motor1.target;
        // load_data[1] = motor1.magEncoder.velocity;
        // load_data[2] = motor2.magEncoder.velocity;
        // load_data[3] = motor1.Uq;
        // load_data[4] = motor2.Uq;

        // load_data[6] = hadc1.Instance->JDR1;
        // load_data[7] = hadc1.Instance->JDR2;

        memcpy(tempData, (uint8_t *)&load_data, sizeof(load_data));
        HAL_UART_Transmit_DMA(&huart3, (uint8_t *)tempData, sizeof(tempData));
#endif
    }
    HAL_GPIO_WritePin(TEST_GPIO_Port, TEST_Pin, GPIO_PIN_RESET);
}

void balancerControl()
{

    // calculate the target angle for throttle control

    target_pitch = pidOperator(&pid_vel, ((motor1.magEncoder.velocity + motor2.magEncoder.velocity) / 2 - lpfOperator(&lpf_throttle, throttle))) + STABLE_TIP;
    // float target_pitch = ;
    // calculate the target voltage
    float voltage_control = pidOperator(&pid_stb, target_pitch - imu.pit);
    // filter steering
    float steering_adj = lpfOperator(&lpf_steering, steering);
    // set the tergat voltage value
    motor1.target = voltage_control + steering_adj;
    motor2.target = voltage_control - steering_adj;
}