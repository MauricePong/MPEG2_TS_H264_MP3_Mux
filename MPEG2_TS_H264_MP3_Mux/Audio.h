#pragma once

#include "Ts.h"

extern unsigned int OneFrameLen_Mp3 ;             //一帧音频数据的的长度
extern unsigned int OneFrameLen_Mp3_Fixed ;       //一帧音频数据的的长度
extern unsigned int OneFrame_Mp3_Num ;            //读取了文件的第几帧
extern unsigned long Bitrate_Mp3;                 //位率
extern unsigned long Sampling_Frequency_Mp3;      //采样频率


extern unsigned int decode_audio_done;

//MP3头结构体
typedef struct Tag_Mp3_Header
{ 
	unsigned int  sync :11;                  //同步信息
	unsigned char version :2;                //版本 
	unsigned char layer :2;                  //层
	unsigned char error_protection:1;        //CRC校验
	unsigned char bitrate_index :4;          //位率
	unsigned char sampling_frequency :2;     //采样频率
	unsigned char padding :1;                //帧长调节
	unsigned char private_t :1;              //保留字
	unsigned char mode :2;                   //声道模式
	unsigned char mode_extension :2;         //扩展模式
	unsigned char copyright :1;              //版权
	unsigned char original :1;               //原版标志
	unsigned char emphasis :2;               //强调模式
}Mp3_Header; 

int GetFrameHead(Mp3_Header * mp3_header,unsigned char * buf);
int MP32PES(TsPes * tsmp3pes,unsigned long Adudiopts);                                       //填写pes结构