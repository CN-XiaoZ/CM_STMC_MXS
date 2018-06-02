#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f10x.h"
#include "stdio.h"
#include "sys_config.h"

#define sFLASH_ID 0xEF4015 // W25Q16

#define SPI_FLASH_PageSize 256
#define SPI_FLASH_PerWritePageSize 256

#define W25X_WriteEnable 0x06
#define W25X_WriteDisable 0x04
#define W25X_ReadStatusReg 0x05
#define W25X_WriteStatusReg 0x01
#define W25X_ReadData 0x03
#define W25X_FastReadData 0x0B
#define W25X_FastReadDual 0x3B
#define W25X_PageProgram 0x02
#define W25X_BlockErase 0xD8
#define W25X_SectorErase 0x20
#define W25X_ChipErase 0xC7
#define W25X_PowerDown 0xB9
#define W25X_ReleasePowerDown 0xAB
#define W25X_DeviceID 0xAB
#define W25X_ManufactDeviceID 0x90
#define W25X_JedecDeviceID 0x9F

#define WIP_Flag 0x01
#define Dummy_Byte 0xFF

#define SPI_FLASH_CS_PORT GPIOB
#define SPI_FLASH_CS_PIN GPIO_Pin_12

#define SPI_FLASH_CLK_PORT GPIOB
#define SPI_FLASH_CLK_PIN GPIO_Pin_13

#define SPI_FLASH_MISO_PORT GPIOB
#define SPI_FLASH_MISO_PIN GPIO_Pin_14

#define SPI_FLASH_MOSI_PORT GPIOB
#define SPI_FLASH_MOSI_PIN GPIO_Pin_15

#define SPI_FLASH_CS_LOW() GPIO_ResetBits(SPI_FLASH_CS_PORT, SPI_FLASH_CS_PIN)
#define SPI_FLASH_CS_HIGH() GPIO_SetBits(SPI_FLASH_CS_PORT, SPI_FLASH_CS_PIN)

#define SPIT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

#define FLASH_DEBUG_ON 1

#define FLASH_INFO(fmt, arg...) printf("<<-FLASH-INFO->> " fmt "\n", ##arg)
#define FLASH_ERROR(fmt, arg...) printf("<<-FLASH-ERROR->> " fmt "\n", ##arg)
#define FLASH_DEBUG(fmt, arg...)                                    \
  do                                                                \
    \ {                                                             \
      if (FLASH_DEBUG_ON)                                           \
        printf("<<-FLASH-DEBUG->> [%d]" fmt "\n", __LINE__, ##arg); \
    }                                                               \
  while (0)

/**
 * @brief  SPI��ʼ������
 * @note   SPI2 APB1����
 * @retval None
 */
void SPI_FLASH_Init(void);
/**
 * @brief  FLASH��������,��������
 * @note
 * @param  SectorAddr: ������ַ
 * @retval None
 */
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
/**
 * @brief  FLASH��������,��ƬFlash����
 * @note
 * @retval None
 */
void SPI_FLASH_BulkErase(void);
/**
 * @brief  ��ҳд�뺯��,�޲���
 * @note   ���ܿ�ҳд�� ����ᱨ��,���ֽ������ܳ���256
 * @param  *pBuffer: ������ uint8_t����
 * @param  WriteAddr: д���ַ
 * @param  NumByteToWrite:д�볤��
 * @retval None
 */
void SPI_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
/**
 * @brief  ��ҳд�뺯��
 * @note   ������������һҳ������д��,�޲���
 * @param  *pBuffer: ������
 * @param  WriteAddr: д���ַ
 * @param  NumByteToWrite: д�볤��
 * @retval None
 */
void SPI_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
/**
 * @brief  ��ȡFLASH����
 * @note
 * @param  *pBuffer:������
 * @param  ReadAddr: ��ȡ��ַ
 * @param  NumByteToRead:��ȡ����
 * @retval None
 */
void SPI_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
/**
 * @brief  ��ȡFlashID
 * @note
 * @retval ����IDֵ
 */
uint32_t SPI_FLASH_ReadID(void);
/**
 * @brief  ��ȡFLASH�豸ID
 * @note
 * @retval ����IDֵ
 */
uint32_t SPI_FLASH_ReadDeviceID(void);
/**
 * @brief  ��Ҫ��ת��uint32_t��ַΪuint8_t����
 * @note
 * @param  ReadAddr: ��ȡ��ַ
 * @retval None
 */
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
/**
 * @brief  ����ģʽ
 * @note
 * @retval None
 */
void SPI_Flash_PowerDown(void);
/**
 * @brief  ����Flash
 * @note
 * @retval None
 */
void SPI_Flash_WAKEUP(void);

uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);


#endif /* __SPI_FLASH_H */
