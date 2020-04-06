#include "stm32f10x.h"
#include "key.h"

#define KEY_DEFAULT     { \
    .pre_state = 0, \
    .state = key_no_press, \
    .pin_cfg.RCC_APB2Periph = RCC_APB2Periph_GPIOB, \
    .pin_cfg.GPIOx = GPIOB, \
    .pin_cfg.GPIO_Pin = GPIO_Pin_1, \
}

key_t key[KEY_NUM] = {0};

/**
 * @brief   key pin init and operations
 * @{
 */
void key_init(void)
{
    GPIO_InitTypeDef init;
    key_pin_t key_pin_cfg[KEY_NUM] = KEY_PIN_CONFIG;
    key_t key_default = KEY_DEFAULT;

    init.GPIO_Mode = GPIO_Mode_IPU;
    init.GPIO_Speed = GPIO_Speed_10MHz;
    for (int i = 0; i < KEY_NUM; i++) {
        RCC_APB2PeriphClockCmd(key_pin_cfg[i].RCC_APB2Periph, ENABLE);
        init.GPIO_Pin = key_pin_cfg[i].GPIO_Pin;
        GPIO_Init(key_pin_cfg[i].GPIOx, &init);
        key[i] = key_default;
        key[i].pin_cfg.RCC_APB2Periph = key_pin_cfg[i].RCC_APB2Periph;
        key[i].pin_cfg.GPIO_Pin = key_pin_cfg[i].GPIO_Pin;
        key[i].pin_cfg.GPIOx = key_pin_cfg[i].GPIOx;
    }
}

/**
 * @brief   按键检测
 * @param   None
 * @retval  key_no_press: 无动作
 *          ！key_no_press: 动作
 */
static key_state_t _key_read(uint32_t index)
{
    if (index >= KEY_NUM) {
        return key_no_press;
    }
    int i = index;
    if (GPIO_ReadInputDataBit(key[i].pin_cfg.GPIOx, key[i].pin_cfg.GPIO_Pin) == Bit_RESET) {
        if (key[i].pre_state == key_pressing) {
            key[i].state = key_pressing;
        }
        else {
            key[i].pre_state = key_pressing;
            /**
             * 长按检测
             * if (key[i].state == key_pressing)
             */
        }
    }
    else {
        if (key[i].pre_state == key_pressing){
            key[i].pre_state = key_no_press;
            key[i].state = key_pressed;
        }
        else {
            key[i].pre_state = key_no_press;
            key[i].state = key_no_press;
        }
    }

    return (key_state_t)(key[i].state != key_no_press);
}

void key_read(void)
{
    for (int i = 0; i < KEY_NUM; i++) {
        _key_read(i);
    }
}

int key_clicked(uint32_t index)
{
    int clicked = 0;
    if (index < KEY_NUM) {
        if (key[index].state == key_pressed) {
            key[index].state = key_no_press;
            clicked = 1;
        }
    }

    return clicked;
}

