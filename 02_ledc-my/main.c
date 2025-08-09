#include "main.h"

/*
使能I.MX6U的所有外设时钟
*/
void clk_enable(void)
{
    CCM_CCGR0 = 0xFFFFFFFF;
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;
}

/*
初始化LED对应的GPIO
*/
void led_init(void)
{
    SW_MUX_GPIO1_IO03 = 0x5; /* 复用为GPIO1_IO03 */
    SW_PAD_GPIO1_IO03 = 0x10B0; /* 设置GPIO1_IO03的属性 */
    GPIO1_GDIR = 0x0000008; /* 设置GPIO1_IO03为输出 */
    GPIO1_DR = 0x0; /* 设置GPIO1_IO03为低电平 */
}

/*
打开LED灯
*/
void led_on(void)
{
    GPIO1_DR &= ~(1 << 3); /* 将GPIO1_DR的bit3清零，GPIO_DR & 0111 */
}

/*
关闭LED灯
*/
void led_off(void)
{
    GPIO1_DR |= (1 << 3); /* 将GPIO1_DR的bit3置1，GPIO_DR | 1000 */
}

/*
延时函数
*/
void delay_short(volatile unsigned int count)
{
    while (count--);
}

/*
延时函数
*/
void delay(volatile unsigned int count)
{
    while (count--)
    {
        delay_short(0x7ff);
    }
}

/*
主函数
*/
int main(void)
{
    clk_enable(); /* 使能I.MX6U的所有外设时钟 */
    led_init(); /* 初始化LED对应的GPIO */
    int cnt = 0;
    int delay_time = 0;
    while (1)
    {
        if (cnt <= 20) {
            delay_time += 100;
        } else {
            delay_time -= 100;
        }
        if (delay_time <= 0) {
            delay_time = 0;
            cnt = 0;
        }
        cnt++;
        led_off(); /* 打开LED灯 */
        delay(delay_time); /* 延时 */
        led_on(); /* 关闭LED灯 */
        delay(delay_time); /* 延时 */
    }
    return 0;
}