#ifndef __MAIN_H
#define __MAIN_H
/*
CCM相关寄存器
*/
#define CCM_CCGR0         *((volatile unsigned int *)0x020C4068) // 使能CCM_CCGR0
#define CCM_CCGR1         *((volatile unsigned int *)0x020C406C) // 使能CCM_CCGR1
#define CCM_CCGR2         *((volatile unsigned int *)0x020C4070) // 使能CCM_CCGR2
#define CCM_CCGR3         *((volatile unsigned int *)0x020C4074) // 使能CCM_CCGR3
#define CCM_CCGR4         *((volatile unsigned int *)0x020C4078) // 使能CCM_CCGR4
#define CCM_CCGR5         *((volatile unsigned int *)0x020C407C) // 使能CCM_CCGR5
#define CCM_CCGR6         *((volatile unsigned int *)0x020C4080) // 使能CCM_CCGR6

/*
IOMUXC相关寄存器
*/
#define SW_MUX_GPIO1_IO03 *((volatile unsigned int *)0x020E0068) // 复用为GPIO1_IO03
#define SW_PAD_GPIO1_IO03 *((volatile unsigned int *)0x020E02F4) // 设置GPIO1_IO03的属性, 表示属性设置为0x10B0

/*
GPIO1相关寄存器地址
*/
#define GPIO1_DR         *((volatile unsigned int *)0x0209C000) // 数据寄存器
#define GPIO1_GDIR       *((volatile unsigned int *)0x0209C004) // 方向寄存器
#define GPIO1_PSR        *((volatile unsigned int *)0x0209C008) // 状态寄存器
#define GPIO1_ICR1       *((volatile unsigned int *)0x0209C00C) // 中断清除寄存器1
#define GPIO1_ICR2       *((volatile unsigned int *)0x0209C010) // 中断清除寄存器2
#define GPIO1_IMR        *((volatile unsigned int *)0x0209C014) // 中断屏蔽寄存器
#define GPIO1_ISR        *((volatile unsigned int *)0x0209C018) // 中断状态寄存器
#define GPIO1_EDGE_SEL   *((volatile unsigned int *)0x0209C01C) // 边缘选择寄存器

#endif