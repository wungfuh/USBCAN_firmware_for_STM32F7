/**
  ******************************************************************************
  * File Name          : utils.c
  * Description        : This file provides code for the configuration
  *                      of the utils.c instances.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "utils.h"
#include "master.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* Private variables ---------------------------------------------------------*/
extern struct timers g_timers;

/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN 1 */
void allLEDsOff(void) {
	HAL_GPIO_WritePin(RGB_R_1_GPIO_Port, RGB_R_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_G_1_GPIO_Port, RGB_G_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_B_1_GPIO_Port, RGB_B_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_R_2_GPIO_Port, RGB_R_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_G_2_GPIO_Port, RGB_G_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_B_2_GPIO_Port, RGB_B_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_R_3_GPIO_Port, RGB_R_3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_G_3_GPIO_Port, RGB_G_3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RGB_B_3_GPIO_Port, RGB_B_3_Pin, GPIO_PIN_SET);
}

/*
 * @brief 	Converts char array to float
 * @param 	char value[] - char array to be converted (4 bytes)
 * @param 	float *p_result - pointer to result float value
 * @param   uint8_t endian - endian type (0-little, 1-big)
 * @retval	none
 */
void char2float(char value[], float *p_result, uint8_t endian) {

switch (endian) {
	case CONVERT_LITTLE_ENDIAN:
		*((unsigned char *)(p_result) +0) = value[0];
		*((unsigned char *)(p_result) +1) = value[1];
		*((unsigned char *)(p_result) +2) = value[2];
		*((unsigned char *)(p_result) +3) = value[3];
		break;
	case CONVERT_BIG_ENDIAN:
		*((unsigned char *)(p_result) +3) = value[0];
		*((unsigned char *)(p_result) +2) = value[1];
		*((unsigned char *)(p_result) +1) = value[2];
		*((unsigned char *)(p_result) +0) = value[3];
		break;
	default:
		break;
	}
}

void buildCanFrameUSB(uint8_t* Frame, uint8_t data[],  CAN_TxHeaderTypeDef*  tx_header)
{
	uint8_t idx = 0;
	uint32_t messageID = 0;
	uint8_t messageLength = 0;
	if(Frame[idx] == 0x74)
	{
		for (int i = idx + 1; i <= 3; ++i)
		{
			messageID = (messageID << 4) | (Frame[i] < 0x39 ? Frame[i] & 0x0F : (Frame[i] + 0xA) - 0x41);
			idx++;
		}
		tx_header->IDE = CAN_ID_STD;
		tx_header->StdId = messageID;

	}
	else
	{
		for (int i = idx + 1; i < 3; ++i)
		{
			messageID = (messageID << 4) | (Frame[idx += 1] < 0x39 ? Frame[idx += 1] & 0x0F : (Frame[idx += 1] + 0xA) - 0x41);
			idx++;
		}
		tx_header->IDE = CAN_ID_EXT;
		tx_header->ExtId = messageID;
	}

	messageLength = Frame[idx + 1] & 0x0F;
	idx++;

	for(int i = 0; i < messageLength; ++i)
	{
		data[i] = 0;
		for (int j = 0; j < 2; ++j)
		{
			data[i] = (data[i] << 4) | (Frame[idx + 1] < 0x39 ? Frame[idx + 1] & 0x0F : (Frame[idx + 1] + 0xA) - 0x41);
			idx++;
		}
	}
	tx_header->DLC = messageLength;
	tx_header->RTR = CAN_RTR_DATA;

}



void buildCanFrame(uint8_t data[], CAN_RxHeaderTypeDef  rx_header, uint8_t* Frame, uint8_t* FrameLength )
{
	uint8_t idx = 0;
	uint32_t can_msg_id;
	uint8_t first = 0;
	if (rx_header.IDE == 0)
	{
		Frame[idx] = 0x74;
		can_msg_id = rx_header.StdId;
	}
	else
	{
		Frame[idx] = 0x54;
		can_msg_id = rx_header.ExtId;
	}


	for(int i = 0; i < 8; i++)
	{
		if (can_msg_id >> 28)
		{
			Frame[idx += 1] = (((can_msg_id >> 28) & 0xFF) < 0xA) ? (can_msg_id >> 28) + '0' : (can_msg_id >> 28) + 'A' - 10;

		}
		else if( first != 0)
		{
		    Frame[idx += 1] = (((can_msg_id >> 28) & 0xFF) < 0xA) ? (can_msg_id >> 28) + '0' : (can_msg_id >> 28) + 'A' - 10;
		}
		can_msg_id = can_msg_id << 4;

	}
	Frame[idx += 1] = ((rx_header.DLC & 0x0F) < 0xA) ? (rx_header.DLC & 0x0F) + '0' : (rx_header.DLC & 0xF) + 'A' - 10;


	for(int i = 0; i < rx_header.DLC; i++)
	{
		Frame[idx += 1] = (((data[i] >> 4) & 0xFF) < 0xA) ? (data[i] >> 4) + '0' : (data[i] >> 4) + 'A' - 10;
		Frame[idx += 1] = ((data[i] & 0x0F) < 0xA) ? (data[i] & 0x0F) + '0' : (data[i] & 0xF) + 'A' - 10;
	}
	Frame[idx += 1] = 0xD;
	*FrameLength = idx + 1 ;
}



void blinkLED(uint8_t blink_case) {

	switch (blink_case) {
		case LED_CAN1_RECEIVE:
			if (HAL_GetTick() - g_timers.can1_receive > LED_CAN1_RECEIVE_PERIOD_MS) {
				HAL_GPIO_TogglePin(CAN1_RECEIVE_LED_PORT, CAN1_RECEIVE_LED_PIN);
					g_timers.can1_receive = HAL_GetTick();
			}
			break;
		case LED_CAN2_RECEIVE:
			if (HAL_GetTick() - g_timers.can2_receive > LED_CAN2_RECEIVE_PERIOD_MS) {
				HAL_GPIO_TogglePin(CAN2_RECEIVE_LED_PORT, CAN2_RECEIVE_LED_PIN);
					g_timers.can2_receive = HAL_GetTick();
			}
			break;
		case LED_CAN3_RECEIVE:
			if (HAL_GetTick() - g_timers.can3_receive > LED_CAN3_RECEIVE_PERIOD_MS) {
				HAL_GPIO_TogglePin(CAN3_RECEIVE_LED_PORT, CAN3_RECEIVE_LED_PIN);
					g_timers.can3_receive = HAL_GetTick();
			}
			break;
		case LED_UDP_RECEIVE:
			if (HAL_GetTick() - g_timers.udp_receive > LED_UDP_RECEIVE_PERIOD_MS) {
				HAL_GPIO_TogglePin(UDP_RECEIVE_LED_PORT, UDP_RECEIVE_LED_PIN);
				g_timers.udp_receive = HAL_GetTick();
			}
			break;
		default:
			break;
	}

}



/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/****END OF FILE****/
