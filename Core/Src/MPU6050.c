/*
 * MPU6050.c
 *
 *  Created on: Nov 19, 2024
 *      Author: arsen
 */


#include "MPU6050.h"

I2C_HandleTypeDef* hi2c;

void MPU6050_Write(uint16_t MemAddress, uint8_t *pData){
	HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MemAddress, MPU_MEMADD_SIZE, pData, MPU_SIZE, MPU_SET_TIMEOUT);
}

void MPU6050_Read(uint16_t MemAddress, uint8_t *pData){
	HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MemAddress, MPU_MEMADD_SIZE, pData, MPU_SIZE, MPU_SET_TIMEOUT);
}

void MPU6050_Init(I2C_HandleTypeDef* hi2c_target){
	uint8_t check, data;
	hi2c = hi2c_target;

	MPU6050_Read(WHO_AM_I_REG, &check);
	if(check == 104){
		data = 0;
		MPU6050_Write(PWR_MGMT_1_REG, &data);

		data = 0x07; // Data rate 1 KHz
		MPU6050_Write(SMPLRT_DIV_REG, &data);



	}

}
