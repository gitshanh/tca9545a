/*
 * tca9545a.c
 *
 *  Created on: Sep 23, 2025
 *      Author: shanhao
 */
#include "stm32f4xx.h"
#include "i2c.h"
#include "tca9545a.h"
#include "driver_amg8833_basic.h"

void tca9545_reset()
{
    TCA9545_RESET_ENABLE();
    HAL_Delay(10);
    TCA9545_RESET_DISABLE();
}

uint8_t tca9545_select_channel(uint8_t channel)
{
    if (HAL_I2C_Master_Transmit(&hi2c1, TCA9545_ADDR_WRITE, &channel, 1, 1000) == HAL_OK)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t tca9545_get_selected_channel(uint8_t *current_channel) {
    if (HAL_I2C_Master_Receive(&hi2c1, TCA9545_ADDR_READ, current_channel, 1, 1000) == HAL_OK)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void temp_measure_init()
{
    tca9545_reset();
    HAL_Delay(100);

    tca9545_select_channel(TCA9545_CHANNEL0);
    //读取一次通道选择，确认选择有效
//    uint8_t read_channel;
//    tca9545_get_selected_channel(&read_channel);
    amg8833_basic_init(&gs_handle0, AMG8833_ADDRESS_0);
    HAL_Delay(100);

    tca9545_select_channel(TCA9545_CHANNEL1);
    amg8833_basic_init(&gs_handle1, AMG8833_ADDRESS_0);
    HAL_Delay(100);

    tca9545_select_channel(TCA9545_CHANNEL2);
    amg8833_basic_init(&gs_handle2, AMG8833_ADDRESS_0);
    HAL_Delay(100);

    tca9545_select_channel(TCA9545_CHANNEL3);
    amg8833_basic_init(&gs_handle3, AMG8833_ADDRESS_0);
    HAL_Delay(100);
}

uint8_t temp_measure_channel(uint8_t channel)
{

    tca9545_select_channel(channel);

    uint8_t res;
    float temp[8][8];
    float tmp;

    /* read temperature */
    switch (channel)
    {
        case TCA9545_CHANNEL0:
            //选择读取温度或者8*8点阵温度
            res = amg8833_basic_read_temperature(&gs_handle0, (float *)&tmp);
            if (res == 0)
            {
                printf("AMG8833 CHANNEL 0: temp = %.2f\r\n", tmp);
            }
            res = amg8833_basic_read_temperature_array(&gs_handle0, temp);
            if (res == 0)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        printf("AMG8833 CHANNEL 0: temp[%d][%d] = %.2f\t", i, j, temp[i][j]);
                    }
                    printf("\r\n");
                }
            }
            break;
        case TCA9545_CHANNEL1:
            res = amg8833_basic_read_temperature(&gs_handle1, (float *)&tmp);
            if (res == 0)
            {
                printf("AMG8833 CHANNEL 1: temp = %.2f\r\n", tmp);
            }
            res = amg8833_basic_read_temperature_array(&gs_handle1, temp);
            if (res == 0)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        printf("AMG8833 CHANNEL 1: temp[%d][%d] = %.2f\t", i, j, temp[i][j]);
                    }
                    printf("\r\n");
                }
            }
            break;
        case TCA9545_CHANNEL2:
            res = amg8833_basic_read_temperature(&gs_handle2, (float *)&tmp);
            if (res == 0)
            {
                printf("AMG8833 CHANNEL 2: temp = %.2f\r\n", tmp);
            }
            res = amg8833_basic_read_temperature_array(&gs_handle2, temp);
            if (res == 0)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (i == 3 || i == 4)
                        {
                            if (j == 3 || j == 4)
                            {
                                printf("AMG8833 CHANNEL 2: temp[%d][%d] = %.2f\t", i, j, temp[i][j]);
                            }
                        }
                    }
                    printf("\r\n");
                }
            }
            break;
        case TCA9545_CHANNEL3:
            res = amg8833_basic_read_temperature(&gs_handle3, (float *)&tmp);
            if (res == 0)
            {
                printf("AMG8833 CHANNEL 3: temp = %.2f\r\n", tmp);
            }
            res = amg8833_basic_read_temperature_array(&gs_handle3, temp);
            if (res == 0)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        printf("AMG8833 CHANNEL 3: temp[%d][%d] = %.2f\t", i, j, temp[i][j]);
                    }
                    printf("\r\n");
                }
            }
            break;

        default:
            break;
    }

    return res;
}
