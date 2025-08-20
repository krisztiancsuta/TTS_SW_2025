/**
 * @file MLX90640_I2C_MSP.c
 * @brief MLX90640 I2C driver implementation for TI MSPM0 microcontrollers
 * 
 * This file provides I2C communication functions for the MLX90640 thermal sensor
 * using the TI MSPM0 I2C driver API. It replaces the Arduino Wire library 
 * implementation with native TI driver calls.
 */

#include "MLX90640_I2C_MSP.h"
#include "ti_drivers_config.h"
#include <string.h>

// Global I2C handle for MLX90640 communication
I2C_Handle mlx90640_i2cHandle = NULL;
bool mlx90640_i2c_initialized = false;
I2C_Params i2cParams;

/**
 * @brief Initialize the I2C interface for MLX90640 communication
 */
void MLX90640_I2CInit(void)
{
    // Initialize I2C driver if not already done
    I2C_init();
    // Initialize I2C parameters
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;  // MLX90640 supports up to 1MHz, but 400kHz is more reliable
    
    // Open I2C handle
    mlx90640_i2cHandle = I2C_open(CONFIG_I2C_0, &i2cParams);
    
    if (mlx90640_i2cHandle != NULL)
    {
        mlx90640_i2c_initialized = true;
    }
}

/**
 * @brief Get the I2C handle used for MLX90640 communication
 */
I2C_Handle MLX90640_GetI2CHandle(void)
{
    return mlx90640_i2cHandle;
}

/**
 * @brief Set the I2C handle to be used for MLX90640 communication
 */
void MLX90640_SetI2CHandle(I2C_Handle handle)
{
    mlx90640_i2cHandle = handle;
    mlx90640_i2c_initialized = (handle != NULL);
}

/**
 * @brief Read multiple 16-bit words from MLX90640
 */
int MLX90640_I2CRead(uint8_t slaveAddr, unsigned int startAddress, unsigned int nWordsRead, uint16_t *data)
{
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[2];
    uint8_t rxBuffer[MLX90640_I2C_BUFFER_LENGTH * 2];
    bool status;
    uint16_t bytesToRead = nWordsRead * 2;
    uint16_t dataIndex = 0;
    
    // Check if I2C is initialized
    if (!mlx90640_i2c_initialized || mlx90640_i2cHandle == NULL)
    {
        return MLX90640_I2C_ERROR_PARAM;
    }
    
    // Check parameters
    if (data == NULL || nWordsRead == 0)
    {
        return MLX90640_I2C_ERROR_PARAM;
    }
    
    // Read data in chunks if necessary (due to buffer limitations)
    while (bytesToRead > 0)
    {
        uint16_t chunkSize = (bytesToRead > MLX90640_I2C_BUFFER_LENGTH * 2) ? 
                            MLX90640_I2C_BUFFER_LENGTH * 2 : bytesToRead;
        uint16_t wordsInChunk = chunkSize / 2;
        
        // Set up address to read from
        txBuffer[0] = (startAddress >> 8) & 0xFF;  // MSB
        txBuffer[1] = startAddress & 0xFF;         // LSB
        
        // Configure I2C transaction
        i2cTransaction.targetAddress = slaveAddr;
        i2cTransaction.writeBuf = txBuffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.readBuf = rxBuffer;
        i2cTransaction.readCount = chunkSize;
        
        // Perform I2C transfer
        status = I2C_transfer(mlx90640_i2cHandle, &i2cTransaction);
        if (!status)
        {
            return MLX90640_I2C_ERROR_NACK;
        }
        
        // Convert byte data to 16-bit words (big endian)
        for (uint16_t i = 0; i < wordsInChunk; i++)
        {
            data[dataIndex + i] = ((uint16_t)rxBuffer[i * 2] << 8) | rxBuffer[i * 2 + 1];
        }
        
        // Update for next chunk
        bytesToRead -= chunkSize;
        dataIndex += wordsInChunk;
        startAddress += wordsInChunk;
    }
    
    return MLX90640_I2C_SUCCESS;
}

/**
 * @brief Write a 16-bit word to MLX90640
 */
int MLX90640_I2CWrite(uint8_t slaveAddr, unsigned int writeAddress, uint16_t data)
{
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[4];
    bool status;
    
    // Check if I2C is initialized
    if (!mlx90640_i2c_initialized || mlx90640_i2cHandle == NULL)
    {
        return MLX90640_I2C_ERROR_PARAM;
    }
    
    // Prepare data to write: [Address MSB][Address LSB][Data MSB][Data LSB]
    txBuffer[0] = (writeAddress >> 8) & 0xFF;  // Address MSB
    txBuffer[1] = writeAddress & 0xFF;         // Address LSB  
    txBuffer[2] = (data >> 8) & 0xFF;          // Data MSB
    txBuffer[3] = data & 0xFF;                 // Data LSB
    
    // Configure I2C transaction
    i2cTransaction.targetAddress = slaveAddr;
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.writeCount = 4;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;
    
    // Perform I2C transfer
    status = I2C_transfer(mlx90640_i2cHandle, &i2cTransaction);
    if (!status)
    {
        return MLX90640_I2C_ERROR_NACK;
    }
    
    // Verify write by reading back (optional - can be removed for faster operation)
    uint16_t readBackData;
    int readResult = MLX90640_I2CRead(slaveAddr, writeAddress, 1, &readBackData);
    if (readResult != MLX90640_I2C_SUCCESS)
    {
        return readResult;
    }
    
    if (readBackData != data)
    {
        return MLX90640_I2C_ERROR_VERIFY;
    }
    
    return MLX90640_I2C_SUCCESS;
}

/**
 * @brief Set I2C frequency for MLX90640 communication
 */
void MLX90640_I2CFreqSet(int freq)
{
    // Note: TI I2C driver frequency is typically set during initialization
    // This function is provided for compatibility but may not change frequency
    // at runtime depending on the driver implementation.
    // 
    // For runtime frequency changes, you would need to close and reopen
    // the I2C handle with new parameters, which is not recommended during
    // active communication.
    
    (void)freq; // Suppress unused parameter warning
}

