/**
  ******************************************************************************
  * File Name          : utils.h
  * Description        : This file contains all the functions prototypes for 
  *                      the utils.h
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UTILS_H
#define __UTILS_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "main.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_if.h"

//#include "arch.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define CONVERT_LITTLE_ENDIAN 	0
#define CONVERT_BIG_ENDIAN 		1


#define LED_CAN1_RECEIVE 	0
#define LED_CAN2_RECEIVE 	1
#define LED_CAN3_RECEIVE 	2
#define LED_UDP_RECEIVE		3

#define LED_CAN1_RECEIVE_PERIOD_MS	100
#define LED_CAN2_RECEIVE_PERIOD_MS	100
#define LED_CAN3_RECEIVE_PERIOD_MS	100
#define LED_UDP_RECEIVE_PERIOD_MS	100

#define CAN1_RECEIVE_LED_PORT  	RGB_B_2_GPIO_Port
#define CAN1_RECEIVE_LED_PIN	RGB_B_2_Pin
#define CAN2_RECEIVE_LED_PORT  	RGB_B_1_GPIO_Port
#define CAN2_RECEIVE_LED_PIN	RGB_B_1_Pin
#define CAN3_RECEIVE_LED_PORT  	RGB_B_3_GPIO_Port
#define CAN3_RECEIVE_LED_PIN	RGB_B_3_Pin
#define UDP_RECEIVE_LED_PORT	RGB_G_3_GPIO_Port
#define UDP_RECEIVE_LED_PIN		RGB_G_3_Pin

/* USER CODE END Private defines */
 typedef struct VCP_FIFO_TYPE
 {
   uint8_t* data;  // Will point to the Cube-generated Tx or Rx buffer
   int  wr;    // Write index
   int  rd;    // Read index
   int  lb;    // Additional index
 } VCP_FIFO;


/* USER CODE BEGIN Prototypes */

void buildCanFrameToUSB(uint8_t data[], CAN_RxHeaderTypeDef  rx_header, uint8_t* Frame, uint8_t* FrameLength );
void buildCanFrameUSB(uint8_t* Frame, uint8_t* data,  CAN_TxHeaderTypeDef* tx_header);
void allLEDsOff(void);
void blinkLED(uint8_t blink_case);
void char2float(char value[], float *p_result, uint8_t endian);

void vcp_init ();
int vcp_send (uint8_t* buf, uint16_t len);
int vcp_recv (uint8_t* buf, uint16_t len);
void vcp_service (void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ UTILS_H */

/**
  * @}
  */

/**
  * @}
  */

/****END OF FILE****/
