


// J3
// P1( SPI0_CLK )                   RD
// P3( SPI0_SOMI )                  DB7
// P5( SPI0_SIMO )                  DB15( please ensure)
// P7( SPI0_EN )                    CS

// P2( GPIO_8_2 )                   OS0
// P4( GPIO_8_1 )                   OS1
// P6( GPIO_1_7 )                   OS2
// P8( GPIO_1_6 )                   RAGE


// J4
// P1( GPIO_1_14 )                  CVA
// P3( GPIO_1_13 )                  CVB
// P5( GPIO_8_7 )                   RST
// P7( GPIO_1_12 )                  BUSY
// P9( GPIO_1_11 )                  FIRST

    // P2( GPIO_8_2 )                   OS0
    GPIOBank8Pin2PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 131, GPIO_DIR_OUTPUT);
    // P4( GPIO_8_1 )                   OS1
    GPIOBank8Pin1PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 130, GPIO_DIR_OUTPUT);
    // P6( GPIO_1_7 )                   OS2
    GPIOBank1Pin7PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 24, GPIO_DIR_OUTPUT);
    // P8( GPIO_1_6 )                   RAGE
    GPIOBank1Pin6PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 23, GPIO_DIR_OUTPUT);


    // J4
    // P1( GPIO_1_14 )                  CVA
    GPIOBank1Pin14PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 31, GPIO_DIR_OUTPUT);
    // P3( GPIO_1_13 )                  CVB
    GPIOBank1Pin13PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 30, GPIO_DIR_OUTPUT);
    // P5( GPIO_8_7 )                   RST
    GPIOBank8Pin7PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 136, GPIO_DIR_INPUT);
    // P7( GPIO_1_12 )                  BUSY
    GPIOBank1Pin12PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 29, GPIO_DIR_INPUT);
    // P9( GPIO_1_11 )                  FIRST
    GPIOBank1Pin11PinMuxSetup();
    GPIODirModeSet( SOC_GPIO_0_REGS , 28, GPIO_DIR_INPUT);
