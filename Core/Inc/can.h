/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "canid.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

extern CAN_HandleTypeDef hcan2;

extern CAN_HandleTypeDef hcan3;

/* USER CODE BEGIN Private defines */
#define CAN_MESSAGE_LENGTH 	18
#define MAX_BUFFER_SIZE		100 * CAN_MESSAGE_LENGTH + 4
/* USER CODE END Private defines */

void MX_CAN1_Init(void);
void MX_CAN2_Init(void);
void MX_CAN3_Init(void);

extern uint32_t CAN_PRESCALER;
extern uint32_t CAN_TIMSEQ1;
extern uint32_t CAN_TIMESEQ2;

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef CANTransmit(CAN_TypeDef *device_id, uint8_t buffer[], CAN_TxHeaderTypeDef tx_header);
HAL_StatusTypeDef CANReceive(CAN_HandleTypeDef *hcan);
void CAN1_Config_Filters(void);
void CAN2_Config_Filters(void);
void CAN3_Config_Filters(void);
void handleCANMessage(CAN_RxHeaderTypeDef  rx_header, uint8_t rx_data[], CAN_TypeDef *hcan);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

