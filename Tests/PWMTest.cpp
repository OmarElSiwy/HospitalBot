#include "CommunicationProtocols/pwm.h"
#include "Inc/TestMonitor.h"
#include "Inc/PWMTest.h"
#include "stm32f4xx_hal_tim.h"

void PWMTest(void *NullParameters) {
  // Run Test Here
  TIM4_PWM_Init();
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

  LastTestRan.Passed = true;
  // DO NOT DELETE, THIS NOTIFIES THE MONITOR TASK
  strncpy((char*)LastTestRan.testName, "Task1Function", sizeof(LastTestRan.testName) - 1);
  LastTestRan.testName[sizeof(LastTestRan.testName) - 1] = '\0'; // Adds Termination Character
  xTaskNotifyGive(MonitorHandle); 
  vTaskDelete(NULL);
}
