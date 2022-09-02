/*****************************************************************************
* | File      	:	DEV_Config.c
* | Author      :   Waveshare team
* | Function    :	Show SDcard BMP picto LCD 
* | Info        :
*   Provide the hardware underlying interface	 
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

static uint32_t slice_num;
static uint32_t motor_L;
static uint32_t motor_R;

void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
	gpio_put(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
	return gpio_get(Pin);
}

/**
 * GPIO Mode
**/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    gpio_init(Pin);
    if(Mode == 0 || Mode == GPIO_IN) {
        gpio_set_dir(Pin, GPIO_IN);
    } else {
        gpio_set_dir(Pin, GPIO_OUT);
    }
}

void DEV_GPIO_Init(void)
{
	DEV_GPIO_Mode(LCD_RST_PIN,GPIO_OUT);
    DEV_GPIO_Mode(LCD_DC_PIN, GPIO_OUT);
    DEV_GPIO_Mode(LCD_BKL_PIN, GPIO_OUT);
    DEV_GPIO_Mode(LCD_CS_PIN, GPIO_OUT);
    DEV_GPIO_Mode(TP_CS_PIN,GPIO_OUT);
    DEV_GPIO_Mode(TP_IRQ_PIN,GPIO_IN);
    DEV_GPIO_Mode(SD_CS_PIN,GPIO_OUT);
	gpio_set_pulls(TP_IRQ_PIN,true,false);

    DEV_Digital_Write(TP_CS_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 1);
    DEV_Digital_Write(LCD_BKL_PIN, 1);
    DEV_Digital_Write(SD_CS_PIN, 1);
}

/********************************************************************************
function:	PWM Init
note:
	PWM 함수
********************************************************************************/
void DEV_PWM_Init(void)
{	
	gpio_set_function(PWM_LED, GPIO_FUNC_PWM); // 핀기능 설정
  gpio_set_function(PWM_M_L, GPIO_FUNC_PWM);
  gpio_set_function(PWM_M_R, GPIO_FUNC_PWM);

  slice_num = pwm_gpio_to_slice_num(PWM_LED); // 2B
  motor_L = pwm_gpio_to_slice_num(PWM_M_L); // PWM_A0
  motor_R = pwm_gpio_to_slice_num(PWM_M_R); // PWM_B0

  pwm_set_clkdiv(slice_num, clock_get_hz(clk_sys)/1000000); //133,000,000
  pwm_set_clkdiv(motor_L, clock_get_hz(clk_sys)/1000000); //133,000,000
  pwm_set_clkdiv(motor_R, clock_get_hz(clk_sys)/1000000); //133,000,000

  pwm_set_wrap(slice_num, 255); // PWM 제어 샘플링 PWM 300값으로 고정
  pwm_set_wrap(motor_L, 1800); // 180도 제어 
  pwm_set_wrap(motor_R, 1800); 

  pwm_set_chan_level(slice_num, PWM_CHAN_B, 255); //GP25 - PWM B3
  pwm_set_chan_level(motor_L, PWM_CHAN_A, 1800); // GP0 - PWM A0
  pwm_set_chan_level(motor_R, PWM_CHAN_B, 1800); // GP0 - PWM B0

  pwm_set_enabled(slice_num, true);
  pwm_set_enabled(motor_L, true);
  pwm_set_enabled(motor_R, true);
}
 

void PWM_LED_ON(uint16_t val) // 
{

  

  pwm_set_chan_level(slice_num, PWM_CHAN_B, val);

}

void PWM_M_L_deg(uint16_t val) // 모터 LEFT 제어 60~90도 GPIO 0번
{  
//   pwm_duty = cmap(val, 0, 255, 0, 1000);
  // if(val >= 200 && val<= 255)
  pwm_set_chan_level(motor_L, PWM_CHAN_A, val);

}

void PWM_M_R_deg(uint16_t val) // 모터 RIGHT 제어 0~30도 GPTI 1번
{
  // if(val >= 200 && val<= 255)
//   pwm_duty = cmap(val, 0, 255, 0, 1000);

  pwm_set_chan_level(motor_R, PWM_CHAN_B, val);
}

void Motor_grab(void){
  PWM_M_L_deg(710);
  PWM_M_R_deg(1710);
}

void Motor_put(uint8_t deg){
  PWM_M_L_deg(710+(deg*11));
  PWM_M_R_deg(1710-(deg*11));
}

void PWMOFF(void) //  LED만 끝나도록 한다
{  
  pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
}
/********************************************************************************
function:	System Init
note:
	Initialize the communication method
********************************************************************************/
uint8_t System_Init(void)
{
	stdio_init_all();
	DEV_GPIO_Init();
	spi_init(SPI_PORT,15000000);
	gpio_set_function(LCD_CLK_PIN,GPIO_FUNC_SPI);
	gpio_set_function(LCD_MOSI_PIN,GPIO_FUNC_SPI);
	gpio_set_function(LCD_MISO_PIN,GPIO_FUNC_SPI);

    return 0;
}

void System_Exit(void)
{

}

/*********************************************
function:	Hardware interface
note:
	SPI4W_Write_Byte(value) : 
		Register hardware SPI
*********************************************/	
uint8_t SPI4W_Write_Byte(uint8_t value)                                    
{   
	uint8_t rxDat;
	spi_write_read_blocking(spi1,&value,&rxDat,1);
    return rxDat;
}

uint8_t SPI4W_Read_Byte(uint8_t value)                                    
{
	return SPI4W_Write_Byte(value);
}

/********************************************************************************
function:	Delay function
note:
	Driver_Delay_ms(xms) : Delay x ms
	Driver_Delay_us(xus) : Delay x us
********************************************************************************/
void Driver_Delay_ms(uint32_t xms)
{
	sleep_ms(xms);
}

void Driver_Delay_us(uint32_t xus)
{
	int j;
    for(j=xus; j > 0; j--);
}
