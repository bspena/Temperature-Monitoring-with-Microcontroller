#include <LCD1602.h>

#include "stm32f4xx_hal.h"

// Macro dei pin usati nei collegamenti
#define RS_Pin GPIO_PIN_5
#define RS_GPIO_Port GPIOB

#define EN_Pin GPIO_PIN_4
#define EN_GPIO_Port GPIOB

#define D4_Pin GPIO_PIN_7
#define D4_GPIO_Port GPIOC

#define D5_Pin GPIO_PIN_6
#define D5_GPIO_Port GPIOB

#define D6_Pin GPIO_PIN_7
#define D6_GPIO_Port GPIOA

#define D7_Pin GPIO_PIN_6
#define D7_GPIO_Port GPIOA

// Handler del timer
#define timer htim1

// Definizione del ritardo in microsecondi
extern TIM_HandleTypeDef timer;
void delay (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while (__HAL_TIM_GET_COUNTER(&timer) < us);
}


// Funzione generica per l'invio dei dati/comando
void send_to_lcd (char data, int rs)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data>>0)&0x01));

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	delay (20);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
	delay (20);
}

// Funzione per l'invio del comando
void lcd_send_cmd (char cmd)
{
    char datatosend;

    // invio di 4 cifre alte
    datatosend = ((cmd>>4)&0x0f);

    // Per inviare il comando rs viene settato a 1
    send_to_lcd(datatosend,0);

    // invio di 4 cifre basse
    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

// Funzione per l'invio dei dati
void lcd_send_data (char data)
{
	char datatosend;

	// invio di 4 cifre alte
	datatosend = ((data>>4)&0x0f);

	// Per inviare i dati rs viene settato a zero
	send_to_lcd(datatosend, 1);

	// invio di 4 cifre basse
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

// Funzione per la pulizia del display
void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

// Funzione di selezione della posizione su cui scrivere
void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}


void lcd_init (void)
{
	// inizializzazione modalità 4 bit
	HAL_Delay(50);
	lcd_send_cmd (0x30);
	HAL_Delay(5);
	lcd_send_cmd (0x30);
	HAL_Delay(1);
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);
	HAL_Delay(10);

  // gestione del display (codici esadecimali dal datasheet)
	lcd_send_cmd (0x28); // definizione delle 2 linee e della matrice
	HAL_Delay(1);
	lcd_send_cmd (0x08); // spegnimento display e cursore
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); // incremento del cursore
	HAL_Delay(1);
	lcd_send_cmd (0x0C); // accensione display e spegnimento cursore
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
