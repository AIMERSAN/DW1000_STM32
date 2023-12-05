#ifndef _COM_BUFFMANAGE_H_
#define _COM_BUFFMANAGE_H_

#ifndef BUFFMANAGE_C_//如果没有定义
#define BUFFMANAGE_Cx_ extern
#else
#define BUFFMANAGE_Cx_
#endif

#include <stm32f10x.h>
#include "com_LoopList.h"


typedef struct{
	signed int  Count;
	signed int  Cnt;
	unsigned char ReadFlage;
	unsigned char SendFlage;
	
	signed int  ReadLen;
	signed int  SendLen;	//用户可自由使用以上变量
		
	int32_t value;    //内部使用,用户不可使用
	signed int  Len;	//内部使用,用户不可使用
	rb_t Buff;        //管理:缓存数据数组
	rb_t ManageBuff;  //管理:每次缓存数据的数组
}buff_manage_struct;



void BufferManageCreate(buff_manage_struct *bms,void *buff,uint32_t BuffLen,void *ManageBuff,uint32_t ManageBuffLen);
void BufferManageWrite(buff_manage_struct *bms,void *buff,uint32_t BuffLen,int *DataLen);
void BufferManageRead(buff_manage_struct *bms,void *buff,int *DataLen);

#endif

