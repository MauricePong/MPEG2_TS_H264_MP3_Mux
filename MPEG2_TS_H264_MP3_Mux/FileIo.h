#pragma once

#include "Information.h"

#define INPUTH264FILENAME     "..\\H264_STREAM\\22.264"
#define INPUTMP3FILENAME      "..\\MP3_STREAM\\22.mp3"
#define OUTPUTTSFILENAME      "..\\TS_STREAM\\22TS.ts"


extern FILE * pVideo_H264_File;
extern FILE * pAudio_Mp3_File;
extern FILE * pVideo_Audio_Ts_File;

FILE * OpenFile(char * FileName,char * OpenMode);                        //���ļ�
void   CloseFile(FILE * pFile);                                          //�ر��ļ�
int    ReadFile(FILE * pFile ,unsigned char * Buffer,int BufferSize);    //��ȡ����
int    WriteFile(FILE * pFile ,char * Buffer,int BufferSize);            //�ļ�д����
