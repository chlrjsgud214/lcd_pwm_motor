/*
 * lcd_fonts.h
 *
 *  Created on: 2020. 12. 30.
 *      Author: baram
 */

#ifndef SRC_COMMON_HW_INCLUDE_LCD_LCD_FONTS_H_
#define SRC_COMMON_HW_INCLUDE_LCD_LCD_FONTS_H_

#include <stdio.h>
#include <stdint.h>

#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  uint8_t   width;
  uint8_t   height;
  const uint16_t *data; 
} lcd_font_t;


extern lcd_font_t font_07x10;
extern lcd_font_t font_11x18;
extern lcd_font_t font_16x26;
extern lcd_font_t font_hangul;


#endif /* SRC_COMMON_HW_INCLUDE_LCD_LCD_FONTS_H_ */
