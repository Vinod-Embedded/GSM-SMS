#include "main.h"
#include <string.h>
#include <stdio.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
	
uint8_t buf[30] = {0};
char mobile[] = "Mobile Number";  // Enter Your Mobile Number here

int main(void)
{
	char msg[30];
	char cmd[50];
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
	
	sprintf(msg,"SMS with GSM Module\r\n");
	HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
	sprintf(msg,"Checking Module...\r\n");
	HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
	uint8_t flag=1;
	
	while(flag){
		sprintf(cmd,"AT\r\n");
		HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
		HAL_UART_Receive_IT (&huart1, buf, 30);
		HAL_Delay(1000);
		
		if(strstr((char *)buf,"OK")){
			sprintf(msg,"Module Connected\r\n");
			HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
			flag=0;
		}
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2,(uint8_t *)buf,sizeof(buf),1000);
		memset(buf,0,sizeof(buf));
	}
	
	sprintf(msg,"Sending Message\r\n");
	HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
	sprintf(cmd,"AT+CMGF=1\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
	HAL_UART_Receive_IT (&huart1, buf, 30);
	HAL_Delay(1000);
	HAL_UART_Transmit(&huart2,(uint8_t *)buf,sizeof(buf),1000);
	memset(buf,0,sizeof(buf));
	
	sprintf(cmd,"AT+CMGS=\"%s\"\r\n",mobile);
	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
	HAL_Delay(100);
	sprintf(cmd,"Hello from GSM%c",0x1a);
	HAL_UART_Transmit(&huart1,(uint8_t *)cmd,strlen(cmd),1000);
	//HAL_UART_Transmit(&huart1,(uint8_t *)((char)(0x1a)),1,1000);
	HAL_UART_Receive_IT (&huart1, buf, 30);
	HAL_Delay(5000);
	
	HAL_UART_Transmit(&huart2,(uint8_t *)buf,sizeof(buf),1000);
	sprintf(msg,"Message Sent\r\n");
	HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
  while (1)
  {
    
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
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

static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
  
}
#endif 
