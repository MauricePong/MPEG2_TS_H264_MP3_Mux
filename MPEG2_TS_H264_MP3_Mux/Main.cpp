#include "Mux.h"

#define FRAMETATE 29
#define AUDIOSAMPLERAME 48000 

int main()
{
	printf("--------�������п�ʼ----------\n");
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
	printf("--------�������н���----------\n");
	printf("-------�밴������˳�---------\n");
	return getchar();
}