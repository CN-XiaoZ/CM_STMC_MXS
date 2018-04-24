#include "GM65.h"
#include "./sys_config.h"
/** 
 * 二进制码表
 * 1
 * 地址:0x0000 标志:01111101 0x7D
 * 关闭LED 开启声音 开启照明 开启瞄准 命令触发模式
 * 命令触发模式下，识读模块接受到主机发送的扫描指令后开始读码
 * 扫描指令：在0x0002的bit0写入1
 * GM65_WriteCommand(0x0002,0x41);
 * 或者串口发送：7E 00 08 01 00 02 01 AB CD
 * 模块输出七字节回应信息：02 00 00 01 00 33 31
 * 然后开始扫描
 * 
 * 地址:0x0000 标志:01111111 0x7F
 * 关闭LED 开启声音 开启照明 开启瞄准 感应模式
 * 
 * 2
 * 地址:0x0002 标志:01000000 0x40
 * 输出解码提示符
 * 
 * 3
 * 地址:0x0003 标志:00000010 0x02
 * 关闭设置二维码
 * 
 * 4
 * 地址:0x0006 标志:11001000 0xC8
 * 设定读像时长20S
 * 
 * 5
 * 地址:0x000D 标志:00000100 0x04
 * 设定UNICODE 并串口输出
 * 
 * 6
 * 地址:0x000E 标志:00100000 0x20
 * 开启解码成功提示音
 * 
 * 7
 * 地址:0x002B 标志:00000000 0x00
 * 地址:0x002A 标志:00000000 0x1A
 * 设置波特率为115200
 * 
 * 8
 * 地址:0x002C 标志:00000011 0x03
 * 允许识读所有条码,并打开360°可读取模式
 * 
 * 9
 * 地址:0x0060 标志:00111001 0x3A
 * 数据接结束符CRLF(0x0D,0x0A),不加后缀CodeID,允许前缀和RF信息
 * 
 * 10
 * 地址:0x0062 标志:00100000 0x20
 * 前缀长度两字符
 * 
 * 11
 * 地址:0x0063 标志:11111111 0xFF
 * 地址:0x0064 标志:11111111 0xFF
 * 前缀字符FF
 * 
 * 12
 * 地址:0x0081 标志:00000010 0x02
 * RF信息长度2字符
 * 
 * 13
 * 地址:0x0082 标志:11011100 0xDC
 * 地址:0x0083 标志:10111010 0xBA
 * 
 * 14
 * 地址:0x00D9 标志:01010101 0x55
 * 恢复出厂设置
 */
void GM65_Init(void)
{
    GM65_WriteCommand(0x0000,0x7D);//1
	delay_ms(100);
    GM65_WriteCommand(0x0002,0x40);//2
	delay_ms(100);
    GM65_WriteCommand(0x0003,0x02);//3
	delay_ms(100);
    GM65_WriteCommand(0x0006,0xC8);//4
	delay_ms(100);
    GM65_WriteCommand(0x000D,0x04);//5
	delay_ms(100);
    GM65_WriteCommand(0x000E,0x20);//6
	delay_ms(100);
    GM65_WriteCommand(0x002C,0x03);//8
	delay_ms(100);
    GM65_WriteCommand(0x0060,0x3A);//9
	delay_ms(100);
    GM65_WriteCommand(0x0062,0x20);//10
	delay_ms(100);
    GM65_WriteCommand(0x0063,0xFF);//11
	delay_ms(100);
    GM65_WriteCommand(0x0064,0xFF);//11
	delay_ms(100);
    GM65_WriteCommand(0x0081,0x02);//12
	delay_ms(100);
    GM65_WriteCommand(0x0082,0xDC);//13
	delay_ms(100);
    GM65_WriteCommand(0x0083,0xBA);//13
	delay_ms(100);
    GM65_SaveCommand();
}

void GM65_RESET(void)
{
    GM65_WriteCommand(0x00D9,0x55);
    delay_ms(1000);
    GM65_Init();
}

void GM65_Send(uint8_t *command)
{
    int count;
    for (count = 0; count < 9; count++)
    {
        USART_SendData(UART4, command[count]);
        while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);/* 等待发送完毕 */
    }
}

void GM65_SCAN(void)
{
}

void GM65_ReadCommand(uint16_t Address, uint8_t Data)
{
    uint8_t command[9];
    command[0] = 0x7E;
    command[1] = 0x00;
    command[2] = 0x07;
    command[3] = 0x01;
    command[4] = (uint8_t)(Address >> 8);
    command[5] = (uint8_t)(Address & 0x00FF);
    command[6] = Data;
    command[7] = 0xAB;
    command[8] = 0xCD;
    GM65_Send(command);
}

void GM65_WriteCommand(uint16_t Address, uint8_t Data)
{
    uint8_t command[9];
    command[0]=0x7E;                            //head_high
    command[1]=0x00;                            //head_low
    command[2]=0x08;                            //types
    command[3]=0x01;                            //lens
    command[4]=(uint8_t)(Address>>8);           //address_high
    command[5]=(uint8_t)(Address&0x00FF);       //address_low
    command[6]=Data;                            //datas
    command[7]=0xAB;                            //crc_high
    command[8]=0xCD;                            //crc_low,set ABCD to pass crc
    GM65_Send(command);
}

void GM65_SaveCommand(void)
{
    uint8_t command[9]={0x7E,0x00,0x09,0x01,0x00,0x00,0x00,0xDE,0xC8};
    GM65_Send(command);
}
