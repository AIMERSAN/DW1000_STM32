#ifndef __UART_H
#define __UART_H

#ifndef UART_C_//如果没有定义
	#define UART_Ex_ extern
#else
	#define USART_Ex_
#endif

#include <stm32f10x.h>
#include "Com_BufferManage.h"
#include "Com_LoopList.h"

/****************************串口1****************************/
//接收环形队列
UART_Ex_ rb_t rb_t_usart1_read;
#define rb_t_usart1_read_buff_len 1024
UART_Ex_ unsigned char rb_t_usart1_read_buff[rb_t_usart1_read_buff_len];
//从缓存拷贝数据使用
UART_Ex_ unsigned char usart1_read_buff_copy[rb_t_usart1_read_buff_len];
//接收计数
UART_Ex_ int usart1_read_count;

//发送环形队列
UART_Ex_ rb_t rb_t_usart1_send;
#define rb_t_usart1_send_buff_len 1024
UART_Ex_ unsigned char rb_t_usart1_send_buff[rb_t_usart1_send_buff_len];
UART_Ex_ unsigned char rb_t_usart1_send_byte;//串口提取环形队列1个字节

//空闲中断标志
UART_Ex_ unsigned char usart1_idle_flag;//标志

void Uart_Init(uint32_t bound);//串口初始化
void UsartOutStrIT(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt);
void UsartOutStr(USART_TypeDef* USARTx, unsigned char *c,uint32_t cnt);//串口发送字符串数据
void UsartOutChar(USART_TypeDef* USARTx, unsigned char c);//串口发送一个字节
void USART1_IRQHandler(void); // 串口中断函数
// void Usart2IdleLoop(int IdleCnt);
#endif


