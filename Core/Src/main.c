/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
	#include "st7735\st7735.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LIGA_LEDS HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 + GPIO_PIN_4 + GPIO_PIN_5 + GPIO_PIN_6, 1)
#define LE_BOTAO_CIMA HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
#define LE_BOTAO_DIREITO HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)
#define LE_BOTAO_BAIXO HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)
#define TAMANHO_TABULEIRO 3
#define JOGADOR1 'X'
#define JOGADOR2 'O'
#define VAZIO ' '
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
static int tabuleiro[3][3];
int placar_jogador1 = 0;
int placar_jogador2 = 0;
int rodadas_jogador1 = 0;
int rodadas_jogador2 = 0;
static int cursor_coluna = 0;
static int cursor_linha = 0;
int jogador_atual = 1; // X É 1
int x;
int y;
int n;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  	  ST7735_Init();
  	ST7735_FillScreen(BLACK);

	  //////////////////////////////////////////////////////////// AQUI ////////////////////////////////////////////

	if ( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) ==0)
	{
		LIGA_LEDS;
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  inicializar_tabuleiro();
	  ChamaHashtag();
	  mover();

	  //   jogar_partida();
	  //  jogar_melhor_de_tres();

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin PB3 PB4
                           PB5 PB6 */
   GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void mover(void)
{

 //desenha_pela_coordenada( cursor_linha, cursor_coluna);

	if (LE_BOTAO_DIREITO == 0)
	{

		cursor_coluna = (cursor_coluna + 1) % 3;
		if (cursor_coluna ==0)
		{
	   	   cursor_linha = (cursor_linha + 1) % 3;
		}

            desenha_pela_coordenada( cursor_linha, cursor_coluna);
	}
	else if (LE_BOTAO_BAIXO == 0)
	{

		cursor_coluna = (cursor_coluna - 1 + 3) % 3;
		if (cursor_coluna == 3 - 1)
		{
	   	   cursor_linha = (cursor_linha - 1 + 3) % 3;
		}

	   desenha_pela_coordenada( cursor_linha, cursor_coluna);
	}
}

void  Definir_local(int cursor_linha, int cursor_coluna, int jogadorAtual)
{
for (int i = 0; i<3; i++)
{
for (int j = 0; j<3; j++)
{
if (jogador_atual == 1)
{
jogador_atual = 2;
}
else
{
jogador_atual = 1;
}

if (i == cursor_linha && j == cursor_coluna )
{
   desenha_pela_coordenada( cursor_linha,  cursor_coluna);
}
else
{
desenha_pela_coordenada( i,  j );
}

}
}
}

void inicializar_tabuleiro() //ESVAZIA O TABULEIRO
 {
     for (int i = 0; i < 3; i++)
     {
         for (int j = 0; j < 3; j++)
         {
             tabuleiro[i][j] = VAZIO;
         }
     }
 }

 void exibir_tabuleiro()
 {
	 ST7735_WriteString(100,15,"PLACAR", Font_7x10, WHITE, BLACK);
	 ST7735_WriteString(60,15,"Jogador 1:  \n",Font_7x10, WHITE, BLACK);
	 ST7735_WriteString(60,15,"Jogador 2:  \n",Font_7x10, WHITE, BLACK);

     for (int i = 0; i < TAMANHO_TABULEIRO; i++)
     {
         for (int j = 0; j < TAMANHO_TABULEIRO; j++)
         {
        		desenha_pela_coordenada(i, j);

         }
         ST7735_WriteString(60,15," \n ",Font_7x10, WHITE, BLACK);

     }
 }

 void efetuar_jogada(int cursor_linha, int cursor_coluna)
  {
     if (tabuleiro[cursor_linha][cursor_coluna] == VAZIO) {
         if (jogador_atual == 1)
  {
        	 ST7735_FillScreen(BLUE);
 	desenha_pela_coordenada(cursor_linha,  cursor_coluna);

         } else {
        	 ST7735_FillScreen(BLUE);
          desenha_pela_coordenada( cursor_linha, cursor_coluna);
         }
     }
 }

 void alternar_jogador()
  {
  if (jogador_atual == 1)
 {
 jogador_atual = 2;
 }
 else
 {
 jogador_atual = 1;
 }
 }




 void jogar_partida()
 {
     int jogadas = 0;
     while (1) {



         ST7735_WriteString(100,10,"Faça sua jogada.\n", Font_7x10, WHITE, BLACK);
     mover();
         efetuar_jogada( cursor_linha,  cursor_coluna);
         jogadas++;

         if (verificar_vencedor(n, jogador_atual) == 1)
         {
             if (jogador_atual == 1) {
                 placar_jogador1++;
                 rodadas_jogador1++;
                 ST7735_WriteString(100,10,"Jogador X venceu esta rodada!", Font_7x10, WHITE, BLACK);
             } else {
                 placar_jogador2++;
                 rodadas_jogador2++;
                 ST7735_WriteString(100,10,"Jogador O venceu esta rodada!", Font_7x10, WHITE, BLACK);
             }
             break;
         } else if (jogadas == 9)
         {
             ST7735_WriteString(100,10,"Empate!", Font_7x10, WHITE, BLACK);

             break;
         }

         alternar_jogador();
     }
 }

 void jogar_melhor_de_tres()
 {
     while (1) {
         jogar_partida();

         if (rodadas_jogador1 == 2) {
        	 ST7735_WriteString(100,10,"Jogador 1 venceu a partida!", Font_7x10, WHITE, BLACK);
             placar_jogador1 = 0;
             placar_jogador2 = 0;
             rodadas_jogador1 = 0;
             rodadas_jogador2 = 0;
             break;
         } else if (rodadas_jogador2 == 2) {
        	 ST7735_WriteString(100,10,"Jogador 2 venceu a partida!", Font_7x10, WHITE, BLACK);
             placar_jogador1 = 0;
             placar_jogador2 = 0;
             rodadas_jogador1 = 0;
             rodadas_jogador2 = 0;
             break;
         }
     }
 }
 void ChamaHashtag()
 	 {

	 	    ST7735_DrawLine(10, 50, 79, 50, WHITE);
	 	    ST7735_DrawLine(10, 20, 79, 20, WHITE);
	 	    ST7735_DrawLine(30, 70, 30, 5, BLUE);
	 	    ST7735_DrawLine(60, 70, 60, 5, BLUE);
	 			    			    HAL_Delay(0);
	 	ST7735_WriteString(100,15,"PLACAR", Font_7x10, WHITE, BLACK);

 	 }

 int verificar_vencedor(int n, int jogador_atual)
 {
  int tabuleiro_de_0[9] = {0,0,0,0,0,0,0,0,0};
   tabuleiro_de_0[n] = jogador_atual;

  if (tabuleiro_de_0[0] == tabuleiro_de_0[1] && tabuleiro_de_0[1] == tabuleiro_de_0[2]  )
     {
     return 1;
     }
 else if(tabuleiro_de_0[3] == tabuleiro_de_0[4] && tabuleiro_de_0[4] == tabuleiro_de_0[5])
 {
  return 1;
 }
 else if (tabuleiro_de_0[6] == tabuleiro_de_0[7] && tabuleiro_de_0[7] == tabuleiro_de_0[8])
 {
  return 1;
 }
 else if (tabuleiro_de_0[0] == tabuleiro_de_0[3] && tabuleiro_de_0[3] == tabuleiro_de_0[6])
 {
 return 1;
 }
 else if (tabuleiro_de_0[1] == tabuleiro_de_0[4] && tabuleiro_de_0[4] == tabuleiro_de_0[7])
 {
 return 1;
 }
 else if (tabuleiro_de_0[2] == tabuleiro_de_0[5] && tabuleiro_de_0[5] == tabuleiro_de_0[6])
 {
 return 1;
 }
 else if (tabuleiro_de_0[0] == tabuleiro_de_0[4] && tabuleiro_de_0[4] == tabuleiro_de_0[8])
 {
 return 1;
 }
 else if (tabuleiro_de_0[2] == tabuleiro_de_0[4] && tabuleiro_de_0[4] == tabuleiro_de_0[6])
 {
 return 1;
 }
 }



 void desenha_pela_coordenada(int a, int b)
 {
 int vetor[3][3];

vetor [0][0] = 0;
 vetor [0][1] = 1;
 vetor [0][2] = 2;
 vetor [1][0] = 3;
 vetor [1][1] = 4;
 vetor [1][2] = 5;
 vetor [2][0] = 6;
 vetor [2][1] = 7;
 vetor [2][2] = 8;



int vetora[a][b];

int n = vetora[a][b];

 for (int i = 0; i <9; i++ )
 {
if (n == 0)
 {
    x = 15; y = 2;
    i = 9;
 }
 else if (n == 1)

 {
    x = 39  ; y = 2;
    i = 9;
 }

 else if (n == 2 )

 {
    x = 67  ; y = 2;
    i = 9;
 }

 else if (n == 3)

 {
    x = 15 ; y = 25;
    i = 9;
 }
 else if (n == 4)

 {
    x = 39  ; y = 25;
    i = 9;
 }

 else if (n == 5)
 {
    x = 67  ; y = 25;
    i = 9;
 }

 else if (n == 6)
 {
    x = 15  ; y = 55;
    i = 9;
 }

 else if (n == 7)
 {
    x = 39  ; y = 55;
    i = 9;
 }

 else if (n == 8)
 {
    x = 67  ; y = 55;
    i = 9;
 }

 }

 if (jogador_atual == 1)
 {
	 ST7735_WriteString(x, y,"X", Font_11x18, WHITE, BLACK);

 }
 else if (jogador_atual == 2)
 {
	 ST7735_WriteString(x, y,"O", Font_11x18, WHITE, BLACK);

 }
 else if (jogador_atual == 0)
 {
	 ST7735_WriteString(x, y," ", Font_11x18, WHITE, BLACK);

 }
 }



/* USER CODE END 4 */

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
