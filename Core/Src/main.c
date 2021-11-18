/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STMPE610.h"
#include "SSD1963.h"
#include "GUI.h"
#include "Windows/MenuDLG.h"
#include "Windows/accWin.h"
#include "Windows/tempWin.h"
#include "ADXL345.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define TOUCH_KOORD
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;

I2C_HandleTypeDef hi2c1;

osThreadId defaultTaskHandle;
osThreadId acctempTaskHandle;
osThreadId buttonTaskHandle;
osMessageQId keyPressedQHandle;
/* USER CODE BEGIN PV */
WM_HWIN hWin,hWinText,hWinList;

int state = 0;
uint32_t i=0,j=0;
uint16_t rawADC=0;

float temp=0.0;

extern uint16_t x,y,z;
extern uint16_t accel_x, accel_y, accel_z;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC3_Init(void);
void StartDefaultTask(void const * argument);
void AccTemp_init(void const * argument);
void ButtonTask_init(void const * argument);

/* USER CODE BEGIN PFP */
extern volatile GUI_TIMER_TIME OS_TimeMS;
//void HAL_SYSTICK_Callback(void)
//{
//	OS_TimeMS++;
//}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */
  Init_LCD_GPIO();
  Init_TOUCH_GPIO(hi2c1);
  Init_ACCEL_GPIO(hi2c1);
  ADXL345_Init();


  WM_SetCreateFlags(WM_CF_MEMDEV); // eliminise flickering

  GUI_Init();


   i=0;
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of keyPressedQ */
  osMessageQDef(keyPressedQ, 5, uint32_t);
  keyPressedQHandle = osMessageCreate(osMessageQ(keyPressedQ), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of acctempTask */
  osThreadDef(acctempTask, AccTemp_init, osPriorityBelowNormal, 0, 512);
  acctempTaskHandle = osThreadCreate(osThread(acctempTask), NULL);

  /* definition and creation of buttonTask */
  osThreadDef(buttonTask, ButtonTask_init, osPriorityIdle, 0, 512);
  buttonTaskHandle = osThreadCreate(osThread(buttonTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x20404768;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PG15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
uint32_t suma(uint32_t x)
{
	return x+5;
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
	GUI_Clear();

	GUI_SetFont(&GUI_Font20_1);
	GUI_SetColor(GUI_RED);
	hWin = CreateMenu();

	vTaskSuspend(acctempTaskHandle);

  /* Infinite loop */
	for (;;)
	{
		uint32_t btnPressed;

		STMPE610_read_xyz();
		GUI_TOUCH_Exec();
		btnPressed = GUI_GetKey();

		osMessagePut(keyPressedQHandle, (uint32_t)btnPressed, 50);

		GUI_Delay(10);
		osDelay(10);
	}
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_AccTemp_init */
/**
* @brief Function implementing the acctempTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AccTemp_init */
void AccTemp_init(void const * argument)
{
  /* USER CODE BEGIN AccTemp_init */
  /* Infinite loop */
  for(;;)
  {

	  	  j+=3;
	  	  HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_15);
	  	  ADXL345_read_xyz();

	  	  HAL_ADC_Start(&hadc3);
	  	  HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
	  	  rawADC=HAL_ADC_GetValue(&hadc3);
	  	  temp=(float)rawADC;
	  	  temp=100.0*((temp)/(2048)-0.5);



	  	  if (state == ID_BTN_TEMP) {
	  		  char* temp_val;

	  		  temp_val = pvPortMalloc(4*sizeof(char));
	  		  uint8_t ostatak ;
	  		  float temp2;
	  		  temp2=temp*10;
	  		  ostatak = (uint8_t)temp2%10;
	  		  hWinList = WM_GetDialogItem(hWin, ID_LISTTEMP);
	  		  sprintf((char*)temp_val, "%d.%d", (uint16_t)temp,ostatak);

	  		  LISTVIEW_SetItemText(hWinList, 0, 0,temp_val );


	  		  vPortFree(temp_val);
	  	  }
	  	  osDelay(200);
  }
  /* USER CODE END AccTemp_init */
}

/* USER CODE BEGIN Header_ButtonTask_init */
/**
* @brief Function implementing the buttonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonTask_init */
void ButtonTask_init(void const * argument)
{
  /* USER CODE BEGIN ButtonTask_init */
	osEvent evt;
  /* Infinite loop */
  for(;;)
  {

	  evt = osMessageGet(keyPressedQHandle, 20);
	  uint32_t btnPressed;
	  btnPressed = (uint32_t)evt.value.p;
	  switch(btnPressed)
	  		{
	  			case ID_BTN_TEMP:
	  				WM_DeleteWindow(hWin);
	  				hWin = CreateTempWin();

	  				hWinList = WM_GetDialogItem(hWin, ID_LISTTEMP);

	  				vTaskResume(acctempTaskHandle);

	  				state = ID_BTN_TEMP;
	  				i += 2;
	  			break;
	  			case ID_BTN_ACC:
	  				WM_DeleteWindow(hWin);
	  				hWin = CreateAccWin();

	  				hWinText = WM_GetDialogItem(hWin, ID_TEXT_TEST);
	  				hWinList = WM_GetDialogItem(hWin, ID_LISTACC);

	  				vTaskResume(acctempTaskHandle);

	  				state = ID_BTN_ACC;

	  			break;
	  			case ID_BTN_NAZAD:
	  				GUI_Clear();
	  				WM_DeleteWindow(hWin);
	  				hWin = CreateMenu();
	  				vTaskSuspend(acctempTaskHandle);
	  				state = 0;
	  			break;
	  			case ID_BTN_NAZAD_TEMP:
	  				GUI_Clear();
	  				WM_DeleteWindow(hWin);
	  				hWin = CreateMenu();
	  				vTaskSuspend(acctempTaskHandle);
	  				state = 0;


	  			break;

	  	  	}
	  		if (state == ID_BTN_ACC) {
	  			char* acc_x_val;
	  			char* acc_y_val;
	  			char* acc_z_val;

//				j = TEXT_SetText(hWinText, test_string);
	  			acc_x_val = pvPortMalloc(6*sizeof(char));
	  			acc_y_val = pvPortMalloc(6*sizeof(char));
	  			acc_z_val = pvPortMalloc(6*sizeof(char));

	  			hWinList = WM_GetDialogItem(hWin, ID_LISTACC);
	  			sprintf((char*)acc_x_val, "%d", accel_x);
	  			sprintf((char*)acc_y_val, "%d", accel_y);
	  			sprintf((char*)acc_z_val, "%d", accel_z);
	  			LISTVIEW_SetItemText(hWinList, 0, 0, acc_x_val);
	  			LISTVIEW_SetItemText(hWinList, 1, 0, acc_y_val);
	  			LISTVIEW_SetItemText(hWinList, 2, 0, acc_z_val);


	  			vPortFree(acc_x_val);
	  			vPortFree(acc_y_val);
	  			vPortFree(acc_z_val);
	  		}
    osDelay(10);
  }
  /* USER CODE END ButtonTask_init */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM6) {
     OS_TimeMS++;
   }
  /* USER CODE END Callback 1 */
}

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
