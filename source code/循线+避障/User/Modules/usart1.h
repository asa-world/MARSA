#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Config(void);

void USART1_sned_char(u8 temp);  

void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);


#endif /* __USART1_H */
