/**
 * @file MLX90640_Driver.h
 * @brief MLX90640 thermal sensor interface functions
 */

#ifndef MLX90640_PROCESS_H
#define MLX90640_PROCESS_H

#include <ti/drivers/I2C.h>

/**
 * @brief Configure MLX90640 sensor settings
 * 
 * @param i2cHandle I2C handle from your main application
 * 
 * @param i2cHandle I2C handle from your main application
 */
void MLX90640_Init(I2C_Handle i2cHandle);

/**
 * @brief Check if MLX90640 has new data ready
 * 
 * @return 1 if new data available, 0 if not, negative on error
 */
int MLX90640_CheckStatus(void);

/**
 * @brief Read thermal data and convert to temperatures
 * 
 * @param temperatures Array to store 768 temperature values
 * @return 0 on success, negative on error
 */
int MLX90640_ReadTemperatures(float *temperatures);

/**
 * @brief Find maximum temperature from thermal data
 * 
 * @param temperatures Array containing 768 temperature values
 * @return Maximum temperature in Celsius
 */
float MLX90640_DataProcessing(float *temperatures);

#endif /* MLX90640_PROCESS_H */
