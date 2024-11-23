/*
 * MPU6050.c
 *
 *  Created on: Nov 19, 2024
 *      Author: arsen
 */


#include "MPU6050.h"



I2C_HandleTypeDef* hi2c;

HAL_StatusTypeDef MPU6050_Write(uint16_t MemAddress, uint8_t *pData, uint16_t Size){
	return HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MemAddress, MPU_MEMADD_SIZE, pData, Size, MPU_SET_TIMEOUT);
}

HAL_StatusTypeDef MPU6050_Read(uint16_t MemAddress, uint8_t *pData,  uint16_t Size){
	return HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MemAddress, MPU_MEMADD_SIZE, pData, Size, MPU_SET_TIMEOUT);
}

MPU6050_Init_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef* hi2c_target){
	MPU6050_Init_StatusTypeDef status;
	uint8_t data;

	hi2c = hi2c_target;

	status.WHO_AM_I =  MPU6050_Read(WHO_AM_I_REG, &status.check, 1);

	if(status.check == 104){
		data = 0;
		status.PWR_MGMT_1 = MPU6050_Write(PWR_MGMT_1_REG, &data, 1);

		data = 0x07; // Data rate 1 KHz
		status.SMPLRT_DIV = MPU6050_Write(SMPLRT_DIV_REG, &data, 1);

		data = 0x00; // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
		status.ACCEL_CONFIG = MPU6050_Write(ACCEL_CONFIG_REG, &data, 1);


		data = 0x00; // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 ̐/s
		status.GYRO_CONFIG = MPU6050_Write(GYRO_CONFIG_REG, &data, 1);



	}

	return status;

}


HAL_StatusTypeDef MPU6050_Read_Accel(Vector3* pAccel){
	u16vec3 AccelRAW;

	HAL_StatusTypeDef HAL_Status = MPU6050_Read(ACCEL_XOUT_H_REG, (uint8_t*)&AccelRAW, sizeof(AccelRAW));

	pAccel->x = AccelRAW.x / 16384.0;
	pAccel->y = AccelRAW.y / 16384.0;
	pAccel->z = AccelRAW.z / 16384.0;

	return HAL_Status;
}

HAL_StatusTypeDef MPU6050_Read_Gyro(Vector3* pGyro){
	u16vec3 GyroRAW;

	HAL_StatusTypeDef HAL_Status = MPU6050_Read(GYRO_XOUT_H_REG, (uint8_t*)&GyroRAW, sizeof(GyroRAW));

	pGyro->x = GyroRAW.x / 131.0;
	pGyro->y = GyroRAW.y / 131.0;
	pGyro->z = GyroRAW.z / 131.0;

	return HAL_Status;

}
