#include "Components/MPU6050.h"

MPUData* Initialize(I2C_HandleTypeDef *I2Cx, uint8_t IsFirst, uint8_t LowerPowerMode) {
    MPUData MPU6050Information;

    uint8_t check;
    MPU6050Information.MPU_ADDRESS = IsFirst ? 0x68 : 0x69;
    HAL_I2C_Mem_Read(I2Cx, MPU6050Information.MPU_ADDRESS << 1, WHO_AM_I, 1, &check, 1, 100);
    if (check != MPU6050Information.MPU_ADDRESS) return NULL;

    // Set Power Management Mode
    uint8_t Power2 = LowerPowerMode ? 0b00111111 : 0;
    HAL_I2C_Mem_Write(I2Cx, MPU6050Information.MPU_ADDRESS << 1, PWR_MGMT_1, 1, 0b00100000, 1, 100);
    HAL_I2C_Mem_Write(I2Cx, MPU6050Information.MPU_ADDRESS << 1, PWR_MGMT_2, 1, &Power2, 1, 100);

    // Disable FIFO
    HAL_I2C_Mem_Write(I2Cx, MPU6050Information.MPU_ADDRESS << 1, FIFO_EN, 1, 0, 1, 100); // Turns off FIFO Buffer
    // Setup Sample Rate
    HAL_I2C_Mem_Write(I2Cx, MPU6050Information.MPU_ADDRESS << 1, SMPLRT_DIV, 1, SAMPLE_RATE, 1, 100); // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    // Config Acceleroemter and Gyroscope
    HAL_I2C_Mem_Write(I2Cx, MPU6050Information.MPU_ADDRESS << 1, ACCEL_CONFIG, 1, 0, 1, 100); // Set Bit 3-4 as 0 for range of +/- 2g
    HAL_I2C_Mem_Write(I2Cx, MPU6050Information.MPU_ADDRESS << 1, GYRO_CONFIG, 1, 0, 1, 100); // Set Bit 3-4 as 0 for Range for +/- 250 degrees/s
    
    MPU6050Information.AccelLSBSensitivity = ACCEL_CONFIG >> 3;
    MPU6050Information.GyroLSBSensitivity = GYRO_CONFIG >> 3;
    
    if (MPU6050Information.AccelLSBSensitivity == 0) MPU6050Information.AccelLSBSensitivity = 16384;
    else if (MPU6050Information.AccelLSBSensitivity == 1) MPU6050Information.AccelLSBSensitivity = 8192;
    else if (MPU6050Information.AccelLSBSensitivity == 2) MPU6050Information.AccelLSBSensitivity = 4096;
    else if (MPU6050Information.AccelLSBSensitivity == 3) MPU6050Information.AccelLSBSensitivity = 2048;

    if (MPU6050Information.GyroLSBSensitivity == 0)  MPU6050Information.GyroLSBSensitivity = 131;
    else if (MPU6050Information.GyroLSBSensitivity == 1) MPU6050Information.GyroLSBSensitivity = 65.5;
    else if (MPU6050Information.GyroLSBSensitivity == 2) MPU6050Information.GyroLSBSensitivity = 32.8;
    else if (MPU6050Information.GyroLSBSensitivity == 3) MPU6050Information.GyroLSBSensitivity = 16.4;

    MPU6050Information.I2C = I2Cx;
    return &MPU6050Information;
}
// Actual = Raw / GyroLSBSensitivity
void ReadGyro(MPUData *MPU6050Information) {
    uint8_t GyroData[6];
    HAL_I2C_Mem_Read(MPU6050Information->I2C, MPU6050Information->MPU_ADDRESS, GYRO_XOUT_H, 1, GyroData, 6, 100);
    MPU6050Information->GyroX = (GyroData[0] << 8 | GyroData[1]) / MPU6050Information->GyroLSBSensitivity;
    MPU6050Information->GyroY = (GyroData[2] << 8 | GyroData[3]) / MPU6050Information->GyroLSBSensitivity;
    MPU6050Information->GyroZ = (GyroData[4] << 8 | GyroData[5]) / MPU6050Information->GyroLSBSensitivity;
}

// Actual = Raw / AccelLSBSensitivity
void ReadAccel(MPUData *MPU6050Information) {
    uint8_t AccelData[6];
    HAL_I2C_Mem_Read(MPU6050Information->I2C, MPU6050Information->MPU_ADDRESS, ACCEL_XOUT_H, 1, AccelData, 6, 100);
    MPU6050Information->AccelX = (AccelData[0] << 8 | AccelData[1]) / MPU6050Information->AccelLSBSensitivity;
    MPU6050Information->AccelY = (AccelData[2] << 8 | AccelData[3]) / MPU6050Information->AccelLSBSensitivity;
    MPU6050Information->AccelZ = (AccelData[4] << 8 | AccelData[5]) / MPU6050Information->AccelLSBSensitivity;
}

// Actual = Raw / 340 + 36.53
void ReadTemp(MPUData *MPU6050Information) {
    uint8_t TempData[2];
    HAL_I2C_Mem_Read(MPU6050Information->I2C, MPU6050Information->MPU_ADDRESS, TEMP_OUT_H, 1, TempData, 2, 100);
    MPU6050Information->Temperature = (TempData[0] << 8 | TempData[1]) / 340.0 + 36.53;
}

void ReadAll(MPUData *MPU6050Information) {
    ReadGyro(&MPU6050Information);
    ReadAccel(&MPU6050Information);
    ReadTemp(&MPU6050Information);
}