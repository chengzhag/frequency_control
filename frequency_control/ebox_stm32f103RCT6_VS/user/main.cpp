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
#include "interpolation.h"

#define KEY_UP PC5
#define KEY_DOWN PA15



NOKIA5110 lcd;
Button key_up(&KEY_UP, 1);
Button key_down(&KEY_DOWN, 1);
ParallelGpio gpioOut;
unsigned char digitOut = 1;
double fc = 0;

static double interOut[] = {1,3,5,7,12,14,19,20,22,29,\
34,36,48,53,68,83,101,116,131,141,163,182,209,228,254};
static double interFc[] = {20,60,184,244,250,300,400,\
500,550,600,700,800,1000,1200,1500,1800,2200,\
2500,2800,3000,3500,4000,4500,5000,5500 };
sky::Interpolation interpolation(interOut, interFc,25);

void setup()
{
	ebox_init();
	uart1.begin(115200);
	lcd.begin();
	key_up.begin();
	key_down.begin();
	gpioOut.bit[0] = &PB7;
	gpioOut.bit[1] = &PB6;
	gpioOut.bit[2] = &PB5;
	gpioOut.bit[3] = &PB4;
	gpioOut.bit[4] = &PB3;
	gpioOut.bit[5] = &PB2;
	gpioOut.bit[6] = &PB1;
	gpioOut.bit[7] = &PB0;
	gpioOut.mode(OUTPUT_PP);

}




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
			if (digitOut == 0)
			{
				digitOut = 255;
			}
		}
		if (key_up.pressed_for(1000, 0))
		{
			digitOut++;
			if (digitOut == 0)
			{
				digitOut = 255;
			}
		}
		if (key_down.click())
		{
			digitOut--;
			if (digitOut == 0)
			{
				digitOut = 1;
			}
		}
		if (key_down.pressed_for(1000, 0))
		{
			digitOut--;
			if (digitOut == 0)
			{
				digitOut = 1;
			}
		}

		lcd.printf(0, 2, "digitOut:%u    ", digitOut);
		fc = interpolation(digitOut);
		lcd.printf(0, 3, "fc:%.0fHz    ", fc);
		gpioOut.write(digitOut);
		delay_ms(20);
	}

}




