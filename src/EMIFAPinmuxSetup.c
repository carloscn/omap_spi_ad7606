/* HW Macros */
#include "../include/EMIFAPinmuxSetup.h"

#include "hw_types.h"

/* System Defines */
#include "soc_OMAPL138.h"
#include "hw_syscfg0_OMAPL138.h"
#include "psc.h"

#define PINMUX12_EMIF_A_ENABLE     (SYSCFG_PINMUX12_PINMUX12_31_28_EMA_A0 << \
									SYSCFG_PINMUX12_PINMUX12_31_28_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_27_24_EMA_A1 << \
								    SYSCFG_PINMUX12_PINMUX12_27_24_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_23_20_EMA_A2 << \
								    SYSCFG_PINMUX12_PINMUX12_23_20_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_19_16_EMA_A3 << \
								    SYSCFG_PINMUX12_PINMUX12_19_16_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_15_12_EMA_A4 << \
								    SYSCFG_PINMUX12_PINMUX12_15_12_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_11_8_EMA_A5 << \
								    SYSCFG_PINMUX12_PINMUX12_11_8_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_7_4_EMA_A6 << \
								    SYSCFG_PINMUX12_PINMUX12_7_4_SHIFT) | \
								   (SYSCFG_PINMUX12_PINMUX12_3_0_EMA_A7 << \
								    SYSCFG_PINMUX12_PINMUX12_3_0_SHIFT)

#define PINMUX11_EMIF_A_ENABLE     (SYSCFG_PINMUX11_PINMUX11_31_28_EMA_A8 << \
									SYSCFG_PINMUX11_PINMUX11_31_28_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_27_24_EMA_A9 << \
								    SYSCFG_PINMUX11_PINMUX11_27_24_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_23_20_EMA_A10 << \
								    SYSCFG_PINMUX11_PINMUX11_23_20_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_19_16_EMA_A11 << \
								    SYSCFG_PINMUX11_PINMUX11_19_16_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_15_12_EMA_A12 << \
								    SYSCFG_PINMUX11_PINMUX11_15_12_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_11_8_EMA_A13 << \
								    SYSCFG_PINMUX11_PINMUX11_11_8_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_7_4_EMA_A14 << \
								    SYSCFG_PINMUX11_PINMUX11_7_4_SHIFT) | \
								   (SYSCFG_PINMUX11_PINMUX11_3_0_EMA_A15 << \
								    SYSCFG_PINMUX11_PINMUX11_3_0_SHIFT)

#define PINMUX9_EMIF_D_ENABLE      (SYSCFG_PINMUX9_PINMUX9_3_0_EMA_D7 << \
                                    SYSCFG_PINMUX9_PINMUX9_3_0_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_7_4_EMA_D6 << \
                                    SYSCFG_PINMUX9_PINMUX9_7_4_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_11_8_EMA_D5 << \
                                    SYSCFG_PINMUX9_PINMUX9_11_8_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_15_12_EMA_D4 << \
                                    SYSCFG_PINMUX9_PINMUX9_15_12_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_19_16_EMA_D3 << \
                                    SYSCFG_PINMUX9_PINMUX9_19_16_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_23_20_EMA_D2 << \
                                    SYSCFG_PINMUX9_PINMUX9_23_20_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_27_24_EMA_D1 << \
                                    SYSCFG_PINMUX9_PINMUX9_27_24_SHIFT) | \
                                   (SYSCFG_PINMUX9_PINMUX9_31_28_EMA_D0 << \
                                    SYSCFG_PINMUX9_PINMUX9_31_28_SHIFT)
 
#define PINMUX8_EMIF_D_ENABLE      (SYSCFG_PINMUX8_PINMUX8_3_0_EMA_D15 << \
							        SYSCFG_PINMUX8_PINMUX8_3_0_SHIFT) | \
							       (SYSCFG_PINMUX8_PINMUX8_7_4_EMA_D14 << \
		       						SYSCFG_PINMUX8_PINMUX8_7_4_SHIFT) | \
				    			   (SYSCFG_PINMUX8_PINMUX8_11_8_EMA_D13 << \
					    			SYSCFG_PINMUX8_PINMUX8_11_8_SHIFT) | \
						    	   (SYSCFG_PINMUX8_PINMUX8_15_12_EMA_D12 << \
							    	SYSCFG_PINMUX8_PINMUX8_15_12_SHIFT) | \
					    		   (SYSCFG_PINMUX8_PINMUX8_19_16_EMA_D11 << \
						    		SYSCFG_PINMUX8_PINMUX8_19_16_SHIFT) | \
							       (SYSCFG_PINMUX8_PINMUX8_23_20_EMA_D10 << \
								    SYSCFG_PINMUX8_PINMUX8_23_20_SHIFT) | \
	     						   (SYSCFG_PINMUX8_PINMUX8_27_24_EMA_D9 << \
		    						SYSCFG_PINMUX8_PINMUX8_27_24_SHIFT) | \
			    				   (SYSCFG_PINMUX8_PINMUX8_31_28_EMA_D8 << \
				    				SYSCFG_PINMUX8_PINMUX8_31_28_SHIFT)
/*EMIFA_BA0 EMIFA_BA1*/ 
#define PINMUX5_EMIF_BA_ENABLE     (SYSCFG_PINMUX5_PINMUX5_31_28_EMA_BA0 << \
							        SYSCFG_PINMUX5_PINMUX5_31_28_SHIFT) | \
							       (SYSCFG_PINMUX5_PINMUX5_27_24_EMA_BA1 << \
							        SYSCFG_PINMUX5_PINMUX5_27_24_SHIFT)


/*EMIFA_CSn2  EMIFA_WEn  EMIFA_OEn*/
#define PINMUX7_EMIF_CTL_ENABLE    (SYSCFG_PINMUX7_PINMUX7_3_0_NEMA_CS2 << \
								    SYSCFG_PINMUX7_PINMUX7_3_0_SHIFT) | \
								   (SYSCFG_PINMUX7_PINMUX7_23_20_NEMA_OE << \
								    SYSCFG_PINMUX7_PINMUX7_23_20_SHIFT) | \
								   (SYSCFG_PINMUX7_PINMUX7_19_16_NEMA_WE << \
								    SYSCFG_PINMUX7_PINMUX7_19_16_SHIFT)

 /*****************************************************************************
 ** 					  FUNCTION DEFINITION
 *****************************************************************************/
 /**
  * \brief	 This function selects the EMIFA pins for use. The EMIFA pins
  * 		 are multiplexed with pins of other peripherals in the
  * 		 System on Chip(SoC).
  *
  * \param	 None.
  *
  * \return  None.
  */
void EMIFAPinMuxSetup(void)
{
	 volatile unsigned int savePinMux = 0;

	 /* Programming the PINMUX12 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX12 register.
	 */
	 //savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(12)) & \
						 ~(SYSCFG_PINMUX12_PINMUX12_31_28 | \
						   SYSCFG_PINMUX12_PINMUX12_27_24 | \
						   SYSCFG_PINMUX12_PINMUX12_23_20 | \
						   SYSCFG_PINMUX12_PINMUX12_19_16 | \
						   SYSCFG_PINMUX12_PINMUX12_15_12 | \
						   SYSCFG_PINMUX12_PINMUX12_11_8  | \
						   SYSCFG_PINMUX12_PINMUX12_7_4   | \
						   SYSCFG_PINMUX12_PINMUX12_3_0);
	  /* 
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX12  register.
     */
     //HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(12)) = \
    		 (PINMUX12_EMIF_A_ENABLE | savePinMux);

	  

	 /* Programming the PINMUX11 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX11 register.
	 */
	 //savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(11)) & \
						 ~(SYSCFG_PINMUX11_PINMUX11_31_28 | \
						   SYSCFG_PINMUX11_PINMUX11_27_24 | \
						   SYSCFG_PINMUX11_PINMUX11_23_20 | \
						   SYSCFG_PINMUX11_PINMUX11_19_16 | \
						   SYSCFG_PINMUX11_PINMUX11_15_12 | \
						   SYSCFG_PINMUX11_PINMUX11_11_8  | \
						   SYSCFG_PINMUX11_PINMUX11_7_4   | \
						   SYSCFG_PINMUX11_PINMUX11_3_0);
	  /* 
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX11  register.
     */
    // HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(11)) = \
    		 (PINMUX11_EMIF_A_ENABLE | savePinMux);



	 /* Programming the PINMUX9 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX9 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(9)) & \
						 ~(SYSCFG_PINMUX9_PINMUX9_31_28 | \
						   SYSCFG_PINMUX9_PINMUX9_27_24 | \
						   SYSCFG_PINMUX9_PINMUX9_23_20 | \
						   SYSCFG_PINMUX9_PINMUX9_19_16 | \
						   SYSCFG_PINMUX9_PINMUX9_15_12 | \
						   SYSCFG_PINMUX9_PINMUX9_11_8  | \
						   SYSCFG_PINMUX9_PINMUX9_7_4   | \
						   SYSCFG_PINMUX9_PINMUX9_3_0);
	  /* 
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX9  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(9)) = \
          (PINMUX9_EMIF_D_ENABLE | savePinMux);


	 /* Programming the PINMUX8 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX8 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(8)) & \
						 ~(SYSCFG_PINMUX8_PINMUX8_31_28 | \
						   SYSCFG_PINMUX8_PINMUX8_27_24 | \
						   SYSCFG_PINMUX8_PINMUX8_23_20 | \
						   SYSCFG_PINMUX8_PINMUX8_19_16 | \
						   SYSCFG_PINMUX8_PINMUX8_15_12 | \
						   SYSCFG_PINMUX8_PINMUX8_11_8  | \
						   SYSCFG_PINMUX8_PINMUX8_7_4   | \
						   SYSCFG_PINMUX8_PINMUX8_3_0);
	  /* 
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX8  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(8)) = \
          (PINMUX8_EMIF_D_ENABLE | savePinMux);


	 /* Programming the PINMUX5 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX5 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
						 ~(SYSCFG_PINMUX5_PINMUX5_31_28 | \
						   SYSCFG_PINMUX5_PINMUX5_27_24);
	  /* 
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX5  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
          (PINMUX5_EMIF_BA_ENABLE | savePinMux);


	 /* Programming the PINMUX7 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX7 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(7)) & \
						 ~(SYSCFG_PINMUX7_PINMUX7_23_20 | \
						   SYSCFG_PINMUX7_PINMUX7_19_16 | \
						   SYSCFG_PINMUX7_PINMUX7_3_0);
	  /* 
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX7  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(7)) = \
          (PINMUX7_EMIF_CTL_ENABLE | savePinMux);

}





