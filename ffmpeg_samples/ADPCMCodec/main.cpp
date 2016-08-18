#include <stdio.h>
#include "ADPCMCodec.h"

int main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("Usage: xx encode/decode srcFile, dstFile");
		return -1;
	}

	char* inFile = argv[2];
	char* outFile = argv[3];

	FILE* in;
	FILE* out;

	in = fopen(inFile, "rb");
	if (!in) {
		printf("Failed to open %s\n", inFile);
		return -1;
	}

	out = fopen(outFile, "wb");
	if (!out) {
		printf("Failed to open %s\n", outFile);
		return -1;
	}

	if (strcmp(argv[1], "encode") == 0) {
		ADPCMCodec codec;
		int ret = codec.encoderInit();

		unsigned int bufSize;
		unsigned char* buf;
		codec.getEncBuf(&buf, &bufSize);

		const int outBufSize = 2048;
		unsigned char outBuf[outBufSize];


		if (ret < 0) {
			printf("Failed to init ADPCM encoder\n");
			return ret;
		}

		int size = 0;
		while ((size = fread(buf, 1, bufSize, in)) > 0) {
			ret = codec.encode(outBuf, outBufSize, buf, size);
			if (ret < 0) {
				printf("Failed to encode to ADPCM\n");
				return ret;
			}

			fwrite(outBuf, 1, ret, out);
		}

		codec.encoderFree();

		fclose(out);
		fclose(in);

	} else if (strcmp(argv[1], "decode") == 0) {
		int bufSize = 512;
		if (argc == 5) {
			bufSize = atoi(argv[4]);
		}
		unsigned char* buf = ( unsigned char* )malloc( bufSize );
		int outBufSize = 4 * bufSize;
		unsigned char* outBuf = ( unsigned char* )malloc( outBufSize );

		ADPCMCodec codec;
		int ret = codec.decoderInit();
		if (ret < 0) {
			printf("Failed to init ADPCM deocder\n");
			goto End;
		}
		int size = 0;

		while ((size = fread(buf, 1, bufSize, in)) > 0) {
			ret = codec.decode((unsigned short*)outBuf, outBufSize, buf, size);
			if (ret < 0) {
				printf("Failed to decode ADPCM\n");
				goto End;
			}

			fwrite(outBuf, 1, ret, out);
		}

	End:
		if (buf)
			free(buf);
		if (outBuf)
			free(outBuf);

		codec.decoderFree();

		fclose(out);
		fclose(in);

		return ret;
	}
}