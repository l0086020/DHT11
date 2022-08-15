#include "main.h"

/**
  * @brief  DHT11_GPIO��ʼ������
  * @param  Mode��ָ����������ģʽ
  * @return None
  */
void DHT_GPIO_Init(GPIOMode_TypeDef Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DHT_RCC_PORT,ENABLE);
	
	GPIO_SetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);
	
	GPIO_InitStructure.GPIO_Mode = Mode;
	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DHT_GPIO_PORT,&GPIO_InitStructure);
}

/**
  * @brief  DHT11ģ����ʼ�źź���
  * @param  None
  * @return 1��0����־���źųɹ����
  */
uint8_t DHT_Start(void)
{
	DHT_GPIO_Init(GPIO_Mode_Out_PP);							//���ģʽ
	
	GPIO_ResetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);		//���20ms�͵�ƽ������
	delay_ms(20);
	GPIO_SetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);
	
	DHT_GPIO_Init(GPIO_Mode_IN_FLOATING);					//����ģʽ
	delay_us(20);
	
	if(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN))
	{
		while(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		return 1;
	}
	return 0;
}

/**
  * @brief  ����DHT11������8λ������
  * @param  None
  * @return ���ؽ��յ���8λ����
  */
uint8_t DHT_Get_Byte_Data(void)
{
	uint8_t temp;
	for(int i = 0; i < 8; i++)
	{
		temp <<= 1;
		while(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		delay_us(28);
		GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN) ? (temp |= 0x01) : (temp &= ~0x01);
		while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
	}
	return temp;
}

/**
  * @brief  ��ȡDHT11���¶�ʪ������
  * @param  buffer[]����Ҫ����һ���洢���ݵ�����
  * @return ��������У���Ƿ���ȷ 1����ȷ 0��ʧ��
  */
uint8_t DHT_Get_Temp_Humi_Data(uint8_t buffer[])
{
	if(DHT_Start())
	{
		buffer[0] = DHT_Get_Byte_Data();
		buffer[1] = DHT_Get_Byte_Data();
		buffer[2] = DHT_Get_Byte_Data();
		buffer[3] = DHT_Get_Byte_Data();
		buffer[4] = DHT_Get_Byte_Data();
	}
	return (buffer[0]+buffer[1]+buffer[2]+buffer[3] == buffer[4]) ? 1 : 0;
}
