/**
 * @file MLX90640_I2C_MSP.h
 * @brief MLX90640 I2C driver for TI MSPM0 microcontrollers
 * 
 * This file provides I2C communication functions for the MLX90640 thermal sensor
 * using the TI MSPM0 I2C driver API. It replaces the Arduino Wire library 
 * implementation with native TI driver calls.
 */

#ifndef _MLX90640_I2C_MSP_H_
#define _MLX90640_I2C_MSP_H_

#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/I2C.h>

// Default MLX90640 I2C address
#define MLX90640_DEFAULT_ADDRESS 0x33

// I2C communication buffer size for MLX90640
#define MLX90640_I2C_BUFFER_LENGTH 64

// Error codes
#define MLX90640_I2C_SUCCESS        0
#define MLX90640_I2C_ERROR_NACK    -1
#define MLX90640_I2C_ERROR_TIMEOUT -2
#define MLX90640_I2C_ERROR_VERIFY  -3
#define MLX90640_I2C_ERROR_PARAM   -4

// Global variables (declared as extern in header)
extern I2C_Handle mlx90640_i2cHandle;
extern bool mlx90640_i2c_initialized;
extern I2C_Params i2cParams;

/**
 * @brief Initialize the I2C interface for MLX90640 communication
 * 
 * This function should be called once before using any other MLX90640 I2C functions.
 * It initializes the I2C driver with appropriate settings for MLX90640 communication.
 */
void MLX90640_I2CInit(void);

/**
 * @brief Read multiple 16-bit words from MLX90640
 * 
 * @param slaveAddr I2C slave address of the MLX90640 sensor
 * @param startAddress Starting register address to read from
 * @param nWordsRead Number of 16-bit words to read
 * @param data Pointer to buffer where read data will be stored
 * @return 0 on success, negative error code on failure
 */
int MLX90640_I2CRead(uint8_t slaveAddr, unsigned int startAddress, unsigned int nWordsRead, uint16_t *data);

/**
 * @brief Write a 16-bit word to MLX90640
 * 
 * @param slaveAddr I2C slave address of the MLX90640 sensor
 * @param writeAddress Register address to write to
 * @param data 16-bit data to write
 * @return 0 on success, negative error code on failure
 */
int MLX90640_I2CWrite(uint8_t slaveAddr, unsigned int writeAddress, uint16_t data);

/**
 * @brief Set I2C frequency for MLX90640 communication
 * 
 * @param freq Frequency in kHz (e.g., 400 for 400kHz)
 * @note This function may not be implemented if frequency is set during initialization
 */
void MLX90640_I2CFreqSet(int freq);

/**
 * @brief Get the I2C handle used for MLX90640 communication
 * 
 * @return I2C_Handle or NULL if not initialized
 */
I2C_Handle MLX90640_GetI2CHandle(void);

/**
 * @brief Set the I2C handle to be used for MLX90640 communication
 * 
 * @param handle I2C handle from the application
 */
void MLX90640_SetI2CHandle(I2C_Handle handle);



#endif /* _MLX90640_I2C_MSP_H_ */
