#include <stdio.h>
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
int main()
{
    int Motor_Number, Motor_Action,Sum;
    uint16_t Motor_Time;
    uint8_t Order[255]={0};
    FILE *fpt; 
    int Pos,i, Flag;
    fpt = fopen("Order.txt","w");
    Order[0]=0x12;
    Order[1]=0x34;
    Order[2]=0xFF;
    //3 4 5 6 7 8 9 10 11 位是9位的配置
    Flag = 0;
    Sum=0;
    i=12;
    while (Flag == 0)
    {
        printf("Input Motor Number\r\n");
        scanf("%d", &Motor_Number);
        printf("Input Time 200MS One Tick\r\n");
        scanf("%d", &Motor_Time);
        printf("Input Motor Action ON=1\r\n");
        scanf("%d", &Motor_Action);
        printf("End?\r\n");
        scanf("%d", &Flag);
        Order[i]=(uint8_t)Motor_Number;
        Order[i+1]=Motor_Time>>8;
        Order[i+2]=Motor_Time&0x00FF;
        Order[i+3]=(uint8_t)Motor_Action;
        i=i+4;
    }
    Order[253]=0x1F;
    Order[254]=0x2F;
    for(i=2;i<252;i++)
    {
        Sum=Sum+Order[i];
    }
    Order[252]=Sum;
    for(i=0;i<255;i++)
    {
        fprintf(fpt,"%02hhX ",Order[i]); 
        printf("%02hhX ",Order[i]); 
    }
    printf("\r\n");
    Motor_Time=(0x09<<8)|0x14;
    printf("%d\r\n",Motor_Time);
}
uint16_t Change8to16(uint8_t HighPart,uint8_t LowPart)
{
    uint16_t sum=0;
    sum=(HighPart<<8)|LowPart;
    return sum;
}