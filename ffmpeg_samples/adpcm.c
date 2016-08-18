#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>

#include <math.h>

#include <libavformat/avformat.h>
#include <stdio.h>

#define false 0

#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

int main( int argc, char* argv[] ) {
	AVCodec* codec;
	AVCodecContext* c = NULL;
	int len;
	FILE* f;
	FILE* outfile;
//    int buffer_size = AVCODEC_MAX_AUDIO_FRAME_SIZE + FF_INPUT_BUFFER_PADDING_SIZE;
	unsigned char inbuf[ AUDIO_INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE ];
//	unsigned char inbuf[ buffer_size ];
	AVPacket avpkt;
	AVFrame* decoded_frame = NULL;
	char* filename = argv[1];
	char* outname = argv[2];

    av_register_all();


	printf( "Decode audio file %s to %s\n", filename, outname );

    AVFormatContext* container = avformat_alloc_context();
    if( avformat_open_input( &container, filename, NULL, NULL ) < 0 ) {
        printf( "Could not open file\n" );
        exit( 1 );
    }

    if( avformat_find_stream_info( container, NULL ) < 0 ) {
        printf( "Could not find file info\n" );
        exit( 1 );
    }

    av_dump_format( container, 0, filename, false );


    int stream_id = -1;
    int i;
    for( i = 0; i < container->nb_streams; i++ ) {
        if( container->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO ) {
            stream_id = i;
            break;
        }
    }
    if( stream_id == -1 ) {
        printf( "Could not find audio stream\n" );
        exit( 1 );
    }

    AVDictionary* metadata = container->metadata;
    AVCodecContext* ctx = container->streams[ stream_id]->codec;
    AVCodec* codec_a = avcodec_find_decoder( ctx->codec_id );
    if( codec_a == NULL ) {
        printf( "cannot find codec!\n" );
        exit( 1 );
    }

    printf( "find audio codec OK\n" );
//    exit( 0 );

#if 0
	codec = avcodec_find_decoder( AV_CODEC_ID_ADPCM_IMA_WAV );
	if( !codec ) {
		fprintf( stderr, "Codec not found\n" );
		exit( 1 );
	}

	c = avcodec_alloc_context3( codec_a );
	if( !c ) {
		fprintf( stderr, "Could not allocate audio codec context\n" );
		exit( 1 );
	}
#endif

	/* open it */
	if( avcodec_open2( ctx, codec_a, NULL ) < 0 ) {
		fprintf( stderr, "Could not open codec\n" );
		exit( 1 );
	}

	f = fopen( filename, "rb" );
	if( !f ) {
		fprintf( stderr, "Could not open %s\n", filename );
		exit( 1 );
	}

	outfile = fopen( outname, "wb" );
	if( !outfile ) {
		av_free( c );
		exit( 1 );
	}

	av_init_packet( &avpkt );
    AVFrame* frame = av_frame_alloc();

	/* decode until eof */
	avpkt.data = inbuf;
	avpkt.size = fread( inbuf, 1, AUDIO_INBUF_SIZE, f );

    int frameFinished = 0;
    while( av_read_frame( container, &avpkt ) >= 0 ) {
        if( avpkt.stream_index == stream_id ) {
            AVPacket decodingPacket = avpkt;
            while( decodingPacket.size > 0 ) {
                int len = avcodec_decode_audio4( ctx, frame, &frameFinished, &decodingPacket );
                if( len < 0 ) {
                    av_frame_free( &frame );
                    printf( "avcodec_decode_audio4 err\n" );
                    exit( 1 );
                }

                if( frameFinished ) {
                    int data_size = frame->nb_samples * frame->channels;
                    printf( "data_size: %d, len: %d\n", data_size, len );
                    if( ctx->sample_fmt == AV_SAMPLE_FMT_S16P ) {
                        short* ptr_l = (short*)frame->extended_data[0];
                        short* ptr_r = (short*)frame->extended_data[1];
                        int i = 0;
                        printf( "linesize[0]: %d\n", frame->linesize[0] );
                        for( ; i < data_size; i++ ) {
                            fwrite( ptr_l++, sizeof(short), 1, outfile );
                        }
                    }

                    decodingPacket.size -= len;
                    decodingPacket.data += len;
                }
            }
            printf( "decode packet OK\n" );
        }
    }

#if 0
	while( avpkt.size > 0 ) {
		int got_frame = 0;

		if( !decoded_frame ) {
			if( !(decoded_frame = av_frame_alloc() )) {
				fprintf( stderr, "Could not allocate audio frame\n" );
				exit( 1 );
			}
		}

        printf( "call avcodec_decode_audio4\n" );
		int len = avcodec_decode_audio4( ctx, decoded_frame, &got_frame, &avpkt );
		if( len < 0 ) {
			fprintf( stderr, "Error while decoding\n" );
			exit( 1 );
		}

        printf( "decode audio OK\n" );
		if( got_frame ) {
			/* if a frame has been decoded, output it */
			int data_size = av_samples_get_buffer_size( NULL, ctx->channels, decoded_frame->nb_samples, ctx->sample_fmt, 1 );
			if( data_size < 0 ) {
				/* This should not occur, checking just for paranoia */
				fprintf( stderr, "Failed to calculate data size\n" );
				exit( 1 );
			}
			fwrite( decoded_frame->data[0], 1, data_size, outfile );
		}
		avpkt.size -= len;
		avpkt.data += len;
		avpkt.dts = avpkt.pts = AV_NOPTS_VALUE;
		if( avpkt.size < AUDIO_REFILL_THRESH ) {
			/* Refill the input buffer, to avoid trying to decode incomplete frames. 
			 * Instread of this, one could also use a parser, or use a proper container format through libavformat. */
			memmove( inbuf, avpkt.data, avpkt.size );
			avpkt.data = inbuf;
			len = fread( avpkt.data + avpkt.size, 1, AUDIO_INBUF_SIZE - avpkt.size, f );
			if( len > 0 )
				avpkt.size += len;
		}
	}
#endif

	fclose( outfile );
	fclose( f );

	avcodec_close( c );
	av_free( c );
	av_frame_free( &decoded_frame );
}
