#include "main.h"

char str[20];

uint8_t DHT_Buffer[5];

int main(void)
{
	OLED_Init();
	while(1)
	{
		if(DHT_Get_Temp_Humi_Data(DHT_Buffer))
		{
			sprintf(str,"Temp:%d.%d",DHT_Buffer[2],DHT_Buffer[3]);
			OLED_ShowString(28,2,(uint8_t *)str);
			sprintf(str,"Humi:%d.%d",DHT_Buffer[0],DHT_Buffer[1]);
			OLED_ShowString(28,4,(uint8_t *)str);
		}
		delay_ms(2000);
	}
}
