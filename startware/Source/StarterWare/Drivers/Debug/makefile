################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.2

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./cppi41dma.obj" \
"./ecap.obj" \
"./edma.obj" \
"./ehrpwm.obj" \
"./emac.obj" \
"./emifa.obj" \
"./gpio.obj" \
"./i2c.obj" \
"./lan8710a.obj" \
"./lidd.obj" \
"./mcasp.obj" \
"./mdio.obj" \
"./pru.obj" \
"./psc.obj" \
"./raster.obj" \
"./rtc.obj" \
"./spi.obj" \
"./timer.obj" \
"./uart.obj" \
"./usb.obj" \
"./usbphyGS60.obj" \
"./vpif.obj" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
LIB_OUTPUTS += \
Drivers.lib \

LIB_OUTPUTS__QUOTED += \
"Drivers.lib" \


# All Target
all: Drivers.lib

# Tool invocations
Drivers.lib: $(OBJS)
ifneq ($(strip $(ORDERED_OBJS)),)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C6000 Archiver'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.2/bin/ar6x" r "Drivers.lib" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
endif
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(LIB_OUTPUTS__QUOTED)
	-$(RM) "cppi41dma.obj" "ecap.obj" "edma.obj" "ehrpwm.obj" "emac.obj" "emifa.obj" "gpio.obj" "i2c.obj" "lan8710a.obj" "lidd.obj" "mcasp.obj" "mdio.obj" "pru.obj" "psc.obj" "raster.obj" "rtc.obj" "spi.obj" "timer.obj" "uart.obj" "usb.obj" "usbphyGS60.obj" "vpif.obj" 
	-$(RM) "cppi41dma.d" "ecap.d" "edma.d" "ehrpwm.d" "emac.d" "emifa.d" "gpio.d" "i2c.d" "lan8710a.d" "lidd.d" "mcasp.d" "mdio.d" "pru.d" "psc.d" "raster.d" "rtc.d" "spi.d" "timer.d" "uart.d" "usb.d" "usbphyGS60.d" "vpif.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@mkdir ..\..\..\..\Library\StarterWare\Drivers\Debug & copy drivers.lib ..\..\..\..\Library\StarterWare\Drivers\Debug\drivers.lib
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

