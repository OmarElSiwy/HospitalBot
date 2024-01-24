#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

// Define Your Struct and Subsystem Details
typedef struct Subsystem{};

// Defining Functions that will be used in the Threads 
void StartDefaultTask(const void *argument);

// Defining Threads and Wrapping them with a Handler
osThreadId TaskHandlers[];
void Initialize() {
  osThreadDef(Task1, StartDefaultTask, osPriorityNormal, 0, 128);
  osThreadId TaskHandlers[] = {
    osThreadCreate(osThread(Task1), NULL)
  };
}

void InitSubSystem();
void StartDefaultTask(void const * argument);
