/**
******************************************************************************
* @file   : *.cpp
* @author : shentq
* @version: V1.2
* @date   : 2016/08/14

* @brief   ebox application example .
*
* Copyright 2016 shentq. All Rights Reserved.
******************************************************************************
*/

#include "ebox.h"
#include "math.h"
#include "colorled.h"
#include "nokia5110.h"
#include "button.h"
#include "parallel_gpio.h"

#define KEY_UP PC5
#define KEY_DOWN PA15

NOKIA5110 lcd;
Button key_up(&KEY_UP, 1);
Button key_down(&KEY_DOWN, 1);


void setup()
{
	ebox_init();
	uart1.begin(115200);
	lcd.begin();
	key_up.begin();
	key_down.begin();
}

unsigned char digitOut = 0;


int main(void)
{
	setup();

	//lcd.disp_string(0, 0, "  Welcome to  ");
	//lcd.disp_string(0, 1, "  ebox world ");
	//lcd.disp_string(0, 2, "cloudmaker.org");
	//lcd.disp_string(0, 3, " Nokia5110 LCD");
	//lcd.write_chinese_string(12, 4, 12, 4, 0, 5);

	while (1)
	{
		key_up.loop();
		key_down.loop();
		
		if (key_up.click())
		{
			digitOut++;
		}
		if (key_up.pressed_for(1000, 0))
		{
			digitOut++;
		}
		if (key_down.click())
		{
			digitOut--;
		}
		if (key_down.pressed_for(1000, 0))
		{
			digitOut--;
		}
		lcd.printf(0, 2, "digitOut:%u    ", digitOut);
		delay_ms(5);
	}

}




