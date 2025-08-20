/**
 * @file MLX90640_Driver.c
 * @brief MLX90640 thermal sensor integration with TI MSPM0 I2C driver
 * 
 * This file demonstrates how to integrate the MLX90640 thermal sensor
 * with your existing I2C setup and read thermal data.
 */

#include "MLX90640_I2C_MSP.h"
#include "MLX90640_API.h"
#include "MLX90640_Process.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// MLX90640 sensor configuration
#define MLX90640_I2C_ADDRESS    0x33  // Default MLX90640 I2C address

// Global variables to store calibration data (read once during init)
static uint16_t mlx90640_eeData[832];
static paramsMLX90640 mlx90640_params;
static bool mlx90640_initialized = false;

// Function prototypes
void MLX90640_Init(I2C_Handle i2cHandle);
int MLX90640_CheckStatus(void);
int MLX90640_ReadTemperatures(float *temperatures);
float MLX90640_DataProcessing(float *temperatures);

/**
 * @brief Configure MLX90640 sensor settings
 * 
 * @param i2cHandle I2C handle from your main application (already initialized)
 * @return 0 on success, negative value on error
 */
void MLX90640_Init(I2C_Handle i2cHandle)
{
    int error;
    
    // Set the I2C handle for MLX90640 communication (I2C already initialized in i2ccontroller.c)
    MLX90640_SetI2CHandle(i2cHandle);
    
    // Read EEPROM data from MLX90640 (store in global variable)
    error = MLX90640_DumpEE(MLX90640_I2C_ADDRESS, mlx90640_eeData);
    if (error != 0)
    {
        // Handle error - could not read EEPROM
        mlx90640_initialized = false;
        return;
    }
    
    // Extract calibration parameters from EEPROM data (store in global variable)
    error = MLX90640_ExtractParameters(mlx90640_eeData, &mlx90640_params);
    if (error != 0)
    {
        // Handle error - invalid EEPROM data
        mlx90640_initialized = false;
        return;
    }
    
    // Set refresh rate (0: 0.5Hz, 1: 1Hz, 2: 2Hz, 3: 4Hz, 4: 8Hz, 5: 16Hz, 6: 32Hz, 7: 64Hz)
    error = MLX90640_SetRefreshRate(MLX90640_I2C_ADDRESS, 4); // 8Hz
    if (error != 0)
    {
        // Handle error
    }
    
    // Set resolution (0: 16bit, 1: 17bit, 2: 18bit, 3: 19bit)
    error = MLX90640_SetResolution(MLX90640_I2C_ADDRESS, 2); // 18bit
    if (error != 0)
    {
        // Handle error  
    }
    
    // Set interleaved mode (recommended for most applications)
    error = MLX90640_SetInterleavedMode(MLX90640_I2C_ADDRESS);
    if (error != 0)
    {
        // Handle error
    }
    
    // Mark as successfully initialized
    mlx90640_initialized = true;
}


/**
 * @brief Read thermal data from MLX90640 and convert to temperatures
 * 
 * @param temperatures Array to store 768 temperature values (32x24 pixels)
 * @return 0 on success, negative value on error
 */
int MLX90640_ReadTemperatures(float *temperatures)
{
    uint16_t frameData[834];
    int error;
    
    // Check if sensor was properly initialized
    if (!mlx90640_initialized)
    {
        return -1; // Sensor not initialized
    }
    
    // Get frame data
    error = MLX90640_GetFrameData(MLX90640_I2C_ADDRESS, frameData);
    if (error < 0) return error;
    
    // Convert frame data to temperatures using pre-loaded calibration parameters
    // Parameters: frameData, params, emissivity, reflected_temp, result_array
    MLX90640_CalculateTo(frameData, &mlx90640_params, 0.95f, 21.0f, temperatures);
    
    return 0;
}

/**
 * @brief Check if MLX90640 has new data ready
 * 
 * @return 1 if new data available, 0 if not, negative on error
 */
int MLX90640_CheckStatus(void)
{
    uint16_t statusRegister;
    int error;
    
    // Check if I2C is initialized
    if (!mlx90640_initialized)
    {
        return -1; // Sensor not initialized
    }
    
    // Read status register from address 0x8000
    error = MLX90640_I2CRead(MLX90640_I2C_ADDRESS, 0x8000, 1, &statusRegister);
    if (error != MLX90640_I2C_SUCCESS)
    {
        return error;
    }
    
    // Check if new data is ready (bit 3)
    return (statusRegister & 0x0008) ? 1 : 0;
}

/**
 * @brief Find maximum temperature from thermal data
 * 
 * @param temperatures Array containing 768 temperature values (already read)
 * @return Maximum temperature in Celsius
 */
float MLX90640_DataProcessing(float *temperatures)
{
    // Find maximum temperature
    float max_temp = temperatures[0];
    for (int i = 1; i < 768; i++)
    {
        if (temperatures[i] > max_temp)
        {
            max_temp = temperatures[i];
        }
    }
    
    return max_temp;
}
