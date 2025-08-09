.global _start

_start:
    /* 设置SVC模式 */
    mrs r0, cpsr
    bic r0, r0, #0x1F /* 将SPSR的低5位清零  */
    orr r0, r0, #0x13 /* 设置SPSR的低5位为SVC模式 */
    msr spsr, r0 /* 将SPSR的值写入到CPSR中 */
    
    /* 设置栈 */
    ldr sp, =0x80200000

    bl main /* 跳转到main函数 */
