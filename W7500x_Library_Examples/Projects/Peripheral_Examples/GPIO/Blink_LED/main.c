/**
  ******************************************************************************
  * @file    GPIO/Blink_LED/main.c 
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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitDef;

/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{
    /* Set Systme init */
    SystemInit();
    
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function
    
    /* GPIO LED(R) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_8; // Set to Pin_8 (LED(R))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_8, PAD_AF1); // PAD Config - LED used 2nd Function
	
    /* GPIO LED(G) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_9; // Set to Pin_9 (LED(G))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_9, PAD_AF1);	// PAD Config - LED used 2nd Function
	  
    /* GPIO LED(B) Set */
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_5; // Set to Pin_5 (LED(B))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOC, &GPIO_InitDef);
    PAD_AFConfig(PAD_PC,GPIO_Pin_5, PAD_AF1); // PAD Config - LED used 2nd Function
		
    GPIO_SetBits(GPIOC, GPIO_Pin_8); // LED(R) Off
    GPIO_SetBits(GPIOC, GPIO_Pin_9); // LED(G) Off
    GPIO_SetBits(GPIOC, GPIO_Pin_5); // LED(B) Off
	
    while(1)
    {
        // LED(RGB) On/off
        delay_ms(500);
  	    GPIO_ResetBits(GPIOC, GPIO_Pin_8);			
	    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	    GPIO_ResetBits(GPIOC, GPIO_Pin_5);		  
	    delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_8);
        GPIO_SetBits(GPIOC, GPIO_Pin_9);
        GPIO_SetBits(GPIOC, GPIO_Pin_5);

        // LED(RG) On/off			
	    delay_ms(500);
  	    GPIO_ResetBits(GPIOC, GPIO_Pin_8);				
	    GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	    delay_ms(500);
	    GPIO_SetBits(GPIOC, GPIO_Pin_8);
        GPIO_SetBits(GPIOC, GPIO_Pin_9);

	    // LED(GB) On/off
	    delay_ms(500);
  	    GPIO_ResetBits(GPIOC, GPIO_Pin_9);				
	    GPIO_ResetBits(GPIOC, GPIO_Pin_5);			
	    delay_ms(500);
  	    GPIO_SetBits(GPIOC, GPIO_Pin_9);				
	    GPIO_SetBits(GPIOC, GPIO_Pin_5);
				
        // LED(BR) On/off
    	delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_5);				
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);			
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_5);				
        GPIO_SetBits(GPIOC, GPIO_Pin_8);

        // LED(R) On/off
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_8);

        // LED(G) On/off
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_9);
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_9);
        
        // LED(B) On/off
        delay_ms(500);
        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
        delay_ms(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_5);			
    }
}

/**
  * @brief  Delay Function
  */
void delay_ms(__IO uint32_t nCount)
{
    volatile uint32_t delay = nCount * 2500; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}
