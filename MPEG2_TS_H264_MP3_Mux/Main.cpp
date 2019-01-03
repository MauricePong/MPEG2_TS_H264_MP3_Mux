#include "Mux.h"

#define FRAMETATE 29
#define AUDIOSAMPLERAME 48000 

int main()
{
	printf("--------程序运行开始----------\n");
	pVideo_H264_File = OpenFile(INPUTH264FILENAME,"rb");
	pAudio_Mp3_File = OpenFile(INPUTMP3FILENAME,"rb");
	pVideo_Audio_Ts_File = OpenFile(OUTPUTTSFILENAME,"wb");

	//////////////////////////////////////////////////////////////////////////
	WriteBuf2File(FRAMETATE,AUDIOSAMPLERAME);
	//////////////////////////////////////////////////////////////////////////

	if (pVideo_H264_File)
	{
		CloseFile(pVideo_H264_File);
		pVideo_H264_File = NULL;
	}
	if (pAudio_Mp3_File)
	{
		CloseFile(pAudio_Mp3_File);
		pAudio_Mp3_File = NULL;
	}
	if (pVideo_Audio_Ts_File)
	{
		CloseFile(pVideo_Audio_Ts_File);
		pVideo_Audio_Ts_File = NULL;
	}
	printf("--------程序运行结束----------\n");
	printf("-------请按任意键退出---------\n");
	return getchar();
}