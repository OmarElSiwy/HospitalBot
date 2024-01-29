#include "Inc/TestMonitor.h"
#include "Inc/SampleTest.h"

void Test(void *NullParameters) {
  // Run Test Here
  
  LastTestRan.Passed = true;
  // DO NOT DELETE, THIS NOTIFIES THE MONITOR TASK
  strncpy((char*)LastTestRan.testName, "Task1Function", sizeof(LastTestRan.testName) - 1);
  LastTestRan.testName[sizeof(LastTestRan.testName) - 1] = '\0'; // Adds Termination Character
  xTaskNotifyGive(MonitorHandle); 
  vTaskDelete(NULL);
}
