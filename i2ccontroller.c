#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include "ti_drivers_config.h"
#include "MAS_CAN.h"
#include "ti_msp_dl_config.h"
#include "MLX90640_I2C_MSP.h"
#include "MLX90640_Process.h"

uint32_t clk;
void *mainThread(void *arg0)
{
    bool status;
    static float temperatures[768]; // Array to store thermal image data (32x24 pixels)
    int temp_result;
    
    // Initialize I2C for MLX90640 communication
    MLX90640_I2CInit();
    
    // Configure MLX90640 sensor with the initialized I2C handle
    MLX90640_Init(mlx90640_i2cHandle);
    
    while(1){
        // Check if MLX90640 has new thermal data available
        if (MLX90640_CheckStatus() == 1)
        {
            // Read temperature data from MLX90640
            temp_result = MLX90640_ReadTemperatures(temperatures);
            if (temp_result == 0)
            {
                // Find maximum temperature from the thermal data
                float max_temp = MLX90640_DataProcessing(temperatures);
                
                // Send max_temp via CAN
                CAN_transfer(max_temp);
            }
            // If temp_result != 0, there was an error reading temperatures
        }
        else
        {
            // Send 0.0 if no new data available
            CAN_transfer(0.0f);
        }
    }
}




