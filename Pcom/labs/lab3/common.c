#include "common.h"

uint8_t simple_csum(uint8_t *buf, size_t len) {

	/* TODO 1.1: Implement the simple checksum algorithm */
	uint8_t sum = 0;

	for (int i = 0; i < len; i++) {
		sum += buf[i];
	}

	return sum;
}

uint32_t crc32(uint8_t *buf, size_t len)
{
	/* TODO 2.1: Implement the CRC 32 algorithm */

	/* Iterate through each byte of buff */
	
		/* Iterate through each bit */
		/* If the bit is 1, compute the new reminder */

	/* By convention, we negate the crc */

	uint32_t crc = ~0;
	const uint32_t POLY = 0xEDB88320;

	while (len--) {
		crc = crc ^ *buf++;

		for (int bit = 0; bit < 8; bit++) {
			if (crc & 1)
				crc = (crc >> 1) ^ POLY; /* bitul cel mai din dreapta e 1 -> facem XOR cu polinomul */
			else
				crc = (crc >> 1); /* bitul e 0 -> doar shift, fara XOR */
		}
	}

	crc = ~crc;
	
	return crc;	
}
