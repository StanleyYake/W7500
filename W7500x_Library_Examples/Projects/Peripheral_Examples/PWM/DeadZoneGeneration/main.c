/**
  ******************************************************************************
  * @file    PWM/DeadZoneGeneration/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "W7500x_gpio.h"
#include "W7500x_pwm.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PWM_DeadzoneModeInitTypDef DeadzoneModeStructure;
uint32_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Setting(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /*System clock configuration*/
    SystemInit();
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function
    /* CPIO configuration */
    GPIO_Setting();

    /* Timer mode configuration */
    PrescalerValue = (SystemCoreClock / 1000000) / 10; // Prescale is 2 for 10MHz
    DeadzoneModeStructure.PWM_CHn_PR = PrescalerValue - 1;
    DeadzoneModeStructure.PWM_CHn_MR = 60000;
    DeadzoneModeStructure.PWM_CHn_LR = 120000;
    DeadzoneModeStructure.PWM_CHn_UDMR = PWM_CHn_UDMR_UpCount;
    DeadzoneModeStructure.PWM_CHn_PDMR = PWM_CHn_PDMR_Periodic;
    DeadzoneModeStructure.PWM_CHn_DZCR = 100;
    
    PWM_DeadzoneModeInit(PWM_CH0, &DeadzoneModeStructure); 

    /* PWM0 output enable */
    PWM_CtrlPWMOutputEnable(PWM_CH0); 
    /* PWM1 output disable for inverted PWM0 output signal */
    PWM_CtrlPWMOutputDisable(PWM_CH1); 

    /* PWM channel 0 start */
    PWM_CHn_Start(PWM_CH0);

    while(1);
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Setting(void)
{
    PAD_AFConfig(PAD_PC, GPIO_Pin_0, PAD_AF2); ///< PAD Configuration for PWM0 output
    PAD_AFConfig(PAD_PC, GPIO_Pin_1, PAD_AF2); ///< PAD Configuration for PWM1 output
}
