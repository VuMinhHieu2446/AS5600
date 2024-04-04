/*
 * as5600.c
 *
 *  Created on: Mar 26, 2021
 *      Author: HoanTV
 */
#include "as5600.h"
#include "string.h"

//	properties
I2C_HandleTypeDef hi2c;
HAL_StatusTypeDef halStatus;
//	functions
void AS5600_WriteRegister(uint8_t Reg, uint8_t Data);
uint8_t AS5600_ReadRegister(uint8_t Reg, I2C_HandleTypeDef i2cHandleTypeDef);

//void resetI2C();

void AS5600_Init(I2C_HandleTypeDef i2cHandleTypeDef) {
	memcpy(&hi2c, &i2cHandleTypeDef, sizeof(i2cHandleTypeDef));
}

void AS5600_WriteRegister(uint8_t Reg, uint8_t Data) {
	halStatus = HAL_I2C_Master_Transmit(&hi2c, (AS5600_ADDR << 1), &Data, 1,
			10);
	halStatus = HAL_I2C_Mem_Write(&hi2c, (AS5600_ADDR << 1), Reg, 1, &Data, 1,
			100);
	if (halStatus != HAL_OK) {
		AS5600_ResetI2C();
	}
}

uint8_t AS5600_ReadRegister(uint8_t Reg, I2C_HandleTypeDef __i2cHandleTypeDef) {
	uint8_t DataRead = 0;
	halStatus = HAL_I2C_Mem_Read(&__i2cHandleTypeDef, (AS5600_ADDR << 1), Reg, 1, &DataRead,
			1, 100);
	return DataRead;
}


uint8_t AS5600_GetStatus(I2C_HandleTypeDef i2cHandleTypeDef) {
	return AS5600_ReadRegister(STATUS, i2cHandleTypeDef) & 0x38;
}

uint16_t AS5600_GetAngle(I2C_HandleTypeDef i2cHandleTypeDef) {
	return (int) ((float) (AS5600_ReadRegister(ANGLE_L, i2cHandleTypeDef)
			+ (AS5600_ReadRegister(ANGLE_H, i2cHandleTypeDef) << 8)) / 4096 * 360);
}
/*
void AS5600_SetHystheresis(uint8_t Hyst) {
	uint8_t TmpConfHigh = AS5600_ReadRegister(CONF_H);
	TmpConfHigh |= (HYST_MASK & Hyst);
	AS5600_WriteRegister(CONF_H, TmpConfHigh);
}

void AS5600_SetOutputStage(uint8_t OutStage) {
	uint8_t TmpConfLow = 0;
	TmpConfLow= AS5600_ReadRegister(CONF_L);
	TmpConfLow |= (OUT_STG_MASK & OutStage);
	AS5600_WriteRegister(CONF_L, TmpConfLow);
	TmpConfLow = 0;
	TmpConfLow= AS5600_ReadRegister(CONF_L);

}

void AS5600_SetPWMFreq(uint8_t Freq) {
	uint8_t TmpConfLow = AS5600_ReadRegister(CONF_L);
	TmpConfLow |= (PWMF_MASK & Freq);
	AS5600_WriteRegister(CONF_L, TmpConfLow);
}

uint16_t AS5600_GetPosition() {
	return (uint16_t) (AS5600_ReadRegister(RAWANG_L)
			+ (AS5600_ReadRegister(RAWANG_H) << 8));
}

uint16_t AS5600_GetStartPosition(void) {
	return (uint16_t) (AS5600_ReadRegister(ZPOS_L)
			+ (AS5600_ReadRegister(ZPOS_H) << 8));
}

uint16_t AS5600_GetStopPosition(void) {
	return (uint16_t) (AS5600_ReadRegister(MPOS_L)
			+ (AS5600_ReadRegister(MPOS_H) << 8));
}
*/
uint16_t AS5600_SetStartPosition(uint16_t value) {
//	uint16_t startPosition = getPosition();
	AS5600_WriteRegister(ZPOS_H, HIBYTE(value));
	HAL_Delay(2);
	AS5600_WriteRegister(ZPOS_L, LOBYTE(value));
	HAL_Delay(2);
	return AS5600_GetStartPosition();
}

uint16_t AS5600_SetStopPosition(uint16_t value) {
//	uint16_t stopPosition = getPosition();
	AS5600_WriteRegister(MPOS_H, HIBYTE(value));
	HAL_Delay(2);
	AS5600_WriteRegister(MPOS_L, LOBYTE(value));
	HAL_Delay(2);
	return AS5600_GetStopPosition();
}

void AS5600_BurnPosition(void) {
	if (AS5600_GetStartPosition() != 0 && AS5600_GetStopPosition() != 0
			&& AS5600_GetBurnCount() <= 2) {
		AS5600_WriteRegister(BURN, 0x80);
		HAL_Delay(2);
	}
}

void AS5600_VerifyBurnCommand(void) {
	AS5600_WriteRegister(BURN, 0x01);
	HAL_Delay(2);
	AS5600_WriteRegister(BURN, 0x11);
	HAL_Delay(2);
	AS5600_WriteRegister(BURN, 0x10);
	HAL_Delay(2);
}
/*
uint8_t AS5600_GetBurnCount(void) {
	return AS5600_ReadRegister(ZMCO);
}

uint8_t AS5600_SetOutPut(uint8_t mode) {
	uint8_t config_status;
	config_status = AS5600_ReadRegister(CONF_L);
	if (mode == 1) {
		config_status = config_status & 0xcf;
	} else {
		config_status = config_status & 0xef;
	}
	AS5600_WriteRegister(CONF_L, config_status);
	HAL_Delay(2);
	return AS5600_ReadRegister(CONF_L);
}
*/

void AS5600_ResetI2C(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}



