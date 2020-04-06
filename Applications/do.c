#include "stm32f10x.h"
#include "do.h"

typedef struct {
    /* 时钟 */
    uint32_t RCC_APB2Periph;
    /* 端口 */
    GPIO_TypeDef *GPIOx;
    /* 引脚 */  
    uint16_t GPIO_Pin;
} do_t;

do_t dout[DO_NUM];

void do_init(void)
{
    GPIO_InitTypeDef init;
    do_t do_pin_cfg[DO_NUM] = DO_PIN_CONFIG;

    init.GPIO_Mode = GPIO_Mode_Out_PP;
    init.GPIO_Speed = GPIO_Speed_10MHz;
    for (int i = 0; i < DO_NUM; i++) {
        RCC_APB2PeriphClockCmd(do_pin_cfg[i].RCC_APB2Periph, ENABLE);
        init.GPIO_Pin = do_pin_cfg[i].GPIO_Pin;
        GPIO_Init(do_pin_cfg[i].GPIOx, &init);
        dout[i].RCC_APB2Periph = do_pin_cfg[i].RCC_APB2Periph;
        dout[i].GPIO_Pin = do_pin_cfg[i].GPIO_Pin;
        dout[i].GPIOx = do_pin_cfg[i].GPIOx;
    }
}

/**
 * @brief   sth
 * @param   None
 * @retval  None
 */
static void _do_set(int index, do_state_t state)
{
    if (state == do_close) {
        #if DO_CLOSE_VALUE
            GPIO_SetBits(dout[index].GPIOx, dout[index].GPIO_Pin);
        #else
            GPIO_ResetBits(dout[index].GPIOx, dout[index].GPIO_Pin);
        #endif
    }
    else {
        #if DO_CLOSE_VALUE
            GPIO_ResetBits(dout[index].GPIOx, dout[index].GPIO_Pin);
        #else
            GPIO_SetBits(dout[index].GPIOx, dout[index].GPIO_Pin);
        #endif
    }
}

/**
 * @brief   sth
 * @param   None
 * @retval  None
 */
void do_set(int index, do_state_t state)
{
    if (index < 0) {
        for (int i = 0; i < DO_NUM; i++) {
            _do_set(i, state);
        }
    }
    else if (index < DO_NUM) {
        _do_set(index, state);
    }
}

void do_triggle(int index)
{
    if (index < 0) {
        for (int i = 0; i < DO_NUM; i++) {
            dout[i].GPIOx->ODR ^= dout[i].GPIO_Pin;
        }
    }
    else if (index < DO_NUM) {
        dout[index].GPIOx->ODR ^= dout[index].GPIO_Pin;
    }
}

do_state_t do_state(int index)
{
    if (index < DO_NUM) {
        return (do_state_t)(GPIO_ReadOutputDataBit(dout[index].GPIOx, dout[index].GPIO_Pin) != DO_CLOSE_VALUE);
    }

    return do_open;
}
