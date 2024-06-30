#include "mpu6500.h"
static uint8_t tx, rx;    // 定义读写变量
volatile float q0 = 1.0f; // 四元数系数
volatile float q1 = 0.0f;
volatile float q2 = 0.0f;
volatile float q3 = 0.0f;
volatile float exInt, eyInt, ezInt;                       /* 错误提示 */
static uint8_t tx_buff[14] = {0xff};                      // MPU6500数据变量（加速度，温度，角度）
extern SPI_HandleTypeDef hspi5;                           // 重新声明
uint8_t mpu_buff[14];                                     // 保存IMU原始数据
uint8_t ist_buff[6];                                      // 保存IST8310原始数据
mpu_data_t mpu_data;                                      // 定义MPU数据句柄
imu_t imu = {0};                                          // IMU数据储存
uint8_t id;                                               // 定义ID
static volatile float gx, gy, gz, ax, ay, az, mx, my, mz; // 储存IMU更新值
volatile uint32_t last_update, now_update;                /* 采样周期, 单位 ms */

// 快速平方根倒数，计算 1/Sqrt(x)
// X:数字还需要计算
// 调用imu ahrs update()函数
float inv_sqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *)&y;

    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));

    return y;
}
// MPU6500单次写命令
uint8_t mpu_write_byte(uint8_t const reg, uint8_t const data)
{
    MPU_NSS_LOW;                                         // 开始通讯
    tx = reg & 0x7F;                                     // 使第一位为0（写模式）
    HAL_SPI_TransmitReceive(&MPU_HSPI, &tx, &rx, 1, 55); // 写入命令地址
    tx = data;
    HAL_SPI_TransmitReceive(&MPU_HSPI, &tx, &rx, 1, 55); // 写入数据
    MPU_NSS_HIGH;                                        // 结束通讯
    return 0;
}
// MPU6500单次读取单字节数据
uint8_t mpu_read_byte(uint8_t const reg)
{
    MPU_NSS_LOW;
    tx = reg | 0x80;                                     // 使地址第一位为1（读模式）
    HAL_SPI_TransmitReceive(&MPU_HSPI, &tx, &rx, 1, 55); // 写入需要读取的地址
    HAL_SPI_TransmitReceive(&MPU_HSPI, &tx, &rx, 1, 55); // 为读取的数据提供存储空间
    MPU_NSS_HIGH;
    return rx;
}

// MPU6500单次读取多字节数据
uint8_t mpu_read_bytes(uint8_t const regAddr, uint8_t *pData, uint8_t len)
{
    MPU_NSS_LOW;
    tx = regAddr | 0x80;
    tx_buff[0] = tx;
    HAL_SPI_TransmitReceive(&MPU_HSPI, &tx, &rx, 1, 55);
    HAL_SPI_TransmitReceive(&MPU_HSPI, tx_buff, pData, len, 55);
    MPU_NSS_HIGH;
    return 0;
}

// 设置imu 6500陀螺仪测量范围
uint8_t mpu_set_gyro_fsr(uint8_t fsr)
{
    return mpu_write_byte(MPU6500_GYRO_CONFIG, fsr << 3);
}
// 设置imu 6050/6500加速测量范围
uint8_t mpu_set_accel_fsr(uint8_t fsr)
{
    return mpu_write_byte(MPU6500_ACCEL_CONFIG, fsr << 3);
}
// 获取IMU数据
void mpu_get_data()
{
    mpu_read_bytes(MPU6500_ACCEL_XOUT_H, mpu_buff, 14);

    mpu_data.ax = mpu_buff[0] << 8 | mpu_buff[1];
    mpu_data.ay = mpu_buff[2] << 8 | mpu_buff[3];
    mpu_data.az = mpu_buff[4] << 8 | mpu_buff[5];
    mpu_data.temp = mpu_buff[6] << 8 | mpu_buff[7];

    mpu_data.gx = ((mpu_buff[8] << 8 | mpu_buff[9]) - mpu_data.gx_offset);
    mpu_data.gy = ((mpu_buff[10] << 8 | mpu_buff[11]) - mpu_data.gy_offset);
    mpu_data.gz = ((mpu_buff[12] << 8 | mpu_buff[13]) - mpu_data.gz_offset);

    // ist8310_get_data(ist_buff);
    // memcpy(&mpu_data.mx, ist_buff, 6);

    memcpy(&imu.ax, &mpu_data.ax, 6 * sizeof(int16_t));

    imu.temp = 21 + mpu_data.temp / 333.87f;
    /* 2000dps -> rad/s */
    imu.wx = mpu_data.gx / 16.384f / 57.3f;
    imu.wy = mpu_data.gy / 16.384f / 57.3f;
    imu.wz = mpu_data.gz / 16.384f / 57.3f;
}
// 获取MPU6500的偏移量数据
void mpu_offset_call(void)
{
    int i;
    for (i = 0; i < 300; i++)
    {
        mpu_read_bytes(MPU6500_ACCEL_XOUT_H, mpu_buff, 14);

        mpu_data.ax_offset += mpu_buff[0] << 8 | mpu_buff[1];
        mpu_data.ay_offset += mpu_buff[2] << 8 | mpu_buff[3];
        mpu_data.az_offset += mpu_buff[4] << 8 | mpu_buff[5];

        mpu_data.gx_offset += mpu_buff[8] << 8 | mpu_buff[9];
        mpu_data.gy_offset += mpu_buff[10] << 8 | mpu_buff[11];
        mpu_data.gz_offset += mpu_buff[12] << 8 | mpu_buff[13];

        HAL_Delay(5);
    }
    mpu_data.ax_offset = mpu_data.ax_offset / 300;
    mpu_data.ay_offset = mpu_data.ay_offset / 300;
    mpu_data.az_offset = mpu_data.az_offset / 300;
    mpu_data.gx_offset = mpu_data.gx_offset / 300;
    mpu_data.gy_offset = mpu_data.gx_offset / 300;
    mpu_data.gz_offset = mpu_data.gz_offset / 300;
}

// 初始化mpu6500和ist3810
uint8_t IMU_Init(void)
{
    HAL_Delay(100);

    id = mpu_read_byte(MPU6500_ID);
    if (id != 0x70)
        return 1;
    uint8_t i = 0;
    uint8_t MPU6500_Init_Data[10][2] = {
        {MPU6500_PWR_MGMT_1, 0x80},     /* 重置设备*/
        {MPU6500_PWR_MGMT_1, 0x03},     /* 陀螺仪时钟源设置 */
        {MPU6500_PWR_MGMT_2, 0x00},     /* 启动 Acc & Gyro */
        {MPU6500_CONFIG, 0x04},         /* 低通滤波 频率41Hz */
        {MPU6500_GYRO_CONFIG, 0x18},    /* +-2000dps */
        {MPU6500_ACCEL_CONFIG, 0x10},   /* +-8G */
        {MPU6500_ACCEL_CONFIG_2, 0x02}, /* 使能低通滤波器  设置 Acc 低通滤波 */
        {MPU6500_USER_CTRL, 0x20},
    }; /* 使能 AUX */
    for (i = 0; i < 10; i++)
    {
        mpu_write_byte(MPU6500_Init_Data[i][0], MPU6500_Init_Data[i][1]);
        HAL_Delay(1);
    }

    mpu_set_gyro_fsr(3);
    mpu_set_accel_fsr(2);

    // ist8310_init();
    mpu_offset_call();
    return 0;
}

// 初始化四元数
void init_quaternion(void)
{
    int16_t hx, hy; // hz;

    hx = imu.mx;
    hy = imu.my;
    // hz = imu.mz;

#ifdef BOARD_DOWN
    if (hx < 0 && hy < 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = -0.005;
            q1 = -0.199;
            q2 = 0.979;
            q3 = -0.0089;
        }
        else
        {
            q0 = -0.008;
            q1 = -0.555;
            q2 = 0.83;
            q3 = -0.002;
        }
    }
    else if (hx < 0 && hy > 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = 0.005;
            q1 = -0.199;
            q2 = -0.978;
            q3 = 0.012;
        }
        else
        {
            q0 = 0.005;
            q1 = -0.553;
            q2 = -0.83;
            q3 = -0.0023;
        }
    }
    else if (hx > 0 && hy > 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = 0.0012;
            q1 = -0.978;
            q2 = -0.199;
            q3 = -0.005;
        }
        else
        {
            q0 = 0.0023;
            q1 = -0.83;
            q2 = -0.553;
            q3 = 0.0023;
        }
    }
    else if (hx > 0 && hy < 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = 0.0025;
            q1 = 0.978;
            q2 = -0.199;
            q3 = 0.008;
        }
        else
        {
            q0 = 0.0025;
            q1 = 0.83;
            q2 = -0.56;
            q3 = 0.0045;
        }
    }
#else
    if (hx < 0 && hy < 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = 0.195;
            q1 = -0.015;
            q2 = 0.0043;
            q3 = 0.979;
        }
        else
        {
            q0 = 0.555;
            q1 = -0.015;
            q2 = 0.006;
            q3 = 0.829;
        }
    }
    else if (hx < 0 && hy > 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = -0.193;
            q1 = -0.009;
            q2 = -0.006;
            q3 = 0.979;
        }
        else
        {
            q0 = -0.552;
            q1 = -0.0048;
            q2 = -0.0115;
            q3 = 0.8313;
        }
    }
    else if (hx > 0 && hy > 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = -0.9785;
            q1 = 0.008;
            q2 = -0.02;
            q3 = 0.195;
        }
        else
        {
            q0 = -0.9828;
            q1 = 0.002;
            q2 = -0.0167;
            q3 = 0.5557;
        }
    }
    else if (hx > 0 && hy < 0)
    {
        if (fabs(hx / hy) >= 1)
        {
            q0 = -0.979;
            q1 = 0.0116;
            q2 = -0.0167;
            q3 = -0.195;
        }
        else
        {
            q0 = -0.83;
            q1 = 0.014;
            q2 = -0.012;
            q3 = -0.556;
        }
    }
#endif
}

// 更新IMU数值
void imu_ahrs_update(void)
{
    float norm;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez, halfT;
    float tempq0, tempq1, tempq2, tempq3;

    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    gx = imu.wx;
    gy = imu.wy;
    gz = imu.wz;
    ax = imu.ax;
    ay = imu.ay;
    az = imu.az;
    mx = imu.mx;
    my = imu.my;
    mz = imu.mz;

    now_update = HAL_GetTick(); // ms
    halfT = ((float)(now_update - last_update) / 2000.0f);
    last_update = now_update;

    /* 快速逆平方根 */
    norm = inv_sqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

#ifdef IST8310
    norm = inv_sqrt(mx * mx + my * my + mz * mz);
    mx = mx * norm;
    my = my * norm;
    mz = mz * norm;
#else
    mx = 0;
    my = 0;
    mz = 0;
#endif
    /* 计算通量的参考方向*/
    hx = 2.0f * mx * (0.5f - q2q2 - q3q3) + 2.0f * my * (q1q2 - q0q3) + 2.0f * mz * (q1q3 + q0q2);
    hy = 2.0f * mx * (q1q2 + q0q3) + 2.0f * my * (0.5f - q1q1 - q3q3) + 2.0f * mz * (q2q3 - q0q1);
    hz = 2.0f * mx * (q1q3 - q0q2) + 2.0f * my * (q2q3 + q0q1) + 2.0f * mz * (0.5f - q1q1 - q2q2);
    bx = sqrt((hx * hx) + (hy * hy));
    bz = hz;

    /* 估计重力和通量方向(v和w)   */
    vx = 2.0f * (q1q3 - q0q2);
    vy = 2.0f * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    wx = 2.0f * bx * (0.5f - q2q2 - q3q3) + 2.0f * bz * (q1q3 - q0q2);
    wy = 2.0f * bx * (q1q2 - q0q3) + 2.0f * bz * (q0q1 + q2q3);
    wz = 2.0f * bx * (q0q2 + q1q3) + 2.0f * bz * (0.5f - q1q1 - q2q2);

    /*
     * 误差是场的参考方向与传感器测量方向的叉积之和
     */
    ex = (ay * vz - az * vy) + (my * wz - mz * wy);
    ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
    ez = (ax * vy - ay * vx) + (mx * wy - my * wx);

    /* PI */
    if (ex != 0.0f && ey != 0.0f && ez != 0.0f)
    {
        exInt = exInt + ex * Ki * halfT;
        eyInt = eyInt + ey * Ki * halfT;
        ezInt = ezInt + ez * Ki * halfT;

        gx = gx + Kp * ex + exInt;
        gy = gy + Kp * ey + eyInt;
        gz = gz + Kp * ez + ezInt;
    }

    tempq0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    tempq1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    tempq2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    tempq3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    /*将四元数标准化 */
    norm = inv_sqrt(tempq0 * tempq0 + tempq1 * tempq1 + tempq2 * tempq2 + tempq3 * tempq3);
    q0 = tempq0 * norm;
    q1 = tempq1 * norm;
    q2 = tempq2 * norm;
    q3 = tempq3 * norm;
}

// 更新imu的态度
void imu_attitude_update(void)
{
    /* yaw    -pi----pi */
    imu.yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 57.3;
    /* pitch  -pi/2----pi/2 */
    imu.pit = -asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;
    /* roll   -pi----pi  */
    imu.rol = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;
}
