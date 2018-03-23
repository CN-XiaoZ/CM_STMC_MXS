#include "./scan/GM65.h"

/** 
 * 二进制码表
 * 地址:0x0000 标志:01010110 0x56
 * 关闭LED 开启声音 开启照明 开启瞄准 命令触发
 * 地址:0x0002 标志:00000010 0x02
 * 输出解码提示符
 * 地址:0x0003 标志:00000010 0x02
 * 关闭设置二维码
 * 地址:0x0006 标志:11001000 0xC8
 * 设定读像时长20S
 * 地址:0x000D 标志:00010000 0x10
 * 设定UNICODE 并串口输出
 * 地址:0x000E 标志:00100000 0x20
 * 开启解码成功提示音
 * 地址:0x002C 标志:10100000 0xA0
 * 允许识读所有条码,并打开360°可读取模式
 * 地址:0x0060 标志:10011010 0x9A
 * 数据接结束符CRLF(0x0D,0x0A),不加后缀CodeID,允许前缀和RF信息
 * 地址:0x0062 标志:00000010 0x02
 * 前缀长度两字符
 * 地址:0x0063 标志:11111111 0xFF
 * 地址:0x0064 标志:11111111 0xFF
 * 前缀字符FF
 * 地址:0x0081 标志:00100000 0x20
 * RF信息长度2字符
 * 地址:0x0082 标志:11011100 0xDC
 * 地址:0x0083 标志:10111010 0xBA
 * 
 * 地址:0x00D9 标志:01010101 0x55
 * 恢复出厂设置
 */
void GM65_SetDefault(void)
{
//    GM65_WriteCommand(0x0000,0x56);
//    GM65_WriteCommand(0x0002,0x02);
//    GM65_WriteCommand(0x0003,0x02);
//    GM65_WriteCommand(0x0006,0xC8);
//    GM65_WriteCommand(0x000D,0x10);
//    GM65_WriteCommand(0x000E,0x20);
//    GM65_WriteCommand(0x002C,0xA0);
//    GM65_WriteCommand(0x0060,0x9A);
//    GM65_WriteCommand(0x0062,0x02);
//    GM65_WriteCommand(0x0063,0xFF);
//    GM65_WriteCommand(0x0064,0xFF);
//    GM65_WriteCommand(0x0081,0x20);
//    GM65_WriteCommand(0x0082,0xDC);
//    GM65_WriteCommand(0x0083,0xBA);
//    GM65_SaveCommand();
}
void GM65_RESET(void)
{
//    GM65_WriteCommand(0x00D9,0x55);
//    delay_ms(1000);
    GM65_SetDefault();
}
void GM65_Send(uint8_t *command)
{
    int count;
    for(count=0;count<9;count++)
    {
        UART4->DR=command[count];
        while ((USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET));
    }
}

void GM65_SCAN(void)
{
    

}
void GM65_ReadCommand(uint16_t Address,uint8_t Data)
{
    int count;
    uint8_t command[9];
    command[0]=0x7E;
    command[1]=0x00;
    command[2]=0x07;
    command[3]=0x01;
    command[4]=(uint8_t)(Address>>8);
    command[5]=(uint8_t)(Address&0x00FF);
    command[6]=Data;
    command[7]=0xAB;
    command[8]=0xCD;
    GM65_Send(command);

}
void GM65_WriteCommand(uint8_t NumofData,uint16_t Address,uint8_t *data)
{
//    int count;
//    uint8_t command[9];
//    command[0]=0x7E;
//    command[1]=0x00;
//    command[2]=0x08;
//    command[3]=0x01;
//    command[4]=(uint8_t)(Address>>8);
//    command[5]=(uint8_t)(Address&0x00FF);
//    command[6]=data;
//    command[7]=0xAB;
//    command[8]=0xCD;
//    GM65_Send(command);
}
void GM65_SaveCommand(void)
{
//    int count;
//    uint8_t command[9]={0x7E,0x00,0x09,0x01,0x00,0x00,0x00,0xDE,0xC8};
//    GM65_Send();
}
