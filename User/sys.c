#include "sys.h"


/**
 * @brief	THUMB指令不支持汇编内联、
 *			采用如下方法实现执行汇编指令WFI 
 *
 * @param   void
 *
 * @return  __asm
 */
__asm void WFI_SET(void)
{
	WFI;		  
}
/**
 * @brief	关闭所有中断(但是不包括fault和NMI中断)
 *
 * @param   void
 *
 * @return  __asm
 */
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
/**
 * @brief	开启所有中断
 *
 * @param   void
 *
 * @return  __asm
 */
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
/**
 * @brief	设置栈顶地址
 *
 * @param   addr	栈顶地址
 *
 * @return  __asm
 */
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

