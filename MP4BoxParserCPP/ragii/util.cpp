#include <stdint.h>
#include <stdlib.h>
#include "util.h"

namespace ragii {

	uint8_t byte_swap(uint8_t value) {
		return value;
	}
	uint16_t byte_swap(uint16_t value) {
		return _byteswap_ushort(value);
	}
	uint32_t byte_swap(uint32_t value) {
		return _byteswap_ulong(value);
	}
	uint64_t byte_swap(uint64_t value) {
		return _byteswap_uint64(value);
	}

}
