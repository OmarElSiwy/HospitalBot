/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "CommunicationProtocols/gpio.h"
#include "stm32f401xe.h"
#include <stdint.h>

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/*
 * Configure All Unused Pins as ANALOG with NO PULL
 */
void InitializePins(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  static bool Initialized = false;
  if (Initialized) return;

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
}

void MX_GPIO_Analog_Init(uint32_t Pin, GPIO_TypeDef *group) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  if (group == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
  else if (group == GPIOB)__HAL_RCC_GPIOB_CLK_ENABLE();
  else if (group == GPIOC)__HAL_RCC_GPIOC_CLK_ENABLE();
  else if (group == GPIOD)__HAL_RCC_GPIOD_CLK_ENABLE();
  else if (group == GPIOH)__HAL_RCC_GPIOH_CLK_ENABLE();

  HAL_GPIO_Init(group, &GPIO_InitStruct);
}


void MX_GPIO_Input_Init(uint32_t Pin, GPIO_TypeDef *group) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  if (group == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
  else if (group == GPIOB)__HAL_RCC_GPIOB_CLK_ENABLE();
  else if (group == GPIOC)__HAL_RCC_GPIOC_CLK_ENABLE();
  else if (group == GPIOD)__HAL_RCC_GPIOD_CLK_ENABLE();
  else if (group == GPIOH)__HAL_RCC_GPIOH_CLK_ENABLE();

  HAL_GPIO_Init(group, &GPIO_InitStruct);
}


void MX_GPIO_Output_Init(uint32_t Pin, GPIO_TypeDef *group) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  if (group == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
  else if (group == GPIOB)__HAL_RCC_GPIOB_CLK_ENABLE();
  else if (group == GPIOC)__HAL_RCC_GPIOC_CLK_ENABLE();
  else if (group == GPIOD)__HAL_RCC_GPIOD_CLK_ENABLE();
  else if (group == GPIOH)__HAL_RCC_GPIOH_CLK_ENABLE();

  HAL_GPIO_Init(group, &GPIO_InitStruct);
}
