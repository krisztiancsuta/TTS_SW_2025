# MLX90640 Integration Guide

This guide shows how to integrate the MLX90640 thermal sensor with your existing TI MSPM0 I2C setup.

## Files Added

1. **MLX90640_I2C_MSP.h** - Header file for MSP-specific I2C functions
2. **MLX90640_I2C_MSP.c** - Implementation using TI I2C drivers
3. **MLX90640_Example.h** - Example usage header
4. **MLX90640_Example.c** - Example usage implementation

## Modified Files

1. **MLX90640_I2C_Driver.h** - Updated to use MSP implementation
2. **MLX90640_I2C_Driver.cpp** - Updated to use MSP implementation

## Integration Steps

### Step 1: Include Headers

Add these includes to your main file (e.g., i2ccontroller.c):

```c
#include "MLX90640_I2C_MSP.h"
#include "MLX90640_API.h"
#include "MLX90640_Example.h"
```

### Step 2: Initialize MLX90640

In your `mainThread` function, after opening your I2C handle:

```c
void *mainThread(void *arg0)
{
    I2C_Handle i2cHandle;
    I2C_Params i2cParams;

    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;

    i2cHandle = I2C_open(CONFIG_I2C_0, &i2cParams);
    if (i2cHandle == NULL) {
        while (1); // Halt if I2C initialization fails
    }

    // Initialize MLX90640
    MLX90640_Example_Init(i2cHandle);

    while(1) {
        // Your existing sensor readings
        read_i2c_values(sin_cos1, sin_cos2, i2cHandle);

        // Add MLX90640 readings
        MLX90640_Integration_Example(i2cHandle);

        CAN_transfer();
    }
}
```

### Step 3: Basic Usage Example

```c
// Static variables for thermal data
static float temperatures[768]; // 32x24 thermal image
static bool mlx_initialized = false;

// In your main loop
if (!mlx_initialized) {
    MLX90640_Example_Init(i2cHandle);
    mlx_initialized = true;
}

// Check for new thermal data
int status = MLX90640_Example_CheckStatus();
if (status == 1) { // New data available
    int result = MLX90640_Example_ReadTemperatures(temperatures);
    if (result == 0) {
        // Process thermal data
        float center_temp = temperatures[384]; // Center pixel
        
        // Send via CAN or process as needed
        // ...
    }
}
```

## MLX90640 I2C Address

The default MLX90640 I2C address is **0x33**. If your sensor has a different address, update the `MLX90640_I2C_ADDRESS` definition in the example files.

## Key Functions

### MLX90640_I2CRead
```c
int MLX90640_I2CRead(uint8_t slaveAddr, unsigned int startAddress, 
                     unsigned int nWordsRead, uint16_t *data);
```
- Reads multiple 16-bit words from MLX90640
- Used by MLX90640_API functions

### MLX90640_I2CWrite  
```c
int MLX90640_I2CWrite(uint8_t slaveAddr, unsigned int writeAddress, uint16_t data);
```
- Writes a 16-bit word to MLX90640
- Used for configuration and control

## Error Handling

The functions return standard error codes:
- `0` - Success
- `-1` - NACK error (device not responding)
- `-2` - Timeout error  
- `-3` - Verification error (write didn't stick)
- `-4` - Parameter error

## Memory Usage

- The thermal image requires 768 float values (3072 bytes)
- EEPROM data requires 832 uint16_t values (1664 bytes)  
- Frame data requires 834 uint16_t values (1668 bytes)

Consider using static allocation or ensure sufficient heap space.

## Performance Notes

- MLX90640 can run at up to 64Hz refresh rate
- I2C communication at 400kHz is recommended (1MHz also supported)
- Each thermal frame requires ~1.6KB of I2C data transfer
- Processing time depends on CPU speed and optimization level

## Troubleshooting

1. **No ACK from sensor**: Check I2C address (0x33) and connections
2. **Invalid EEPROM data**: Sensor may be damaged or not properly initialized
3. **Verification errors**: I2C communication issues or timing problems
4. **Memory allocation**: Ensure sufficient stack/heap for large arrays

## Example Integration with Your Current Code

Your current `i2ccontroller.c` reads from two ADC sensors. You can easily add MLX90640:

```c
while(1) {
    // Existing ADC readings
    read_i2c_values(sin_cos1, sin_cos2, i2cHandle);
    
    // Add thermal sensor reading
    if (MLX90640_Example_CheckStatus() == 1) {
        MLX90640_Example_ReadTemperatures(temperatures);
        // Process thermal data...
    }
    
    CAN_transfer();
}
```
