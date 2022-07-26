#include "stm32f10x.h"
#include "oled.h"
#include "DHT11.h"
#include "stdio.h"

char str[50];

int main(void)
{
	uint8_t DataBuff[5];
	OLED_Init();
	while(1)
	{
		if(DHT_TEM_HUM_DATA(DataBuff))
		{
			sprintf(str,"Temp: %d.%d      Humi: %d.%d",DataBuff[2],DataBuff[3],DataBuff[0],DataBuff[1]);
			OLED_ShowString(24,2,(uint8_t *)str);
		}
		delay_ms(2000);
	}
}
