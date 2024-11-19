/*
 * MPU6050.c
 *
 *  Created on: Nov 19, 2024
 *      Author: arsen
 */


#include "MPU6050.h"

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

	MPU6050_Read(WHO_AM_I_REG, &check);
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

void MPU6050_Read_Accel(Vector3* pAccelRAW){
	uint8_t Rec_Data[6];

	MPU6050_Read(ACCEL_XOUT_H_REG, Rec_Data, 6); // sizeof(Rec_Data)

	pAccelRAW->x = (uint16_t)(Rec_Data[0] << 8 | RecData[1]);
	pAccelRAW->y = (uint16_t)(Rec_Data[2] << 8 | RecData[3]);
	pAccelRAW->z = (uint16_t)(Rec_Data[4] << 8 | RecData[5]);
	

}

void MPU6050_Read_Gyro(Vector3* pGyroRAW){
	uint8_t Rec_Data[6];

	MPU6050_Read(GYRO_XOUT_H_REG, Rec_Data, 6); // sizeof(Rec_Data)

	pGyroRAW->x = (uint16_t)(Rec_Data[0] << 8 | RecData[1]);
	pGyroRAW->y = (uint16_t)(Rec_Data[2] << 8 | RecData[3]);
	pGyroRAW->z = (uint16_t)(Rec_Data[4] << 8 | RecData[5]);
	

}
