/*
 * MPU6050.h
 *
 *  Created on: Nov 19, 2024
 *      Author: arsen
 */

#ifndef INC_MPU6050_H_
#include "main.h"
#define INC_MPU6050_H_

#define MPU6050_ADDR 0xD0

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

#define MPU_SET_TIMEOUT 1000
#define MPU_REG_SIZE 1
#define MPU_MEMADD_SIZE 1

typedef struct{
	uint16_t x, y, z;
} Vector3;
void MPU6050_Init(I2C_HandleTypeDef* hi2c);


#endif /* INC_MPU6050_H_ */
