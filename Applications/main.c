/**
 * @brief: 主逻辑
 */
#include "stm32f10x.h"
#include "do.h"
#include "key.h"

#define RELAY_CLOSE_SECOND      120 /* 继电器闭合时间，单位：秒，最大49天 */

volatile uint32_t systick_count = 0;
uint32_t relay_tick = 0;
uint32_t do_value = 0;

void key_scan(void);

int main(void)
{
    key_init();
    do_init();
    SysTick_Config(SystemCoreClock / 1000);
    do_set(ALL, do_open);
    
    while (1) {
        key_scan();

        for (int i = 0; i < KEY_NUM; i++) {
            if (key_clicked(i)) { /* 按钮按下 */
                do_set(ALL, do_open); /* 所有的继电器都断开 */
                do_set(DO_LAST, do_close);  /* 灭最后一个灯 */
                do_set(i, do_close);  /* 再打开对应的灯 */
                relay_tick = systick_count; /* 更新计时 */
            }
        }

        if((systick_count - relay_tick) > RELAY_CLOSE_SECOND * 1000) { /* 到时 */
            relay_tick = systick_count;
            do_set(ALL, do_open); /* 所有继电器断开 */
        }
    }

    return 0;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    ++systick_count;
}

void key_scan(void)
{
    static uint32_t key_tick = 0;
    if (systick_count - key_tick > 50) { // 50ms检测一次按键
        key_tick = systick_count;
        key_read();
    }
}
