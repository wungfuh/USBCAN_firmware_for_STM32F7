/**
  ******************************************************************************
  * File Name          : master.h
  * Description        : This file contains all the functions prototypes for 
  *                      the master.h
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MASTER_H
#define __MASTER_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "main.h"
#include "stdbool.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define CAN_MESSAGES_TO_UDP_BUFFER_SIZE	100
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

extern struct flags g_flags;
extern struct timers g_timers;
extern struct counters g_counters;
extern struct can_to_udp_message g_can_to_udp;
//uint16_t g_length;

struct flags {
	uint8_t time_set;
};

struct timers {
	uint32_t send_door_timer;
	uint32_t send_lights_timer;
	uint32_t can1_receive;
	uint32_t can2_receive;
	uint32_t can3_receive;
	uint32_t udp_receive;
};

struct counters {
	uint32_t can_message_index;
};


#pragma pack (1)
struct can_message {
	uint16_t can_id;
	uint16_t can_msg_id;
	uint32_t timestamp_high;
	uint16_t timestamp_low;
	uint8_t data[8];
};

#pragma pack (1)
struct can_to_udp_message {
	uint16_t protocol_version;
	uint16_t length;
	struct can_message can_messages[CAN_MESSAGES_TO_UDP_BUFFER_SIZE];
};



#ifdef __cplusplus
}
#endif
#endif /*__ MASTER_H */

/**
  * @}
  */

/**
  * @}
  */

/****END OF FILE****/
