#include "DHT11.h"

uint8_t buff;

void DHT_GPIO_CONFIG(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = mode;;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
}

uint8_t DHT_START()
{
	DHT_GPIO_CONFIG(GPIO_Mode_Out_PP);
	GPIO_SetBits(GPIOG,GPIO_Pin_12);
	delay_us(2);
	
	GPIO_ResetBits(GPIOG,GPIO_Pin_12);
	delay_ms(20);
	GPIO_SetBits(GPIOG,GPIO_Pin_12);
	delay_us(30);
	
	DHT_GPIO_CONFIG(GPIO_Mode_IN_FLOATING);
	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12) == RESET)
	{
		while(!(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12)));
		while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12));
		return 1;
	}
	return 0;
}

void DHT_GET_DATA()
{
	for(uint8_t i = 0;i<8;i++)
	{
		buff = buff << 1;
		while(!(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12)));
		delay_us(30);
		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) ? (buff |= 0x01) : (buff &= ~0x01);
		while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12));
	}
}

uint8_t DHT_TEM_HUM_DATA(uint8_t DataBuff[])
{
	if(DHT_START())
	{
		DHT_GET_DATA();
		DataBuff[0] = buff;
		DHT_GET_DATA();
		DataBuff[1] = buff;
		DHT_GET_DATA();
		DataBuff[2] = buff;
		DHT_GET_DATA();
		DataBuff[3] = buff;
		DHT_GET_DATA();
		DataBuff[4] = buff;
	}
	if(DataBuff[4] == DataBuff[0]+DataBuff[1]+DataBuff[2]+DataBuff[3])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
