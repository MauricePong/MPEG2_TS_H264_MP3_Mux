#include "Audio.h"

unsigned int decode_audio_done = 0;
unsigned int OneFrameLen_Mp3 = 0;              //一帧音频数据的的长度
unsigned int OneFrameLen_Mp3_Fixed  = 0;       //一帧音频数据的的长度
unsigned int OneFrame_Mp3_Num = 0;             //读取了文件的第几帧
unsigned long Bitrate_Mp3 = 0;                 //位率
unsigned long Sampling_Frequency_Mp3 = 48000;  //采样频率

int GetFrameHead(Mp3_Header * mp3_header ,unsigned char * buf)
{
	unsigned char mp3headerbuf[4];

	int error = 0;
	OneFrameLen_Mp3 = 0;
	Bitrate_Mp3 = 0.0;
	Sampling_Frequency_Mp3 = 0;

	memset(mp3headerbuf,0,4);
	if (feof(pAudio_Mp3_File))                                            //如果到文件末尾
	{
		return 0;
	}
	else
	{            
		error =  fread (mp3headerbuf, 1, 4, pAudio_Mp3_File);              //从文件读取四个字节到buf
		if (error < 0)             
		{
			printf("读取MP3头数据失败\n");
			return 0;
		}
		if (error = 0 )
		{
			//文件结束
		}
		else
		{
			//文件读取正常
		}
	}
	mp3_header->sync = (mp3headerbuf[0] << 3)| (mp3headerbuf[1] >> 5) & 0x07;
	mp3_header->version = (mp3headerbuf[1] >> 3 ) & 0x03;
	mp3_header->layer = ( mp3headerbuf[1] >> 1) & 0x03;
	mp3_header->error_protection = mp3headerbuf[1] & 0x01;
	mp3_header->bitrate_index = (mp3headerbuf[2] >> 4 ) & 0x0F;
	mp3_header->sampling_frequency = (mp3headerbuf[2] >> 2 ) & 0x03;
	mp3_header->padding = (mp3headerbuf[2] >> 1) & 0x01;
	mp3_header->private_t = mp3headerbuf[2] & 0x01;
	mp3_header->mode = (mp3headerbuf[3] >> 6) & 0x03;
	mp3_header->mode_extension = (mp3headerbuf[3] >> 4) & 0x03;
	mp3_header->copyright = (mp3headerbuf[3] >> 3) & 0x01;
	mp3_header->original = (mp3headerbuf[3] >> 2) & 0x01;
	mp3_header->emphasis = mp3headerbuf[3] & 0x03;


	if (mp3_header->version == 0x02)                 //MPEG 2 
	{
		if (mp3_header->sampling_frequency == 0x00)                                //22.05khz
		{
			Sampling_Frequency_Mp3 = 22.05;
		}
		else if (mp3_header->sampling_frequency == 0x01)                           //24khz
		{
			Sampling_Frequency_Mp3 = 24;
		}
		else if (mp3_header->sampling_frequency == 0x02)                           //16khz
		{
			Sampling_Frequency_Mp3 = 16;
		}
		else 
		{
			printf("mp3_header->Sampling_Frequency_Mp3 == 0x03 未定义\n");            
		}

		if (mp3_header->layer == 0x01)               //layer 3            
		{
			if (mp3_header->bitrate_index == 0x00)
			{
				printf("mp3_header->bitrate_index == 0x00 free\n");
			}
			else if (mp3_header->bitrate_index == 0x01)
			{
				Bitrate_Mp3 = 8;
			}
			else if (mp3_header->bitrate_index == 0x02)
			{
				Bitrate_Mp3 = 16;
			}
			else if (mp3_header->bitrate_index == 0x03)
			{
				Bitrate_Mp3 = 24;
			}
			else if (mp3_header->bitrate_index == 0x04)
			{
				Bitrate_Mp3 = 32;
			}
			else if (mp3_header->bitrate_index == 0x05)
			{
				Bitrate_Mp3 = 40;
			}
			else if (mp3_header->bitrate_index == 0x06)
			{
				Bitrate_Mp3 = 48;
			}
			else if (mp3_header->bitrate_index == 0x07)
			{
				Bitrate_Mp3 = 56;
			}
			else if (mp3_header->bitrate_index == 0x08)
			{
				Bitrate_Mp3 = 64;
			}
			else if (mp3_header->bitrate_index == 0x09)
			{
				Bitrate_Mp3 = 80;
			}
			else if (mp3_header->bitrate_index == 0x0A)
			{
				Bitrate_Mp3 = 96;
			}
			else if (mp3_header->bitrate_index == 0x0B)
			{
				Bitrate_Mp3 = 112;
			}
			else if (mp3_header->bitrate_index == 0x0C)
			{
				Bitrate_Mp3 = 128;
			}
			else if (mp3_header->bitrate_index == 0x0D)
			{
				Bitrate_Mp3 = 144;
			}
			else if (mp3_header->bitrate_index == 0x0E)
			{
				Bitrate_Mp3 = 160;
			}
			else  //0x0F
			{
				printf("mp3_header->bitrate_index == 0x0F 不允许的值\n");
			}

			OneFrameLen_Mp3 = (72 * Bitrate_Mp3)/ Sampling_Frequency_Mp3 + mp3_header->padding ;
		}
		if (mp3_header->layer == 0x02 )               //layer 2            
		{
			if (mp3_header->bitrate_index == 0x00)
			{
				printf("mp3_header->bitrate_index == 0x00 free\n");
			}
			else if (mp3_header->bitrate_index == 0x01)
			{
				Bitrate_Mp3 = 8;
			}
			else if (mp3_header->bitrate_index == 0x02)
			{
				Bitrate_Mp3 = 16;
			}
			else if (mp3_header->bitrate_index == 0x03)
			{
				Bitrate_Mp3 = 24;
			}
			else if (mp3_header->bitrate_index == 0x04)
			{
				Bitrate_Mp3 = 32;
			}
			else if (mp3_header->bitrate_index == 0x05)
			{
				Bitrate_Mp3 = 40;
			}
			else if (mp3_header->bitrate_index == 0x06)
			{
				Bitrate_Mp3 = 48;
			}
			else if (mp3_header->bitrate_index == 0x07)
			{
				Bitrate_Mp3 = 56;
			}
			else if (mp3_header->bitrate_index == 0x08)
			{
				Bitrate_Mp3 = 64;
			}
			else if (mp3_header->bitrate_index == 0x09)
			{
				Bitrate_Mp3 = 80;
			}
			else if (mp3_header->bitrate_index == 0x0A)
			{
				Bitrate_Mp3 = 96;
			}
			else if (mp3_header->bitrate_index == 0x0B)
			{
				Bitrate_Mp3 = 112;
			}
			else if (mp3_header->bitrate_index == 0x0C)
			{
				Bitrate_Mp3 = 128;
			}
			else if (mp3_header->bitrate_index == 0x0D)
			{
				Bitrate_Mp3 = 144;
			}
			else if (mp3_header->bitrate_index == 0x0E)
			{
				Bitrate_Mp3 = 160;
			}
			else  //0x0F
			{
				printf("mp3_header->bitrate_index == 0x0F 不允许的值\n");
			}
			OneFrameLen_Mp3 = (72 * Bitrate_Mp3)/ Sampling_Frequency_Mp3 + mp3_header->padding ;
		}
		else if (mp3_header->layer == 0x03)          //layer 1
		{ 
			if (mp3_header->bitrate_index == 0x00)
			{
				printf("mp3_header->bitrate_index == 0x00 free\n");
			}
			else if (mp3_header->bitrate_index == 0x01)
			{
				Bitrate_Mp3 = 32;
			}
			else if (mp3_header->bitrate_index == 0x02)
			{
				Bitrate_Mp3  = 48;
			}
			else if (mp3_header->bitrate_index == 0x03)
			{
				Bitrate_Mp3 = 56;
			}
			else if (mp3_header->bitrate_index == 0x04)
			{
				Bitrate_Mp3 = 64;
			}
			else if (mp3_header->bitrate_index == 0x05)
			{
				Bitrate_Mp3 = 80;
			}
			else if (mp3_header->bitrate_index == 0x06)
			{
				Bitrate_Mp3 = 96;
			}
			else if (mp3_header->bitrate_index == 0x07)
			{
				Bitrate_Mp3 = 112;
			}
			else if (mp3_header->bitrate_index == 0x08)
			{
				Bitrate_Mp3 = 128;
			}
			else if (mp3_header->bitrate_index == 0x09)
			{
				Bitrate_Mp3 = 144;
			}
			else if (mp3_header->bitrate_index == 0x0A)
			{
				Bitrate_Mp3 = 160;
			}
			else if (mp3_header->bitrate_index == 0x0B)
			{
				Bitrate_Mp3 = 176;
			}
			else if (mp3_header->bitrate_index == 0x0C)
			{
				Bitrate_Mp3 = 192;
			}
			else if (mp3_header->bitrate_index == 0x0D)
			{
				Bitrate_Mp3 = 224;
			}
			else if (mp3_header->bitrate_index == 0x0E)
			{
				Bitrate_Mp3 = 256;
			}
			else  //0x0F
			{
				printf("mp3_header->bitrate_index == 0x0F 不允许的值\n");
			}
			OneFrameLen_Mp3 = (24 * Bitrate_Mp3)/ Sampling_Frequency_Mp3 + mp3_header->padding ;
		}
		else                                         //00 未定义
		{
			printf("MPEG 2 ,00 暂不做处理\n");
		}
	}
	else if (mp3_header->version == 0x03)            //MPEG 1
	{
		if (mp3_header->sampling_frequency == 0x00)                                //44.1khz
		{
			Sampling_Frequency_Mp3 = 44.1;
		}
		else if (mp3_header->sampling_frequency == 0x01)                           //48khz
		{
			Sampling_Frequency_Mp3 = 48;
		}
		else if (mp3_header->sampling_frequency == 0x02)                           //32khz
		{
			Sampling_Frequency_Mp3 = 32;
		}
		else 
		{
			printf("mp3_header->Sampling_Frequency_Mp3 == 0x03 未定义\n");            
		}

		if (mp3_header->layer == 0x01)               //layer 3            
		{
			if (mp3_header->bitrate_index == 0x00)
			{
				printf("mp3_header->bitrate_index == 0x00 free\n");
			}
			else if (mp3_header->bitrate_index == 0x01)
			{
				Bitrate_Mp3 = 32;
			}
			else if (mp3_header->bitrate_index == 0x02)
			{
				Bitrate_Mp3 = 40;
			}
			else if (mp3_header->bitrate_index == 0x03)
			{
				Bitrate_Mp3 = 48;
			}
			else if (mp3_header->bitrate_index == 0x04)
			{
				Bitrate_Mp3 = 56;
			}
			else if (mp3_header->bitrate_index == 0x05)
			{
				Bitrate_Mp3 = 64;
			}
			else if (mp3_header->bitrate_index == 0x06)
			{
				Bitrate_Mp3 = 80;
			}
			else if (mp3_header->bitrate_index == 0x07)
			{
				Bitrate_Mp3 = 96;
			}
			else if (mp3_header->bitrate_index == 0x08)
			{
				Bitrate_Mp3 = 112;
			}
			else if (mp3_header->bitrate_index == 0x09)
			{
				Bitrate_Mp3 = 128;
			}
			else if (mp3_header->bitrate_index == 0x0A)
			{
				Bitrate_Mp3 = 160;
			}
			else if (mp3_header->bitrate_index == 0x0B)
			{
				Bitrate_Mp3 = 192;
			}
			else if (mp3_header->bitrate_index == 0x0C)
			{
				Bitrate_Mp3 = 224;
			}
			else if (mp3_header->bitrate_index == 0x0D)
			{
				Bitrate_Mp3 = 256;
			}
			else if (mp3_header->bitrate_index == 0x0E)
			{
				Bitrate_Mp3 = 320;
			}
			else  //0x0F
			{
				printf("mp3_header->bitrate_index == 0x0F 不允许的值\n");
			}
			OneFrameLen_Mp3 = (144 * Bitrate_Mp3)/ Sampling_Frequency_Mp3 + mp3_header->padding ;
		}

		if (mp3_header->layer == 0x02 )              //layer 2            
		{
			if (mp3_header->bitrate_index == 0x00)
			{
				printf("mp3_header->bitrate_index == 0x00 free\n");
			}
			else if (mp3_header->bitrate_index == 0x01)
			{
				Bitrate_Mp3 = 32;
			}
			else if (mp3_header->bitrate_index == 0x02)
			{
				Bitrate_Mp3 = 48;
			}
			else if (mp3_header->bitrate_index == 0x03)
			{
				Bitrate_Mp3 = 56;
			}
			else if (mp3_header->bitrate_index == 0x04)
			{
				Bitrate_Mp3 = 64;
			}
			else if (mp3_header->bitrate_index == 0x05)
			{
				Bitrate_Mp3 = 80;
			}
			else if (mp3_header->bitrate_index == 0x06)
			{
				Bitrate_Mp3 = 96;
			}
			else if (mp3_header->bitrate_index == 0x07)
			{
				Bitrate_Mp3 = 112;
			}
			else if (mp3_header->bitrate_index == 0x08)
			{
				Bitrate_Mp3 = 128;
			}
			else if (mp3_header->bitrate_index == 0x09)
			{
				Bitrate_Mp3 = 160;
			}
			else if (mp3_header->bitrate_index == 0x0A)
			{
				Bitrate_Mp3 = 192;
			}
			else if (mp3_header->bitrate_index == 0x0B)
			{
				Bitrate_Mp3 = 224;
			}
			else if (mp3_header->bitrate_index == 0x0C)
			{
				Bitrate_Mp3 = 256;
			}
			else if (mp3_header->bitrate_index == 0x0D)
			{
				Bitrate_Mp3 = 320;
			}
			else if (mp3_header->bitrate_index == 0x0E)
			{
				Bitrate_Mp3 = 384;
			}
			else  //0x0F
			{
				printf("mp3_header->bitrate_index == 0x0F 不允许的值\n");
			}
			OneFrameLen_Mp3 = (144 * Bitrate_Mp3)/ Sampling_Frequency_Mp3 + mp3_header->padding ;
		}
		else if (mp3_header->layer == 0x03)          //layer 1
		{ 
			if (mp3_header->bitrate_index == 0x00)
			{
				printf("mp3_header->bitrate_index == 0x00 free\n");
			}
			else if (mp3_header->bitrate_index == 0x01)
			{
				Bitrate_Mp3 = 32;
			}
			else if (mp3_header->bitrate_index == 0x02)
			{
				Bitrate_Mp3 = 64;
			}
			else if (mp3_header->bitrate_index == 0x03)
			{
				Bitrate_Mp3 = 96;
			}
			else if (mp3_header->bitrate_index == 0x04)
			{
				Bitrate_Mp3 = 128;
			}
			else if (mp3_header->bitrate_index == 0x05)
			{
				Bitrate_Mp3 = 160;
			}
			else if (mp3_header->bitrate_index == 0x06)
			{
				Bitrate_Mp3 = 192;
			}
			else if (mp3_header->bitrate_index == 0x07)
			{
				Bitrate_Mp3 = 224;
			}
			else if (mp3_header->bitrate_index == 0x08)
			{
				Bitrate_Mp3 = 256;
			}
			else if (mp3_header->bitrate_index == 0x09)
			{
				Bitrate_Mp3 = 288;
			}
			else if (mp3_header->bitrate_index == 0x0A)
			{
				Bitrate_Mp3 = 320;
			}
			else if (mp3_header->bitrate_index == 0x0B)
			{
				Bitrate_Mp3 = 352;
			}
			else if (mp3_header->bitrate_index == 0x0C)
			{
				Bitrate_Mp3 = 384;
			}
			else if (mp3_header->bitrate_index == 0x0D)
			{
				Bitrate_Mp3 = 416;
			}
			else if (mp3_header->bitrate_index == 0x0E)
			{
				Bitrate_Mp3 = 448;
			}
			else  //0x0F
			{
				printf("mp3_header->bitrate_index == 0x0F 不允许的值\n");
			}
			OneFrameLen_Mp3 = (48 * Bitrate_Mp3)/ Sampling_Frequency_Mp3 + mp3_header->padding ;
		}
		else                                         //00 未定义
		{
			printf("MPEG 1 ,00 暂不做处理\n");
		}
	}
	else if(mp3_header->version == 0x00)             //MPEG 2.5
	{
		if (mp3_header->layer == 0x01 || mp3_header->layer == 0x02 )               //layer 3  //layer 2            
		{
			printf("MPEG2.5 ,layer 3 /layer 2 暂不做处理");
		}
		else if (mp3_header->layer == 0x03)          //layer 1
		{ 
			printf("MPEG2.5 ,layer 1 暂不做处理");
		}
		else                                         //00 未定义
		{
			printf("MPEG 2.5 ,00 暂不做处理\n");
		}
	}
	else                                             //01 未定义 
	{
		printf("暂不处理\n");
	}
	memcpy(buf,mp3headerbuf,4);          //将头写入数据
	return 1;
}



int MP32PES(TsPes * tsmp3pes,unsigned long Adudiopts)
{
	unsigned int mp3pes_pos = 0;
	unsigned int OneFrameLen_MP3_t = 0;
	Mp3_Header mp3_header;

	//读取出一帧数据
	GetFrameHead(&mp3_header,tsmp3pes->Es);
	mp3pes_pos += OneFrameLen_Mp3 ;

	OneFrameLen_MP3_t  = ReadFile(pAudio_Mp3_File ,tsmp3pes->Es + 4, OneFrameLen_Mp3 - 4); //读取一帧数据到buf中
	if (OneFrameLen_MP3_t == 0)
	{
		decode_audio_done = 1;
		return 0;
	}

	tsmp3pes->packet_start_code_prefix = 0x000001;
	tsmp3pes->stream_id = TS_MP3_STREAM_ID;                                //E0~EF表示是视频的,C0~DF是音频,H264-- E0
	tsmp3pes->PES_packet_length = 0 ;                                      //一帧数据的长度 不包含 PES包头 ,8自适应段的长度
	tsmp3pes->Pes_Packet_Length_Beyond = OneFrameLen_Mp3;                  //= OneFrameLen_amp3;     //这里读错了一帧  
	if (OneFrameLen_MP3_t > 0xFFFF)                                        //如果一帧数据的大小超出界限
	{
		tsmp3pes->PES_packet_length = 0x00;
		tsmp3pes->Pes_Packet_Length_Beyond = OneFrameLen_Mp3;  
		mp3pes_pos += 16;
	}
	else
	{
		tsmp3pes->PES_packet_length = 0x00;
		tsmp3pes->Pes_Packet_Length_Beyond = OneFrameLen_Mp3;  
		mp3pes_pos += 14;
	}
	tsmp3pes->marker_bit = 0x02;
	tsmp3pes->PES_scrambling_control = 0x00;                               //人选字段 存在，不加扰
	tsmp3pes->PES_priority = 0x00;
	tsmp3pes->data_alignment_indicator = 0x00;
	tsmp3pes->copyright = 0x00;
	tsmp3pes->original_or_copy = 0x00;
	tsmp3pes->PTS_DTS_flags = 0x02;                                        //10'：PTS字段存在,DTS不存在
	tsmp3pes->ESCR_flag = 0x00;
	tsmp3pes->ES_rate_flag = 0x00;
	tsmp3pes->DSM_trick_mode_flag = 0x00;
	tsmp3pes->additional_copy_info_flag = 0x00;
	tsmp3pes->PES_CRC_flag = 0x00;
	tsmp3pes->PES_extension_flag = 0x00;
	tsmp3pes->PES_header_data_length = 0x05;                               //后面的数据 包括了PTS所占的字节数

	//清 0 
	tsmp3pes->tsptsdts.pts_32_30  = 0;
	tsmp3pes->tsptsdts.pts_29_15 = 0;
	tsmp3pes->tsptsdts.pts_14_0 = 0;

	tsmp3pes->tsptsdts.reserved_1 = 0x03;                                 //填写 pts信息
	// Adudiopts大于30bit，使用最高三位 
	if(Adudiopts > 0x7FFFFFFF)
	{
		tsmp3pes->tsptsdts.pts_32_30 = (Adudiopts >> 30) & 0x07;                 
		tsmp3pes->tsptsdts.marker_bit1 = 0x01;
	}
	else 
	{
		tsmp3pes->tsptsdts.marker_bit1 = 0;
	}
	// Videopts大于15bit，使用更多的位来存储
	if(Adudiopts > 0x7FFF)
	{
		tsmp3pes->tsptsdts.pts_29_15 = (Adudiopts >> 15) & 0x007FFF ;
		tsmp3pes->tsptsdts.marker_bit2 = 0x01;
	}
	else
	{
		tsmp3pes->tsptsdts.marker_bit2 = 0;
	}
	//使用最后15位
	tsmp3pes->tsptsdts.pts_14_0 = Adudiopts & 0x007FFF;
	tsmp3pes->tsptsdts.marker_bit3 = 0x01;

	return mp3pes_pos;
}
