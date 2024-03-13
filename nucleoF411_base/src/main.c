#include "TSL2561/inc/opto.h"
#include "stm32f4xx_hal_msp.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_i2c.h"
#include "leds.h"
#include "sw.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

TIM_HandleTypeDef htim5;
UART_HandleTypeDef huart2;
I2C_HandleTypeDef hi2c1;

#define BUF_SIZE 10
#define OPTO_ADDRESS 0x6a

char buf[10];
char uart2_buffer[BUF_SIZE];
uint32_t p_wr=0;
uint32_t p_rd=0;

//===========================================================
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	}
}
//============================================================
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char c;

    if(huart == &huart2)
    {
        c = huart2.Instance->DR;
        uart2_buffer[(p_wr++)%BUF_SIZE] = c; // % : operateur modulo : reste de la division


    }
}
//============================================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

}
//============================================================
int main()
{
	HAL_Init();
	HAL_MspInit(); // Initialisation des Broches

	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 400000;
	HAL_I2C_Init(&hi2c1);

	huart2.Instance          = USART2;
	huart2.Init.BaudRate     = 115200;
	huart2.Init.WordLength   = UART_WORDLENGTH_8B;
	huart2.Init.StopBits     = UART_STOPBITS_1;
	huart2.Init.Parity       = UART_PARITY_NONE;
	HAL_UART_Init(&huart2);

	HAL_UART_Receive_IT(&huart2, buf, 1);

	opto_init();

	int opto = 0;
	float lux=0.0;

while(1)
		{

			//opto_read(&opto);
			//lux = (float)opto;
			//uart_printf(&huart2, "Lumière (LUX): %f\n\r", lux);

			//HAL_Delay(500);
	int id;
	int ac_x1;
	int ac_x2;
	int ac_y1;
	int ac_y2;
	int ac_z1;
	int ac_z2;

	int ge_x1;
	int ge_x2;
	int ge_y1;
	int ge_y2;
	int ge_z1;
	int ge_z2;

	id = Ac_read_id();

	ac_x1=ac_read_x1();
	ac_x2=ac_read_x2();
	ac_y1=ac_read_y1();
	ac_y2=ac_read_y2();
	ac_z1=ac_read_z1();
	ac_z2=ac_read_z2();

	ge_x1=ge_read_x1();
	ge_x2=ge_read_x2();
	ge_y1=ge_read_y1();
	ge_y2=ge_read_y2();
	ge_z1=ge_read_z1();
	ge_z2=ge_read_z2();


	HAL_Delay(500);

	uart_printf(&huart2, "id  : %d", id);

	uart_printf(&huart2, "ac_x1:%d    ac_x2:%d    ac_y1:%d    ac_y2:%d       ac_z1:%d       ac_z2:%d    ge_x1:%d   ge_x2:%d    ge_y1:%d   ge_y2:%d    ge_z1:%d   ge_z2:%d ",ac_x1,ac_x2,ac_y1,ac_y2,ac_z1,ac_z2,ge_x1,ge_x2,ge_y1,ge_y2,ge_z1,ge_z2 );




		}

	return 0;
}
//============================================================





