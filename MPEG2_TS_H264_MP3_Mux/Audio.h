#pragma once

#include "Ts.h"

extern unsigned int OneFrameLen_Mp3 ;             //һ֡��Ƶ���ݵĵĳ���
extern unsigned int OneFrameLen_Mp3_Fixed ;       //һ֡��Ƶ���ݵĵĳ���
extern unsigned int OneFrame_Mp3_Num ;            //��ȡ���ļ��ĵڼ�֡
extern unsigned long Bitrate_Mp3;                 //λ��
extern unsigned long Sampling_Frequency_Mp3;      //����Ƶ��


extern unsigned int decode_audio_done;

//MP3ͷ�ṹ��
typedef struct Tag_Mp3_Header
{ 
	unsigned int  sync :11;                  //ͬ����Ϣ
	unsigned char version :2;                //�汾 
	unsigned char layer :2;                  //��
	unsigned char error_protection:1;        //CRCУ��
	unsigned char bitrate_index :4;          //λ��
	unsigned char sampling_frequency :2;     //����Ƶ��
	unsigned char padding :1;                //֡������
	unsigned char private_t :1;              //������
	unsigned char mode :2;                   //����ģʽ
	unsigned char mode_extension :2;         //��չģʽ
	unsigned char copyright :1;              //��Ȩ
	unsigned char original :1;               //ԭ���־
	unsigned char emphasis :2;               //ǿ��ģʽ
}Mp3_Header; 

int GetFrameHead(Mp3_Header * mp3_header,unsigned char * buf);
int MP32PES(TsPes * tsmp3pes,unsigned long Adudiopts);                                       //��дpes�ṹ