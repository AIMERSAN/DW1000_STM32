/*! ----------------------------------------------------------------------------
 * @file	deca_spi.h
 * @brief	SPI access functions
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */

#ifndef _DECA_SPI_H_
#define _DECA_SPI_H_

#include "drv_Spi.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "deca_types.h"

#define DECA_MAX_SPI_HEADER_LENGTH      (3)                     // max number of bytes in header (for formating & sizing)

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: openspi()
 *
 * Low level abstract function to open and initialise access to the SPI device.
 * returns 0 for success, or -1 for error
 */
//int openspi(void) ;

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: closespi()
 *
 * Low level abstract function to close the the SPI device.
 * returns 0 for success, or -1 for error
 */
//int closespi(void) ;

int writetospi_serial
(
    SPI_TypeDef*   SPIx,
    GPIO_TypeDef*  SPIx_CS_GPIO,
    uint16_t       SPIx_CS_PIN,
    uint16_t       headerLength,
    const uint8_t *headerBuffer,
    uint32_t       bodylength,
    const uint8_t *bodyBuffer
);

int readfromspi_serial
(
    SPI_TypeDef*   SPIx,
    GPIO_TypeDef*  SPIx_CS_GPIO,
    uint16_t       SPIx_CS_PIN,
    uint16_t       headerLength,
    const uint8_t *headerBuffer,
    uint32_t       readlength,
    uint8_t       *readBuffer
);

extern int writetospi_serial
(
    SPI_TypeDef*   SPIx,
    GPIO_TypeDef*  SPIx_CS_GPIO,
    uint16_t       SPIx_CS_PIN,
    uint16_t       headerLength,
    const uint8_t *headerBuffer,
    uint32_t       bodylength,
    const uint8_t *bodyBuffer
);

extern int readfromspi_serial
(
    SPI_TypeDef*   SPIx,
    GPIO_TypeDef*  SPIx_CS_GPIO,
    uint16_t       SPIx_CS_PIN,
    uint16_t       headerLength,
    const uint8_t *headerBuffer,
    uint32_t       readlength,
    uint8_t       *readBuffer
);

#define writetospi writetospi_serial
#define readfromspi readfromspi_serial

#ifdef __cplusplus
}
#endif

#endif /* _DECA_SPI_H_ */
