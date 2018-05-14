#include <stdio.h>
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
int main()
{
    int i;
    for(i=0;i<20;i++)
    {
        printf("Order[%d]=(uint8_t)XT>>8;\r\n",4*i+13);
        printf("Order[%d]=(uint8_t)XT>>8;\r\n",4*i+14);
    }

}
