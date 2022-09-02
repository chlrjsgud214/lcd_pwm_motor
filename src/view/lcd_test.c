/*****************************************************************************
* | File      	:   lcd_2in8.c
* | Author      :   Waveshare team
* | Function    :   2.9inch e-paper V2 test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-01-20
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "main.h"
#include "LCD_Driver.h"
#include "LCD_Touch.h"
#include "LCD_GUI.h"`
#include "LCD_Bmp.h"
#include "DEV_Config.h"`
#include <stdio.h>
#include "hardware/watchdog.h"
#include "pico/stdlib.h"



int lcd_test(void)
{
	//uint8_t counter = 0;
   	bspInit(); // USB COM Port 활성화 
	System_Init();
	SD_Init();
	DEV_PWM_Init();
	LCD_SCAN_DIR  lcd_scan_dir = SCAN_DIR_DFT;
	LCD_Init(lcd_scan_dir,800);
	TP_Init(lcd_scan_dir);
	// GUI_Show();	
	LCD_SCAN_DIR bmp_scan_dir = SCAN_DIR_DFT;
	LCD_Show_bmp(bmp_scan_dir,lcd_scan_dir);	
	TP_GetAdFac(); // 터치 캘리브레이션
	//TP_Dialog();
	// TP_gesvallist();
	//Driver_Delay_ms(50);
	TP_pwm_motor_main();
	// PWM_M_L_deg(400); // 1710 = 0 ~ 400 = 120
	// PWM_M_R_deg(1710); // 1725 = 0도 
	// Driver_Delay_ms(3000);
	// PWM_M_L_deg(1710);
	// PWM_M_R_deg(400); // 최소 동작 
	TP_pwm_motor_move(deg_val,true); // 초기 풀어진 상태 15도
	while(1){		
		TP_DrawBoard(); 
	}
	return 0;
}

