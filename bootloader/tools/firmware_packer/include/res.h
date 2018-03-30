//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//    I BBMMBB      BBMMBBI     BBI EEMMFFI BBMMI     BBI EEMMFFI BBMMI       BBMMBBI   EEMMI EEMMLL        //
//    EEI   EEFF  EEI   LLBB  EEMMBBI I BBEE  I EE  EEMMBBI I BBEE  I EE    EEI   LLBB    EEBBI I BB        //
//  I FF        I EE      BBI   EEI     EEI   I EE    EEI     EEI   I EE  I EE      BBI   EEI   I EE        //
//  LLFF        LLEE      EELL  EEI     EEI   I EE    EEI     EEI   I EE  LLEE      EELL  EEI   I EE        //
//  I EE      I I BB      EEI   EEI     EEI   I EE    EEI     EEI   I EE  I BB      EEI   EEI   I EE        //
//    BBLL  I I   BBFF  I EE    EEI     EEI   I BB    EEI     EEI   I BB    BBFF  I EE    BBI   I EE        //
//    I BBMMEE    I BBMMBB    EEMMMMLLBBMMBBLLMMMMEEEEMMMMLLBBMMBBLLMMMMEE  I BBMMBB    EEMMMMLLBBMMBB      //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//                                                Scott System                                              //
//                                                                                                          //
//                               (c) Copyright 2007-2008, Scottyu China                                     //
//                                                                                                          //
//                                           All Rights Reserved                                            //
//                                                                                                          //
// File    : res.h                                                                                          //
// By      : scottyu                                                                                        //
// Version : V1.00                                                                                          //
// Time    : 2008-07-14 14:51:58                                                                            //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
// HISTORY                                                                                                  //
//                                                                                                          //
// 1 2008-07-14 14:52:02                                                                                    //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//


#ifndef __LION_RES__H__
#define __LION_RES__H__     1

#include "pack.h"

//------------------------------------------------------------------------------------------------------------
//资源数据节名
//------------------------------------------------------------------------------------------------------------
#define RES_SEC_NAME_SIZE	8			//
#define RES_SEC_NAME		".resthem"	//8字节长度
#define RES_VERSION			0x0100		//资源数据节格式版本
#define RES_ALIGN			32


//------------------------------------------------------------------------------------------------------------
//资源文件类型
//------------------------------------------------------------------------------------------------------------
#define SYSRES 				0
#define LIBRES  			1
#define APPRES				2			



//------------------------------------------------------------------------------------------------------------
//资源数据头定义
//------------------------------------------------------------------------------------------------------------
#ifdef WIN32_DATA_PACK
#pragma pack(push, 1)
#endif
typedef __PACKED struct tag_RESHEAD{
	s8		SecName[8];		    //节名
	u16		version;		    //版本0x0100
	u16		size;			    //头数据结构大小	
	u32		StyleOffset;	    //风格数据结构偏移量
	u32		StyleNum;		    //风格个数
    u32		ResNum;		        //资源个数
	u32		align;			    //数据边界对齐模式
	u32		flags;			    //标志，SYSRES LIBRES  APPRES
}RESHEAD;
#ifdef WIN32_DATA_PACK
#pragma pack(pop)
#endif

//------------------------------------------------------------------------------------------------------------
//本结构的大小
#define RESHEAH_SIZE	sizeof(RESHEAD)	//32 byte




//------------------------------------------------------------------------------------------------------------
//主题描述表定义
//------------------------------------------------------------------------------------------------------------
#define STYLE_NAME_SIZE 18

#ifdef WIN32_DATA_PACK
#pragma pack(push, 1)
#endif
typedef __PACKED struct tag_STYLE{
	u16		ID;					//风格ID， 唯一
	s8		Name[STYLE_NAME_SIZE];//风格名称，ASCII码	
	u32		ResTableOffset;	    //资源表起始地址偏移量
	u32		ResOffset;		    //资源数据起始地址偏移量
	u32		ResSize;			//资源数据长度
}STYLE;
#ifdef WIN32_DATA_PACK
#pragma pack(pop)
#endif

//------------------------------------------------------------------------------------------------------------
//本结构的大小
#define STYLE_SIZE	sizeof(STYLE)	//32 byte



//------------------------------------------------------------------------------------------------------------
//资源描述表定义
//------------------------------------------------------------------------------------------------------------
#define RES_NAME_SIZE    20

#ifdef WIN32_DATA_PACK
#pragma pack(push, 1)
#endif
typedef __PACKED struct tag_RESITEM{	
    u16		type;			    //资源类型
	u16		ID;				    //资源ID,不同风格的相同资源ID相同
	s8		Name[RES_NAME_SIZE];//资源名称，名称可以重复
	u32		offset;		        //资源起始地址在res节的偏移
	u32		size;			    //资源的size
}RESITEM;
#ifdef WIN32_DATA_PACK
#pragma pack(pop)
#endif

//------------------------------------------------------------------------------------------------------------
//本结构的大小
#define RESITEM_SIZE	sizeof(RESITEM) //32


//------------------------------------------------------------------------------------------------------------
// THE END !
//------------------------------------------------------------------------------------------------------------

#endif //__LION_RES__H__

