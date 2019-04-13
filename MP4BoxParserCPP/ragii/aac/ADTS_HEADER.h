#pragma once
#include <stdint.h>

namespace ragii { namespace aac {

	struct ADTS_HEADER
	{
		uint16_t sync_word : 12;
		uint8_t mpeg_version : 1;
		uint8_t layer : 2;
		uint8_t protection : 1;
		uint8_t freq_number : 4;
		uint8_t private_stream : 1;
		uint8_t channel : 3;
		uint8_t original : 1;
		uint8_t home : 1;
		uint8_t protected_stream : 1;
		uint8_t protect_start : 1;
		uint16_t header_length : 13;
		uint16_t buffer_length : 11;
		uint8_t frame_count : 2;
		uint16_t crc : 16;
	};

	struct FREQ_INFO
	{
		uint8_t number;
		uint16_t freq;
	};

	static FREQ_INFO FREQ_TABLE[] = {
		{ 0x00, 96000 },
		{ 0x01, 88200 },
		{ 0x02, 64000 },
		{ 0x03, 48000 },
		{ 0x04, 44100 },
		{ 0x05, 32000 },
		{ 0x06, 24000 },
		{ 0x07, 22050 },
		{ 0x08, 16000 },
		{ 0x09, 12000 },
		{ 0x0a, 11025 },
		{ 0x0b,  8000 },
		{ 0x0c,  7350 },
		{ 0x0d,     0 },
		{ 0x0e,     0 },
		{ 0x0f,     0 },
	};

} }
