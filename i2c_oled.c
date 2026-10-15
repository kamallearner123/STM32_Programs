#include "main.h"
#include "ssd1306.h"

extern I2C_HandleTypeDef hi2c1;

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();

    SSD1306_Init(&hi2c1, 0x3C);
    SSD1306_Clear();

    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("STM32 NUCLEO",
                       Font_7x10, White);

    SSD1306_SetCursor(0, 20);
    SSD1306_WriteString("I2C OLED",
                       Font_7x10, White);

    SSD1306_UpdateScreen();

    while (1)
    {
        HAL_Delay(1000);
    }
}
