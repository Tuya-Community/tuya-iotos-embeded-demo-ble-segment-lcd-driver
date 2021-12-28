/**
 * @file tuya_demo_seg_lcd_driver.c
 * @author lifan
 * @brief segment lcd driver demo source file
 * @version 1.0
 * @date 2021-09-24
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#include "tuya_demo_seg_lcd_driver.h"
#include "tuya_seg_lcd.h"
#include "tuya_timer.h"
#include "tuya_ble_log.h"

/***********************************************************
************************micro define************************
***********************************************************/
/* LED flash settings */
#define SEG_LCD_FLASH_INTV  300
#define SEG_LCD_FLASH_COUNT 3

/* DP ID */
#define DP_ID_SEG_LCD_MODE  101
#define DP_ID_SEG_LCD_DISP  102

/***********************************************************
***********************typedef define***********************
***********************************************************/
typedef BYTE_T SEG_LCD_MODE_E;
#define MODE_LIGHT_ON       0x00
#define MODE_LIGHT_OFF      0x01
#define MODE_FLASH          0x02
#define MODE_FLASH_DIGIT    0x03

typedef BYTE_T SEG_LCD_DISP_E;
#define DISP_NUM            0x00
#define DISP_STRING         0x01
#define DISP_CHAR           0x02
#define DISP_CUSTOM_CHAR    0x03

/***********************************************************
***********************variable define**********************
***********************************************************/
/* Segment LCD user define */
STATIC SEG_LCD_PIN_T sg_seg_lcd_pin_s = {
    .com = {TY_GPIOA_1, TY_GPIOC_2, TY_GPIOC_3, TY_GPIOB_4},
    .seg = {TY_GPIOA_0, TY_GPIOC_0, TY_GPIOD_3, TY_GPIOC_1, TY_GPIOC_4, TY_GPIOB_5}
};

/***********************************************************
***********************function define**********************
***********************************************************/
/**
 * @brief segment lcd driver init
 * @param[in] none
 * @return none
 */
VOID_T tuya_seg_lcd_driver_init(VOID_T)
{
    tuya_seg_lcd_init(sg_seg_lcd_pin_s);
    tuya_seg_lcd_disp_num(0, 0);
    tuya_seg_lcd_set_light(TRUE);
}

/**
 * @brief segment lcd flash end callback function
 * @param[in] none
 * @return none
 */
STATIC VOID_T __seg_lcd_flash_end_cb()
{
    TUYA_APP_LOG_INFO("Segment LCD flash ends.");
}

/**
 * @brief set segment lcd mode
 * @param[in] mode: set segment driver mode
 * @return none
 */
STATIC VOID_T __set_seg_lcd_mode(IN CONST SEG_LCD_MODE_E mode)
{
    switch (mode) {
    case MODE_LIGHT_ON:
        {
            tuya_seg_lcd_set_light(TRUE);
            TUYA_APP_LOG_INFO("Segment LCD is light on.");
        }
        break;
    case MODE_LIGHT_OFF:
        {
            tuya_seg_lcd_set_light(FALSE);
            TUYA_APP_LOG_INFO("Segment LCD is light off.");
        }
        break;
    case MODE_FLASH:
        {
            tuya_seg_lcd_set_flash(SEG_LCD_FLASH_DIGIT_ALL, SLFT_STA_ON_END_ON, SEG_LCD_FLASH_INTV, SEG_LCD_FLASH_FOREVER, NULL);
            TUYA_APP_LOG_INFO("Segment LCD is flashing.");
        }
        break;
    case MODE_FLASH_DIGIT:
        {
            tuya_seg_lcd_set_flash(0, SLFT_STA_ON_END_ON, SEG_LCD_FLASH_INTV, SEG_LCD_FLASH_COUNT, __seg_lcd_flash_end_cb);
            TUYA_APP_LOG_INFO("Segment LCD's digit 0 will flash 3 times.");
        }
        break;
    default:
        break;
    }
}

/**
 * @brief set segment lcd display content
 * @param[in] disp: set segment display mode
 * @return none
 */
STATIC VOID_T __set_seg_lcd_disp(IN CONST SEG_LCD_DISP_E disp)
{
    switch (disp) {
    case DISP_NUM:
        {
            tuya_seg_lcd_disp_num(12, 1);
            TUYA_APP_LOG_INFO("Segment LCD display number.");
        }
        break;
    case DISP_STRING:
        {
            tuya_seg_lcd_disp_str("---");
            TUYA_APP_LOG_INFO("Segment LCD display string.");
        }
        break;
    case DISP_CHAR:
        {
            tuya_seg_lcd_disp_ch('3', 0);
            tuya_seg_lcd_disp_ch('2', 1);
            tuya_seg_lcd_disp_ch('1', 2);
            TUYA_APP_LOG_INFO("Segment LCD display character.");
        }
        break;
    case DISP_CUSTOM_CHAR:
        {
            SEG_LCD_CH_T cus_ch;
            cus_ch.a = 0;
            cus_ch.b = 0;
            cus_ch.c = 1;
            cus_ch.d = 0;
            cus_ch.e = 1;
            cus_ch.f = 0;
            cus_ch.g = 1;
            cus_ch.dp = 0;
            tuya_seg_lcd_disp_custom_ch(cus_ch, 0);
            tuya_seg_lcd_disp_custom_ch(cus_ch, 1);
            tuya_seg_lcd_disp_custom_ch(cus_ch, 2);
            TUYA_APP_LOG_INFO("Segment LCD display custom character.");
        }
        break;
    default:
        break;
    }
}

/**
 * @brief dp data handler
 * @param[in] dp_data: dp data array
 * @return none
 */
VOID_T tuya_ble_dp_write_handler(IN UCHAR_T *dp_data)
{
    switch (dp_data[0]) {
    case DP_ID_SEG_LCD_MODE:
        __set_seg_lcd_mode(dp_data[3]);
        break;
    case DP_ID_SEG_LCD_DISP:
        __set_seg_lcd_disp(dp_data[3]);
        break;
    default:
        break;
    }
}
