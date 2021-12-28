/**
 * @file tuya_demo_seg_lcd_driver.h
 * @author lifan
 * @brief segment lcd driver demo header file
 * @version 1.0
 * @date 2021-09-18
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#ifndef __TUYA_DEMO_SEG_LCD_DRIVER_H__
#define __TUYA_DEMO_SEG_LCD_DRIVER_H__

#include "tuya_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************micro define************************
***********************************************************/

/***********************************************************
***********************typedef define***********************
***********************************************************/

/***********************************************************
***********************variable define**********************
***********************************************************/

/***********************************************************
***********************function define**********************
***********************************************************/
/**
 * @brief segment lcd driver init
 * @param[in] none
 * @return none
 */
VOID_T tuya_seg_lcd_driver_init(VOID_T);

/**
 * @brief dp data handler
 * @param[in] dp_data: dp data array
 * @return none
 */
VOID_T tuya_ble_dp_write_handler(IN UCHAR_T *dp_data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TUYA_DEMO_SEG_LCD_DRIVER_H__ */
