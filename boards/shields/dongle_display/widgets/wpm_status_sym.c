/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */
 
#include <lvgl.h>

/* LVGL compatibility: some LVGL builds don't expose LV_IMG_CF_INDEXED_1BIT. */
#ifndef LV_IMG_CF_INDEXED_1BIT
/* LVGL v8 enum value for LV_IMG_CF_INDEXED_1BIT is 7 (UNKNOWN=0, RAW=1..3, TRUE_COLOR=4..6, INDEXED_1BIT=7). */
#define LV_IMG_CF_INDEXED_1BIT 7
#endif

#ifndef LV_ATTRIBUTE_IMG_SPEEDOMETER
#define LV_ATTRIBUTE_IMG_SPEEDOMETER
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SPEEDOMETER uint8_t sym_speedometer_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 
  0x00, 0x00, 
  0x00, 0x00, 
  0x0f, 0x80, 
  0x12, 0x40, 
  0x28, 0xa0, 
  0x40, 0x10, 
  0xa0, 0xa8, 
  0x81, 0x08, 
  0xc2, 0x18, 
  0x82, 0x08, 
  0x80, 0x08, 
  0x40, 0x10, 
  0x20, 0x20, 
};

const lv_img_dsc_t sym_speedometer = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.w = 14,
  .header.h = 14,
  .data_size = 36,
  .data = sym_speedometer_map,
};