#include "TSL2561/inc/opto.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdio.h>
#include <math.h>

#define OPTO_ADDRESS 0x6a

extern I2C_HandleTypeDef hi2c1;

void opto_init()
{
  uint8_t data[2];

  data[0] = 0x18; //activation des axes linear acceleration sesnsor register
  data[1] = 0x3c; //Mode de mesure continu, temps d'intégration de 402 ms
  HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data, 2); // Envoi de données via I2C
  //HAL_Delay(100);

  uint8_t data1[2];
  data1[0] = 0x19; //control register
  data1[1] = 0x3c;
  HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data1, 2);

  uint8_t data2[2];
  data2[0] = 0x10;  //linear acceleration sensor control register parametre  +-8g
  data2[1] = 0x4c;
  HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data2, 2);

  uint8_t data3[2];
  data3[0] = 0x11; //angular rate sensor controle register parametre 2000dps
  data3[1] = 0x8e;
  HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data3, 2);


}
//int opto_read(int *opto)
int Ac_read_id()
{
	uint8_t data_send_ac=0x0f;
	uint8_t data_rec_ac[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_ac, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_ac, 1);

	// Analyse des données reçues

	int ret_value = (int)data_rec_ac[0];

	return ret_value;

}

int ac_read_x1()
{
	uint8_t data_send_acx1=0x29;
	uint8_t data_rec_acx1[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acx1, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acx1, 1);

	// Analyse des données reçues

	int ret_value_acx1 = (int)data_rec_acx1[0];

	return ret_value_acx1;

}

/*int ac_read_x()
{
	uint8_t data_send_acx[2];
	uint8_t data_rec_acx[2];

    data_send_acx[0]=0x29;
	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acx, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acx, 1);

    data_send_acx[1]=0x28;
    HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acx, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acx, 1);
	// Analyse des données reçues

	int ret_value_acx = ((int)data_rec_acx[0] <<8 | data_rec_acx[1] ;

	return ret_value_acx;

}*/


int ac_read_x2()
{
	uint8_t data_send_acx2=0x28;
	uint8_t data_rec_acx2[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acx2, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acx2, 1);

	// Analyse des données reçues

	int ret_value_acx2 = (int)data_rec_acx2[0];

	return ret_value_acx2;

}

int ac_read_y1()
{
	uint8_t data_send_acy1=0x2b;
	uint8_t data_rec_acy1[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acy1, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acy1, 1);

	// Analyse des données reçues

	int ret_value_acy1 = (int)data_rec_acy1[0];

	return ret_value_acy1;

}


int ac_read_y2()
{
	uint8_t data_send_acy2=0x2a;
	uint8_t data_rec_acy2[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acy2, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acy2, 1);

	// Analyse des données reçues

	int ret_value_acy2 = (int)data_rec_acy2[0];

	return ret_value_acy2;

}

int ac_read_z1()
{
	uint8_t data_send_acz1=0x2d;
	uint8_t data_rec_acz1[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acz1, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acz1, 1);

	// Analyse des données reçues

	int ret_value_acz1 = (int)data_rec_acz1[0];

	return ret_value_acz1;

}

int ac_read_z2()
{
	uint8_t data_send_acz2=0x2c;
	uint8_t data_rec_acz2[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_acz2, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_acz2, 1);

	// Analyse des données reçues

	int ret_value_acz2 = (int)data_rec_acz2[0];

	return ret_value_acz2;

}


int ge_read_x1()
{
	uint8_t data_send_gex1=0x23;
	uint8_t data_rec_agex1[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_gex1, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_agex1, 1);

	// Analyse des données reçues

	int ret_value_gex1 = (int)data_rec_agex1[0];

	return ret_value_gex1;

}

int ge_read_x2()
{
	uint8_t data_send_gex2=0x22;
	uint8_t data_rec_agex2[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_gex2, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_agex2, 1);

	// Analyse des données reçues

	int ret_value_gex1 = (int)data_rec_agex2[0];

	return ret_value_gex1;

}

int ge_read_y1()
{
	uint8_t data_send_gey1=0x25;
	uint8_t data_rec_agey1[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_gey1, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_agey1, 1);

	// Analyse des données reçues

	int ret_value_gey1 = (int)data_rec_agey1[0];

	return ret_value_gey1;

}

int ge_read_y2()
{
	uint8_t data_send_gey2=0x24;
	uint8_t data_rec_agey2[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_gey2, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_agey2, 1);

	// Analyse des données reçues

	int ret_value_gey2 = (int)data_rec_agey2[0];

	return ret_value_gey2;

}

int ge_read_z1()
{
	uint8_t data_send_gez1=0x27;
	uint8_t data_rec_agez1[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_gez1, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_agez1, 1);

	// Analyse des données reçues

	int ret_value_gez1 = (int)data_rec_agez1[0];

	return ret_value_gez1;

}

int ge_read_z2()
{
	uint8_t data_send_gez2=0x26;
	uint8_t data_rec_agez2[1];

	HAL_I2C_Master_Transmit_IT(&hi2c1, OPTO_ADDRESS, data_send_gez2, 1);
	HAL_I2C_Master_Receive_IT(&hi2c1, OPTO_ADDRESS, data_rec_agez2, 1);

	// Analyse des données reçues

	int ret_value_gez2 = (int)data_rec_agez2[0];

	return ret_value_gez2;

}

/*int ch0 = (int)rxbuf[1]<<8 + (int)rxbuf[0];
int ch1 = (int)rxbuf[2]<<8 + (int)rxbuf[3];

if (0<ch1/ch0<0.25)
	{
		*opto=(0.105*ch0)-(0.208*ch1);
	}
else if (0.25<ch1/ch0<0.38)
	{
		*opto=(0.1088*ch0)-(0.2231*ch1);
	}
else if (0.38<ch1/ch0<0.45)
	{
		*opto=(0.0729*ch0)-(0.1286*ch1);
	}
else if (0.45<ch1/ch0<0.60)
	{
		*opto=(0.060*ch0)-(0.10*ch1);
	}
else if (ch1/ch0>0.60)
	{
		*opto=0;
	}*/
