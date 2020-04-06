/**
 * @brief: 按钮
 */

#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/**
 * @brief: 移植修改内容
 * @start{
 */
/* 按钮个数 */
#define KEY_NUM         6
/* 引脚具体的定义 数量必须和 KEY_NUM 对应 */
#define KEY_PIN_CONFIG  { \
    /* key1 */ \
    RCC_APB2Periph_GPIOB, \
    GPIOB, \
    GPIO_Pin_2, \
    /* key2 */ \
    RCC_APB2Periph_GPIOB, \
    GPIOB, \
    GPIO_Pin_3, \
    /* key3 */ \
    RCC_APB2Periph_GPIOB, \
    GPIOB, \
    GPIO_Pin_4, \
    /* key4 */ \
    RCC_APB2Periph_GPIOB, \
    GPIOB, \
    GPIO_Pin_5, \
    /* key5 */ \
    RCC_APB2Periph_GPIOB, \
    GPIOB, \
    GPIO_Pin_6, \
    /* key6 */ \
    RCC_APB2Periph_GPIOB, \
    GPIOB, \
    GPIO_Pin_7, \
}
/**
 * @end}
 */

typedef enum {
    key_no_press,
    key_pressing,
    key_pressed,
    key_click = !key_no_press
} key_state_t;

typedef struct {
    /* 时钟 */
    uint32_t RCC_APB2Periph;
    /* 端口 */
    GPIO_TypeDef *GPIOx;
    /* 引脚 */  
    uint16_t GPIO_Pin;
} key_pin_t;

typedef struct {
    /* 之前状态 */
    key_state_t pre_state;
    /* 当前状态 */
    key_state_t state;
    /* 引脚配置 */
    key_pin_t pin_cfg;
} key_t;

extern key_t key[];

void key_init(void);
void key_read(void);
int key_clicked(uint32_t index);

#endif /* __KEY_H */
