//#include <unistd.h>
//#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>

/******************************************************************************
 * */
/*
 * Maximal period LFSR algorithms
 * Feed them with the old random value to get the next.
 * */

/** 32bit
 * Poly: x^32 + x^31 + x^29 + x + 1 
 * */
inline uint32_t galois32(uint32_t lfsr)
{
	return (lfsr >> 1) ^ (-(lfsr & 1u) & 0xD0000001u); 
}

/** 16bit
 * Poly: x^16 + x^14 + x^13 + x^11 + 1 
 * */
inline uint16_t galois16(uint16_t lfsr)
{
	return (lfsr >> 1) ^ (-(lfsr & 1u) & 0xB400u);    
}

/** 8bit
 * Poly: x^8 + x^6 + x^5 + x^4 + 1
 * */
inline uint8_t galois8(uint8_t lfsr)
{
	return (lfsr >> 1) ^ (-(lfsr & 1u) & 0xB8);
}

/** 32bit 
 * Poly: x^32 + x^31 + x^29 + x + 1 
 * */

inline uint32_t fib32(uint32_t lfsr)
{
	uint32_t bit = ((lfsr >> 0) ^ (lfsr >> 1) ^ 
			(lfsr >> 3) ^ (lfsr >> 31) ^ 1);
	return (lfsr >> 1 ) | (bit << 31);
}

/** 16bit
 * Poly: x^16 + x^14 + x^13 + x^11 + 1 
 * */
inline uint16_t fib16(uint16_t lfsr)
{
	uint16_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ 
			(lfsr >> 3) ^ (lfsr >> 5) ^ 1);
	return (lfsr >> 1) | (bit << 15);
}

/** 8bit
 * Poly: x^8 + x^6 + x^5 + x^4 + 1
 * */
inline uint8_t fib8(uint8_t lfsr)
{
	uint8_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ 
			(lfsr >> 3) ^ (lfsr >> 4) ^ 1);
	return (lfsr >> 1) | (bit << 7);
}

/******************************************************************************
 * */

/* Checksum functions
 *
 * */

/** 16bits 1'complement sum (RFC1071)
 *
 * */
uint16_t cksum16(void *addr, uint32_t length)
{
	uint32_t sum = 0;

	/*Sum all 16 bit words*/
	while (length > 1)
	{
		sum = sum + *((uint16_t*) addr++);
		length = length - 2;
	}
	/*Add left over byte if any*/
	if (length > 0)
		sum = sum + *((uint8_t*) addr);
	/*Fold 32bit sum to 16bits*/	
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	
	return (uint16_t)(~sum);
}



