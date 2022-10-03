/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int counter = 100;
const int MAX_LED = 4;
const int MAX_LED_MATRIX = 8;
int index_led = 0;
int index_led_matrix = 0;
int led_buffer[4] = {1, 2, 3, 4};
uint16_t matrix_buffer[8] = {0xffff, 0x03ff, 0xedff, 0xeeff, 0xeeff, 0xedff, 0x03ff, 0xffff};
uint16_t zero[8] = {0xffff, 0xc1ff, 0x80ff, 0xbaff, 0xb6ff, 0xaeff, 0x80ff, 0xc1ff};
uint16_t one[8] = {0xffff, 0xbfff, 0xbfff, 0x80ff, 0x80ff, 0xbdff, 0xbfff, 0xffff};
uint16_t two[8] = {0xffff, 0x99ff, 0x90ff, 0xb6ff, 0xa6ff, 0x8eff, 0x9cff, 0xbdff};
uint16_t three[8] = {0xffff, 0xc9ff, 0x80ff, 0xb6ff, 0xb6ff, 0xb6ff, 0x9cff, 0xddff};
uint16_t four[8] = {0xffff, 0xafff, 0x80ff, 0x80ff, 0xacff, 0xe9ff, 0xe3ff, 0xe7ff};
uint16_t five[8] = {0xffff, 0xceff, 0x86ff, 0xb6ff, 0xb6ff, 0xb6ff, 0x90ff, 0xd0ff};
uint16_t six[8] = {0xffff, 0xcfff, 0x87ff, 0xb6ff, 0xb6ff, 0xb4ff, 0x81ff, 0xc3ff};
uint16_t seven[8] = {0xffff, 0xfcff, 0xf8ff, 0xf2ff, 0x86ff, 0x8eff, 0xfcff, 0xfcff};
uint16_t eight[8] = {0xffff, 0xc9ff, 0x80ff, 0xb6ff, 0xb6ff, 0xb6ff, 0x80ff, 0xc9ff};
uint16_t nine[8] = {0xffff, 0xe1ff, 0xc0ff, 0x96ff, 0xb6ff, 0xb6ff, 0xb0ff, 0xf9ff};

int hour = 15, minute = 8, second = 50;

void updateClockBuffer() {
	if (hour < 10) {
		led_buffer[0] = 0;
		led_buffer[1] = hour;
	} else {
		led_buffer[0] = hour / 10;
		led_buffer[1] = hour % 10;
	}

	if (minute < 10) {
		led_buffer[2] = 0;
		led_buffer[3] = minute;
	} else {
		led_buffer[2] = minute / 10;
		led_buffer[3] = minute % 10;
	}
}
void display7SEG(int num) {
  switch(num) {
	  case 0 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 1);
		  break;
	  }

	  case 1 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 1);
		  break;
	  }

	  case 2 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }
	  case 3 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }
	  case 4 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }
	  case 5 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }
	  case 6 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }
	  case 7 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 1);
		  break;
	  }
	  case 8 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }
	  case 9 : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 0);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 0);
		  break;
	  }

	  default : {
		  HAL_GPIO_WritePin(SEG7_0_GPIO_Port, SEG7_0_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_1_GPIO_Port, SEG7_1_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_2_GPIO_Port, SEG7_2_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_3_GPIO_Port, SEG7_3_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_4_GPIO_Port, SEG7_4_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_5_GPIO_Port, SEG7_5_Pin, 1);
		  HAL_GPIO_WritePin(SEG7_6_GPIO_Port, SEG7_6_Pin, 1);
		  break;
	  }
  }
}
void update7SEG(int index){
	switch(index) {
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 0); // turn on the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 1); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 1); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 1); // turn off the fourth SEG
			display7SEG(led_buffer[0]);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 1); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0); // turn on the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 1); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 1); // turn off the fourth SEG
			display7SEG(led_buffer[1]);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 1); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 1); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0); // turn on the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 1); // turn off the fourth SEG
			display7SEG(led_buffer[2]);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 1); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 1); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 1); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 0); // turn on the fourth SEG
			display7SEG(led_buffer[3]);
			break;
		default:
			break;
	}
}
  void updateLEDMatrix(int index){
      switch (index){
          case 0:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = zero[i];
          	}
              break;
          case 1:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = one[i];
          	}
              break;
          case 2:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = two[i];
          	}
              break;
          case 3:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = three[i];
          	}
              break;
          case 4:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = four[i];
          	}
              break;
          case 5:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = five[i];
          	}
              break;
          case 6:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = six[i];
          	}
              break;
          case 7:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = seven[i];
          	}
              break;
          case 8:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = eight[i];
          	}
          	break;
          case 9:
          	for (int i = 0; i < 8; i++) {
          		matrix_buffer[i] = nine[i];
          	}
          	break;
          default:
              break;
      }
  }
void shift_left(uint16_t array[8]) {
	uint16_t temp = array[7];
	for (int i = 7; i > 0; i--) {
		array[i] = array[i - 1];
	}
	array[0] = temp;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int i = -1;
  setTimer1(2);
  while (1)
  {
	  if (timer1_flag == 1) {
		 // Display character 'A'

		  setTimer1(1);
		  i++;
		  if (i >= MAX_LED_MATRIX) {
			  i = 0;

		  }
		  GPIOA->ODR = ~0x8000 >> i;
		  GPIOB->ODR = matrix_buffer[i];
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 799;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, EN2_Pin|EN3_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|ENM0_Pin|ENM1_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG7_0_Pin|SEG7_1_Pin|SEG7_2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG7_3_Pin|SEG7_4_Pin|SEG7_5_Pin
                          |SEG7_6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EN2_Pin EN3_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin ENM0_Pin ENM1_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = EN2_Pin|EN3_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|ENM0_Pin|ENM1_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG7_0_Pin SEG7_1_Pin SEG7_2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG7_3_Pin SEG7_4_Pin SEG7_5_Pin
                           SEG7_6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG7_0_Pin|SEG7_1_Pin|SEG7_2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG7_3_Pin|SEG7_4_Pin|SEG7_5_Pin
                          |SEG7_6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int dem = 10;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
