	
/* Scheduler include files. */
#include "FreeRtOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
#include "uart.h"		//Explore Embedded UART library

/* Local Tasks declaration */
static void MyTask1(void* pvParameters);
static void MyTask2(void* pvParameters);
static void MyTask3(void* pvParameters);
static void MyIdleTask(void* pvParameters);

#define LED_IdleTask 0x01u
#define LED_Task1    0x02u
#define LED_Task2    0x04u
#define LED_Task3    0x08u
#define LED_Task4    0x10u

#define LED_PORT LPC_GPIO2->FIOPIN

int main(void)
{  
	SystemInit();			/* Initialize the controller */
	UART_Init(38400);		/* Initialize the Uart module */	
	LPC_GPIO2->FIODIR = 0xffffffffu;

	/* Create the three tasks with priorities 1,2,3. Only tasks will be created. 
	 * Tasks will be excecuted once the scheduler is started.
	 * An idle task is also created, which will be run when there are no tasks in RUN state */ 
	xTaskCreate( MyTask1, ( signed char * )"Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( MyTask2, ( signed char * )"Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( MyTask3, ( signed char * )"Task3", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	xTaskCreate( MyIdleTask, ( signed char * )"IdleTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

	UART_Printf("\n\rIn the main");
	
	vTaskStartScheduler();		/* Start the schedular */

	while(1);
}


/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
	while(1)
	{
		LED_PORT = 	LED_Task1;	  /* Led to indicate the execution of Task1*/
		UART_Printf("\n\rTask1");  
		vTaskDelay(15000);
	}
}

/* Task1 with priority 2 */
static void MyTask2(void* pvParameters)
{
	while(1)
	{
		LED_PORT = 	LED_Task2;	  /* Led to indicate the execution of Task2*/
		UART_Printf("\n\rTask2");
		vTaskDelay(6000);
	}
}

/* Task1 with priority 3 */
static void MyTask3(void* pvParameters)
{
	while(1)
	{
		LED_PORT = 	LED_Task3;	  /* Led to indicate the execution of Task3*/
		UART_Printf("\n\rTask3");
		vTaskDelay(6000);
	}
}

/* Task1 with priority 4 */
static void MyIdleTask(void* pvParameters)
{	
	while(1)
	{
		LED_PORT = 	LED_IdleTask;		 /* Led to indicate the execution of Idle Task*/
		UART_Printf("\n\rIn idle state");
	}									 
}

