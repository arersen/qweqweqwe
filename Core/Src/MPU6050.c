/*
 * MPU6050.c
 *
 *  Created on: Nov 19, 2024
 *      Author: arsen
 */


#include "MPU6050.h"

typedef struct{
	double x, y, z;
} Vector3;

typedef struct{
	uint16_t x, y, z;
} u16vec3;

I2C_HandleTypeDef* hi2c;

void MPU6050_Write(uint16_t MemAddress, uint8_t *pData, uint16_t Size){
	HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MemAddress, MPU_MEMADD_SIZE, pData, Size, MPU_SET_TIMEOUT);
}

void MPU6050_Read(uint16_t MemAddress, uint8_t *pData,  uint16_t Size){
	HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MemAddress, MPU_MEMADD_SIZE, pData, Size, MPU_SET_TIMEOUT);
}

void MPU6050_Init(I2C_HandleTypeDef* hi2c_target){
	uint8_t check, data;
	hi2c = hi2c_target;

	MPU6050_Read(WHO_AM_I_REG, &check, 1);
	if(check == 104){
		data = 0;
		MPU6050_Write(PWR_MGMT_1_REG, &data, 1);

		data = 0x07; // Data rate 1 KHz
		MPU6050_Write(SMPLRT_DIV_REG, &data, 1);

		data = 0x00;
		MPU6050_Write(ACCEL_CONFIG_REG, &data, 1);

		data = 0x00;
		MPU6050_Write(GYRO_CONFIG_REG, &data, 1);



	}

}


void MPU6050_Read_Accel(Vector3* pAccel){
	u16vec3 pAccelRAW;

	MPU6050_Read(ACCEL_XOUT_H_REG, (uint8_t*)&pAccelRAW, sizeof(pAccelRAW));

	pAccel->x = (double)pAccelRAW.x / 16384.0;
	pAccel->y = (double)pAccelRAW.y / 16384.0;
	pAccel->z = (double)pAccelRAW.z / 16384.0;

}

void MPU6050_Read_Gyro(Vector3* pGyro){
	u16vec3 pGyroRAW;

	MPU6050_Read(GYRO_XOUT_H_REG, (uint8_t*)&pGyroRAW, sizeof(pGyroRAW));

	pGyro->x = (double)pGyroRAW.x / 131.0;
	pGyro->y = (double)pGyroRAW.y / 131.0;
	pGyro->z = (double)pGyroRAW.z / 131.0;

}
