#include "oled.h"
#include "OLED_Font_Bmp.h"

//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	uint8_t i;
	if(cmd) OLED_DC_Set();
	else	OLED_DC_Clr();
	OLED_CS_Clr();
	for(i = 0;i < 8;i++)
	{
		OLED_SCLK_Clr();
		if(dat&0x80)	OLED_SDIN_Set();
		else	OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat <<= 1;
	}
	OLED_CS_Set();
	OLED_DC_Set();
}

//������ʾλ��
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}  

//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);
	OLED_WR_Byte(0x14,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD);
}

//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);
	OLED_WR_Byte(0x10,OLED_CMD);
	OLED_WR_Byte(0xAE,OLED_CMD);
}

//��������
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x02,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}

/*��ָ��λ����ʾһ���ַ������������ַ�
	x��0-127
	y��0-7
	mode��0.������ʾ��1.������ʾ��
	size��ѡ������16/12
*/
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';//�õ�ƫ�ƺ��ֵ			
	if(x>Max_Column-1){x=0;y=y+2;}
	if(SIZE ==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
		OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		
	}
}

unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}	

//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 	
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 

//��ʾһ���ַ���
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j]);
		x+=8;
		if(x>120){x=0;y+=2;}
		j++;
	}
}

//��ʾ����
void OLED_ShowChinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);	
	for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
		adder+=1;
	 }	
	OLED_Set_Pos(x,y+1);	
	for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
	}	
}
//��ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
	unsigned int j=0;
	unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 

//��ʼ��SSD1306
void OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO,ENABLE);
	
	//CS
	GPIO_InitStructure.GPIO_Pin = OLED_CS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_CS_GPIO,&GPIO_InitStructure);
	//DC
	GPIO_InitStructure.GPIO_Pin = OLED_DC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_DC_GPIO,&GPIO_InitStructure);
	//SCLK
	GPIO_InitStructure.GPIO_Pin = OLED_SCLK_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_SCLK_GPIO,&GPIO_InitStructure);
	//SDIN
	GPIO_InitStructure.GPIO_Pin = OLED_SDIN_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_SDIN_GPIO,&GPIO_InitStructure);
	
	GPIO_SetBits(OLED_CS_GPIO,OLED_CS_GPIO_PIN);
	GPIO_SetBits(OLED_DC_GPIO,OLED_DC_GPIO_PIN);
	GPIO_SetBits(OLED_SCLK_GPIO,OLED_SCLK_GPIO_PIN);
	GPIO_SetBits(OLED_SDIN_GPIO,OLED_SDIN_GPIO_PIN);
	
	OLED_WR_Byte(0xAE,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	OLED_WR_Byte(0x10,OLED_CMD);
	OLED_WR_Byte(0x40,OLED_CMD);
	
	OLED_WR_Byte(0x81,OLED_CMD);
	OLED_WR_Byte(0xCF,OLED_CMD);
	OLED_WR_Byte(0xA1,OLED_CMD);
	OLED_WR_Byte(0xC8,OLED_CMD);
	
	OLED_WR_Byte(0xA6,OLED_CMD);
	OLED_WR_Byte(0xA8,OLED_CMD);
	OLED_WR_Byte(0x3F,OLED_CMD);
	OLED_WR_Byte(0xD3,OLED_CMD);
	
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xD5,OLED_CMD);
	OLED_WR_Byte(0x80,OLED_CMD);
	OLED_WR_Byte(0xD9,OLED_CMD);
	
	OLED_WR_Byte(0xF1,OLED_CMD);
	OLED_WR_Byte(0xDA,OLED_CMD);
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);
	
	OLED_WR_Byte(0x40,OLED_CMD);
	OLED_WR_Byte(0x20,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	OLED_WR_Byte(0x8D,OLED_CMD);
	
	OLED_WR_Byte(0x14,OLED_CMD);
	OLED_WR_Byte(0xA4,OLED_CMD);
	OLED_WR_Byte(0xA6,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
	OLED_Set_Pos(0,0);
}
