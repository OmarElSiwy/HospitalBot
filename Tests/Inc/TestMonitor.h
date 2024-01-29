#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis_os.h"
#include <stdbool.h>
#include "CommunicationProtocols/usart.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

// Signal Handler for Monitor Thread
extern TaskHandle_t MonitorHandle;

typedef struct TestInfo {
    char testName[32]; // Adjust size as needed
    bool Passed;
} TestInfo;

// Test Name:
extern volatile TestInfo LastTestRan;

void MonitorTask(void *NullParameters);

#ifdef __cplusplus
}
#endif
