// Test Imports
#include "Inc/PWMTest.h"

// Tester Loop ______________________________________________________
#include "Inc/TestMonitor.h"

volatile TestInfo LastTestRan;

// Define the handle for MonitorTask
TaskHandle_t MonitorHandle = NULL;

void MonitorTask(void *pvParameters) {
  int NumberOfTests = 1;
  int counter = 1;

  MX_USART2_UART_Init();

  while (NumberOfTests > 0) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait for notification

    // Print the name of the task that sent the notification
    char buffer[100];
    sprintf(buffer, "Test %d (%s) %s\r\n", counter, LastTestRan.testName, LastTestRan.Passed ? "Passed" : "Failed");
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen((char*)buffer), 10);

    counter++;
    NumberOfTests--;
  }

  char buffer[] = {"All Tests have passed\r\n\r\n"};
  HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen((char*)buffer), 10);

}

// __________________________________________________________________

void SystemClock_Config(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();

  xTaskCreate(MonitorTask, "Monitor", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &MonitorHandle);
    
  // Add Other Tests Here
  xTaskCreate(PWMTest, "PWM Test", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

  osKernelStart();
}

void Error_Handler(void) {
  __disable_irq();
  while (1) {}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM9) {
    HAL_IncTick();
  }
}
