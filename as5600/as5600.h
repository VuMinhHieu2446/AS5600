/*
 * as5600.h
 *
 *  Created on: Mar 26, 2021
 *      Author: HoanTV
 */

#ifndef AS5600_AS5600_H_
#define AS5600_AS5600_H_

#include "stm32f4xx_hal.h"

#define LOBYTE(x)  ((uint8_t)((x) & 0x00FFU))
#define HIBYTE(x)  ((uint8_t)(((x) & 0xFF00U) >> 8U))

#define I2C_SCL_PORT GPIOB
#define I2C_SDA_PORT GPIOB
#define I2C_SCL_PIN GPIO_PIN_6
#define I2C_SDA_PIN GPIO_PIN_7

#define AS5600_ADDR	0x36		// Address on the bus

// Description of AS5600 register addresses

#define ZMCO		0x00
#define ZPOS_H		0x01		// Start position
#define ZPOS_L		0x02
#define MPOS_H		0x03		// Stop position
#define MPOS_L		0x04
#define MANG_H		0x05
#define MANG_L		0x06
#define CONF_H		0x07
#define CONF_L		0x08

#define	RAWANG_H	0x0C		// Raw Angle
#define RAWANG_L	0x0D
#define ANGLE_H		0x0E		// Angle of rotation
#define ANGLE_L		0x0F

#define STATUS		0x0b
#define AGC			0x1A
#define MAGN_H		0x1B
#define MAGN_L		0x1C

#define BURN		0xFF

// Description of bit masks of registers

#define	CONF_L_PM			0x03		// Power mode: 00 = NOM, 01 = LPM1, 10 = LPM2, 11 = LPM3
#define CONF_H_SF			0x03		// Noise filter slowness: 00 = 16x (1); 01 = 8x; 10 = 4x; 11 = 2x
#define CONF_H_FTH			0x1C		// Threshold of the "fast" filter
#define CONF_H_WD			0x20		// Watchdog

// Description of service constants

#define	MAGNET_LOW	0x10
#define MAGNET_HIGH	0x20
#define MAGNET_NORM 0x30

#define HYST_MASK		0x0C
#define HYST_OFF		0x00
#define HYST_1LSB		0x04
#define HYST_2LSB		0x08
#define HYST_3LSB		0x0C

#define	OUT_STG_MASK				0x30
#define	OUT_STG_ANALOG				0x00
#define OUT_STG_ANALOG_RED			0x10
#define	OUT_STG_PWM					0x20

#define PWMF_MASK					0xC0
#define PWMF_115HZ					0x00
#define	PWMF_230HZ					0x40
#define	PWMF_460HZ					0x80
#define PWMF_920HZ					0xC0




void AS5600_Init(I2C_HandleTypeDef i2cHandleTypeDef);
void AS5600_ResetI2C();

uint16_t AS5600_GetAngle(I2C_HandleTypeDef i2cHandleTypeDef);
uint16_t AS5600_GetPosition(void);
uint16_t AS5600_GetStartPosition(void);
uint16_t AS5600_GetStopPosition(void);
uint16_t AS5600_SetStartPosition(uint16_t value);
uint16_t AS5600_SetStopPosition(uint16_t value);
uint8_t AS5600_GetStatus(I2C_HandleTypeDef i2cHandleTypeDef);
void AS5600_BurnPosition(void);
void AS5600_VerifyBurnCommand(void);
uint8_t AS5600_GetBurnCount(void);
void AS5600_SetHystheresis(uint8_t Hyst);
void AS5600_SetOutputStage(uint8_t OutStage);
void AS5600_SetPWMFreq(uint8_t Freq);
uint8_t AS5600_DetectMagnet(void);
uint8_t AS5600_SetOutPut(uint8_t mode);

void AS5600_WriteRegister(uint8_t Reg, uint8_t Data);
uint8_t AS5600_ReadRegister(uint8_t Reg, I2C_HandleTypeDef i2cHandleTypeDef);

#endif /* AS5600_AS5600_H_ */
