/**
 ******************************************************************************
 * @file    W25Q16.c
 * @author  MXS-Xizo
 * @version V1.0
 * @date    2018-02-16
 * @brief   SPI接口的W25Q16FLASH的底层函数
 ******************************************************************************
 */
#include "./flash/W25Q16.h"




static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);
static __IO uint32_t SPITimeout = SPIT_LONG_TIMEOUT;

void SPI_FLASH_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = SPI_FLASH_CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SPI_FLASH_CS_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = SPI_FLASH_CLK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_FLASH_CLK_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MISO_PIN;
    GPIO_Init(SPI_FLASH_MISO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_FLASH_MOSI_PIN;
    GPIO_Init(SPI_FLASH_MOSI_PORT, &GPIO_InitStructure);
    SPI_FLASH_CS_HIGH();

    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);
    SPI_Cmd(SPI2, ENABLE);
}

void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
    SPI_FLASH_WriteEnable();
    SPI_FLASH_WaitForWriteEnd();
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_SectorErase);
    SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    SPI_FLASH_SendByte(SectorAddr & 0xFF);
    SPI_FLASH_CS_HIGH();
    SPI_FLASH_WaitForWriteEnd();
}

void SPI_FLASH_BulkErase(void)
{
    SPI_FLASH_WriteEnable();
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ChipErase);
    SPI_FLASH_CS_HIGH();
    SPI_FLASH_WaitForWriteEnd();
}

void SPI_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr,
                         uint16_t NumByteToWrite)
{
    SPI_FLASH_WriteEnable();
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_PageProgram);
    SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    SPI_FLASH_SendByte(WriteAddr & 0xFF);

    if (NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
        FLASH_ERROR("SPI_FLASH_PageWrite too large!");
    }

    while (NumByteToWrite--)
    {
        SPI_FLASH_SendByte(*pBuffer);
        pBuffer++;
    }
    SPI_FLASH_CS_HIGH();
    SPI_FLASH_WaitForWriteEnd();
}

void SPI_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr,
                           uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0,
            i = 0;
    Addr      = WriteAddr % SPI_FLASH_PageSize;

    count       = SPI_FLASH_PageSize - Addr;
    NumOfPage   = NumByteToWrite / SPI_FLASH_PageSize;
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    if (Addr == 0)
    {
        if (NumOfPage == 0)
        {
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else
        {
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr += SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else
    {
        if (NumOfPage == 0)
        {
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);

                WriteAddr += count;
                pBuffer += count;
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else
        {
            NumByteToWrite -= count;
            NumOfPage   = NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);

            WriteAddr += count;
            pBuffer += count;
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr += SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            if (NumOfSingle != 0)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

void SPI_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr,
                          uint16_t NumByteToRead)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ReadData);
    SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    SPI_FLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    SPI_FLASH_SendByte(ReadAddr & 0xFF);

    while (NumByteToRead--)
    {
        *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);

        pBuffer++;
    }

    SPI_FLASH_CS_HIGH();
}

uint32_t SPI_FLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_JedecDeviceID);

    Temp0 = SPI_FLASH_SendByte(Dummy_Byte);

    Temp1 = SPI_FLASH_SendByte(Dummy_Byte);

    Temp2 = SPI_FLASH_SendByte(Dummy_Byte);

    SPI_FLASH_CS_HIGH();
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}

uint32_t SPI_FLASH_ReadDeviceID(void)
{
    uint32_t Temp = 0;

    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_DeviceID);
    SPI_FLASH_SendByte(Dummy_Byte);
    SPI_FLASH_SendByte(Dummy_Byte);
    SPI_FLASH_SendByte(Dummy_Byte);

    Temp = SPI_FLASH_SendByte(Dummy_Byte);

    SPI_FLASH_CS_HIGH();

    return Temp;
}

void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ReadData);
    SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    SPI_FLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    SPI_FLASH_SendByte(ReadAddr & 0xFF);
}

uint8_t SPI_FLASH_ReadByte(void) { return (SPI_FLASH_SendByte(Dummy_Byte)); }

uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(0);
    }
    SPI_I2S_SendData(SPI2, byte);

    SPITimeout = SPIT_FLAG_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(1);
    }

    return SPI_I2S_ReceiveData(SPI2);
}

uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(2);
    }

    SPI_I2S_SendData(SPI2, HalfWord);

    SPITimeout = SPIT_FLAG_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(3);
    }
    return SPI_I2S_ReceiveData(SPI2);
}

void SPI_FLASH_WriteEnable(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_WriteEnable);
    SPI_FLASH_CS_HIGH();
}

#define WIP_Flag 0x01

void SPI_FLASH_WaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;

    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte(W25X_ReadStatusReg);

    do
    {
        FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);
    } while ((FLASH_Status & WIP_Flag) == SET);
    SPI_FLASH_CS_HIGH();
}

void SPI_Flash_PowerDown(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_PowerDown);
    SPI_FLASH_CS_HIGH();
}

void SPI_Flash_WAKEUP(void)
{
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte(W25X_ReleasePowerDown);
    SPI_FLASH_CS_HIGH();
}

static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    FLASH_ERROR("SPI TimeOut! errorCode = %d", errorCode);
    return 0;
}
