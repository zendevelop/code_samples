#pragma once
extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
}

class ADPCMCodec
{
public:
	ADPCMCodec();
	~ADPCMCodec();

	int decoderInit();
	int decode(unsigned short* dstBuf, unsigned int dstBufSize, unsigned char* srcBuf, unsigned int srcSize);
	int decoderFree();

	int encoderInit();
	int getEncBuf(unsigned char** encBuf, unsigned int* size);
	int encode(unsigned char* dstBuf, unsigned int dstBufSize, unsigned char* srcBuf, unsigned int srcSize);
	int encoderFree();


private:
	AVCodecID codecID = AV_CODEC_ID_ADPCM_IMA_ISS;
	AVCodec* pDecCodec;
	AVCodecContext* pDecCodecCtx;
	AVFrame* pDecFrame;

	AVCodec* pEncCodec;
	AVCodecContext* pEncCodecCtx;
	AVFrame* pEncFrame;
	unsigned char* frame_buf;
	unsigned int encBufSize;
};

