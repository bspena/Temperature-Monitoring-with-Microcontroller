#include "stm32f4xx_hal.h"

// Macro del pin dato
#define DHT_PORT GPIOA
#define DHT_PIN GPIO_PIN_1


uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM; uint8_t Presence = 0;

#include "DHT.h"

uint32_t DWT_Delay_Init(void)
{
  /* Disable TRC */
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
  /* Enable TRC */
  CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

  /* Disable clock cycle counter */
  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
  /* Enable  clock cycle counter */
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

  /* Reset the clock cycle counter value */
  DWT->CYCCNT = 0;

     /* 3 NO OPERATION instructions */
     __ASM volatile ("NOP");
     __ASM volatile ("NOP");
  __ASM volatile ("NOP");

  /* Check if clock cycle counter has started */
     if(DWT->CYCCNT)
     {
       return 0; /*clock cycle counter started*/
     }
     else
  {
    return 1; /*clock cycle counter not started*/
  }
}

__STATIC_INLINE void delay(volatile uint32_t microseconds)
{
  uint32_t clk_cycle_start = DWT->CYCCNT;

  /* Go to number of cycles for system */
  microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

  /* Delay till end */
  while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


// Funzione di inizializzazione del sensore
void DHT_Start (void)
{
	DWT_Delay_Init();

	// Imposta il pin della macro come output
	Set_Pin_Output (DHT_PORT, DHT_PIN);

	// Pone il pin basso
	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 0);
	delay (18000);

	// Pone il pin alto
    HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 1);
    delay (20);

    // Setta il pin per la ricezione dei dati
    Set_Pin_Input(DHT_PORT, DHT_PIN);
}

// Funzione per la comunizione seriale in cui il sensore comunica di essere attivo
uint8_t DHT_Check_Response (void)
{
	uint8_t Response = 0;
	delay (40);
	if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
	{
		delay (80);
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) Response = 1;
		else Response = -1;
	}

	// Attende che il pin vada basso
	while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));

	return Response;
}


// Funzione per lettura dei dati dall'ambiente
uint8_t DHT_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{

		// Si attende che il pin diventi alto
		while (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));
		delay (40);

		// Se il pin è basso
		if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
		{
			// Scrive 0
			i&= ~(1<<(7-j));
		}
		else i|= (1<<(7-j));  // Se il pin è alto, viene scritto 1
		while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));  // Si attende che il pin vada basso
	}
	return i;
}


void DHT_GetData (DHT_DataTypedef *DHT_Data)
{
    DHT_Start ();
	Presence = DHT_Check_Response ();
	Rh_byte1 = DHT_Read ();
	Rh_byte2 = DHT_Read ();
	Temp_byte1 = DHT_Read ();
	Temp_byte2 = DHT_Read ();
	SUM = DHT_Read();

	if (SUM == (Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2))
	{
		DHT_Data->Temperature = Temp_byte1;
		DHT_Data->Humidity = Rh_byte1;

	}
}


