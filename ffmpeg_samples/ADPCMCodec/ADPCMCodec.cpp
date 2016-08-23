#include "ADPCMCodec.h"



ADPCMCodec::ADPCMCodec()
{
	avcodec_register_all();
}


ADPCMCodec::~ADPCMCodec()
{
}

int ADPCMCodec::decoderInit() {
	
	pDecCodec = avcodec_find_decoder(codecID);
	if (!pDecCodec) {
		return -1;
	}
	pDecCodecCtx = avcodec_alloc_context3(pDecCodec);
	if (!pDecCodecCtx ) {
		return -1;
	}

	pDecCodecCtx->codec_id = codecID;
	pDecCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	pDecCodecCtx->sample_rate = 16000;
	pDecCodecCtx->channel_layout = AV_CH_LAYOUT_MONO;
	pDecCodecCtx->channels = av_get_channel_layout_nb_channels(pDecCodecCtx->channel_layout);

	if (avcodec_open2(pDecCodecCtx, pDecCodec, NULL) < 0) {
		return -1;
	}

	pDecFrame = av_frame_alloc();

	return 0;
}

int ADPCMCodec::decoderFree() {
	av_frame_free(&pDecFrame);
	avcodec_close(pDecCodecCtx);
	av_free(pDecCodecCtx);

	return 0;
}

int ADPCMCodec::decode(unsigned short* dstBuf, unsigned int dstBufSize, unsigned char* srcBuf, unsigned int srcSize) {
	AVPacket avPkt;
	av_init_packet(&avPkt);
	avPkt.data = srcBuf;
	avPkt.size = srcSize;

	int gotOutput;
	int outSize = 0;

	while (avPkt.size > 0) {
		int len = avcodec_decode_audio4(pDecCodecCtx, pDecFrame, &gotOutput, &avPkt);
		if (len < 0)
			return -1;

		if (gotOutput) {
			int dataSize = pDecFrame->nb_samples * pDecFrame->channels;
			unsigned short* ptr = (unsigned short*)pDecFrame->extended_data[0];
			if (dstBufSize < dataSize * sizeof(unsigned short))
				return -1;

			memcpy(dstBuf, ptr, dataSize * sizeof(unsigned short));

			avPkt.size -= len;
			avPkt.data += len;
			outSize += dataSize * sizeof(unsigned short);
		}
	}

	return outSize;
}

int ADPCMCodec::encoderInit() {
	AVCodecID codecID = AV_CODEC_ID_ADPCM_IMA_WAV;
	pEncCodec = avcodec_find_encoder(codecID);
	if (!pEncCodec)
		return -1;

	pEncCodecCtx = avcodec_alloc_context3(pEncCodec);
	if (!pEncCodecCtx)
		return -1;

	pEncCodecCtx->codec_id = codecID;
	pEncCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	pEncCodecCtx->sample_fmt = AV_SAMPLE_FMT_S16;
	pEncCodecCtx->sample_rate = 16000;
	pEncCodecCtx->channel_layout = AV_CH_LAYOUT_MONO;
	pEncCodecCtx->channels = av_get_channel_layout_nb_channels(pEncCodecCtx->channel_layout);
//	pEncCodecCtx->bit_rate = 64000;

	if (avcodec_open2(pEncCodecCtx, pEncCodec, NULL) < 0)
		return -1;

	int size = 0;

	pEncFrame = av_frame_alloc();
	pEncFrame->nb_samples = pEncCodecCtx->frame_size;
	pEncFrame->format = pEncCodecCtx->sample_fmt;
	encBufSize = av_samples_get_buffer_size(NULL, pEncCodecCtx->channels, pEncCodecCtx->frame_size, pEncCodecCtx->sample_fmt, 1);
	frame_buf = (unsigned char*)av_malloc(encBufSize);
	//avcodec_fill_audio_frame(pEncFrame, pEncCodecCtx->channels, pEncCodecCtx->sample_fmt, (const unsigned char*)frame_buf, encBufSize, 1);

	return 0;
}

int ADPCMCodec::encoderFree() {
	av_free(frame_buf);
	av_frame_free(&pEncFrame);
	avcodec_close(pEncCodecCtx);
	av_free(pEncCodecCtx);

	return 0;
}

int ADPCMCodec::getEncBuf(unsigned char** encBuf, unsigned int* size) {
	*encBuf = frame_buf;
	*size = encBufSize;
	return 0;
}

int ADPCMCodec::encode( unsigned char* dstBuf, unsigned int dstBufSize, unsigned char* srcBuf, unsigned int srcSize ) {
	int encSize = 0;
	int gotOutput = 0;
	AVPacket avPkt;
	av_init_packet(&avPkt);
	avPkt.data = NULL;
	avPkt.size = 0;

	avcodec_fill_audio_frame(pEncFrame, pEncCodecCtx->channels, pEncCodecCtx->sample_fmt, (const unsigned char*)srcBuf, srcSize, 1);
	int ret = avcodec_encode_audio2(pEncCodecCtx, &avPkt, pEncFrame, &gotOutput);
	if (ret < 0)
		return -1;

	if (gotOutput) {
		if (dstBufSize < avPkt.size)
			return -1;

		memcpy(dstBuf, avPkt.data, avPkt.size);
		encSize = avPkt.size;
		av_free_packet(&avPkt);
	}

	return encSize;
}