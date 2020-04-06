/**
 * @brief: 继电器
 */
#ifndef __DO_H
#define __DO_H

/**
 * @brief: 移植修改内容
 * @start{
 */
/* 使继电器闭合的引脚电平 */
#define DO_CLOSE_VALUE  1
/* 继电器及灯数量 */
#define DO_NUM          7
/* 引脚具体的定义 数量必须和 DO_NUM 对应 */
#define DO_PIN_CONFIG  { \
    /* DO1- 继电器 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_6, \
    /* DO2 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_7, \
    /* DO3 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_8, \
    /* DO4 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_9, \
    /* DO5 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_10, \
    /* DO6 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_11, \
    /* DO7 */ \
    RCC_APB2Periph_GPIOC, \
    GPIOC, \
    GPIO_Pin_12, \
}

#define ALL             (-1) /* 全部 */
/* 各个继电器的别名 可以不设置 */
#define RELAY           (0)  /* 继电器 */
#define LED             (1)  /* 灯 */
/**
 * @end}
 */

#define DO_LAST         (DO_NUM - 1) /* 最后一个继电器 */

typedef enum {
    do_close,
    do_open = !do_close
} do_state_t;

void do_init(void);
void do_set(int index, do_state_t state);
void do_triggle(int index);
do_state_t do_state(int index);

#endif /* __DO_H */
