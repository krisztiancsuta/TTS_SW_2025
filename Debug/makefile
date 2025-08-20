################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_4.0.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./MAS_CAN.o" \
"./MLX90640_API.o" \
"./MLX90640_Driver.o" \
"./MLX90640_I2C_MSP.o" \
"./MLX90640_Init.o" \
"./MLX90640_Process.o" \
"./i2ccontroller.o" \
"./main_freertos.o" \
"./ti_drivers_config.o" \
"./ti_msp_dl_config.o" \
"./freertos/ticlang/startup_mspm0g350x_ticlang.o" \
"./ti/display/Display.o" \
"./ti/display/DisplayUart.o" \
"../mspm0g3507.cmd" \
$(GEN_CMDS__FLAG) \
-Wl,-l"/Users/krisztiancsuta/ti/mspm0_sdk_2_04_00_06/source/ti/drivers/lib/ticlang/m0p/drivers_mspm0g1x0x_g3x0x.a" \
-Wl,-lfreertos_builds_LP_MSPM0G3507_release_ticlang.lib \
-Wl,-l"/Users/krisztiancsuta/ti/mspm0_sdk_2_04_00_06/source/ti/driverlib/lib/ticlang/m0p/mspm0g1x0x_g3x0x/driverlib.a" \
-Wl,-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include freertos/ticlang/subdir_vars.mk
-include ti/display/subdir_vars.mk
-include subdir_rules.mk
-include freertos/ticlang/subdir_rules.mk
-include ti/display/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
TTS_SW_2025.out 

EXE_OUTPUTS__QUOTED += \
"TTS_SW_2025.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "TTS_SW_2025.out"

dependents:
	-cd /Users/krisztiancsuta/Documents/FRT/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug && $(MAKE) all

# Tool invocations
TTS_SW_2025.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) /Users/krisztiancsuta/Documents/FRT/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug/freertos_builds_LP_MSPM0G3507_release_ticlang.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_4.0.2.LTS/bin/tiarmclang" -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -D__MSPM0G3507__ -gdwarf-3 -Wl,-m"TTS_SW_2025.map" -Wl,-i"/Users/krisztiancsuta/Documents/FRT/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug" -Wl,-i"/Users/krisztiancsuta/ti/mspm0_sdk_2_04_00_06/source" -Wl,-i"/Users/krisztiancsuta/Documents/FRT/TTS_SW_2025" -Wl,-i"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_4.0.2.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="TTS_SW_2025_linkInfo.xml" -Wl,--rom_model -o "TTS_SW_2025.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "MAS_CAN.o" "MLX90640_API.o" "MLX90640_Driver.o" "MLX90640_I2C_MSP.o" "MLX90640_Init.o" "MLX90640_Process.o" "i2ccontroller.o" "main_freertos.o" "ti_drivers_config.o" "ti_msp_dl_config.o" "freertos/ticlang/startup_mspm0g350x_ticlang.o" "ti/display/Display.o" "ti/display/DisplayUart.o" 
	-$(RM) "MAS_CAN.d" "MLX90640_API.d" "MLX90640_Driver.d" "MLX90640_I2C_MSP.d" "MLX90640_Init.d" "MLX90640_Process.d" "i2ccontroller.d" "main_freertos.d" "ti_drivers_config.d" "ti_msp_dl_config.d" "freertos/ticlang/startup_mspm0g350x_ticlang.d" "ti/display/Display.d" "ti/display/DisplayUart.d" 
	-$(RM) "MLX90640_API.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/krisztiancsuta/Documents/FRT/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug/freertos_builds_LP_MSPM0G3507_release_ticlang.lib:

-include ../makefile.targets

