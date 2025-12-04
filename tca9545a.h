/*
 * tca9545a.h
 *
 *  Created on: Sep 23, 2025
 *      Author: shanhao
 */

#ifndef INC_TCA9545A_H_
#define INC_TCA9545A_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "main.h"

//addr: 1-1-1-0-0-A1-A0-R/W
#define TCA9545_ADDR_WRITE      0xE0
#define TCA9545_ADDR_READ       0xE1

/**
 * control_register INT3-INT2-INT1-INT0-B3-B2-B1-B0
 * 中断只读，低有效，b3为通道3，高电平有效，可读写
 */
#define TCA9545_CHANNEL_NONE            0x0
#define TCA9545_CHANNEL0                0x1
#define TCA9545_CHANNEL1                0x2
#define TCA9545_CHANNEL2                0x4
#define TCA9545_CHANNEL3                0x8

#define TCA9545_RESET_ENABLE()            HAL_GPIO_WritePin(TCA9545_RESET_GPIO_Port, TCA9545_RESET_Pin, GPIO_PIN_RESET)
#define TCA9545_RESET_DISABLE()           HAL_GPIO_WritePin(TCA9545_RESET_GPIO_Port, TCA9545_RESET_Pin, GPIO_PIN_SET)

void temp_measure_init();
uint8_t temp_measure_channel(uint8_t channel);

#endif /* INC_TCA9545A_H_ */
