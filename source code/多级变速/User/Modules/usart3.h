#ifndef __USART3_H
#define	__USART3_H

#include "stm32f10x.h"
#include <stdio.h>

void USART3_Config(void);
void USART3_sned_char(u8 temp);
void USART3_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif /* __USART2_H */
