#ifndef _MBTIME01_H_
#define _MBTIME01_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <cmqc.h>
#include <stdint.h>

typedef struct MbTime {
	uint32_t 	StrucLength;

	uint32_t 	unk01;
	uint32_t 	unk02;
	uint32_t 	unk03;
	uint32_t 	unk04;
	uint32_t 	unk05;
	uint32_t 	unk06;

	uint32_t 	Encoding;

	uint32_t 	IdentifierLength;
	char  		*Identifier;

	uint32_t 	RootIdLength;
	char		*RootId;

	uint32_t 	NextHdrLength;
	char		*NextHdr;

	uint32_t 	PaddingLength;

	uint32_t 	DomainLength;
	char 		*Domain;

	uint32_t 	unk08;
	uint32_t 	unk09;
	uint32_t 	unk10;

	uint32_t 	DateStrLength;
	char 		*DateStr;

	uint32_t 	TimeStrLength;
	char 		*TimeStr;


	MQMD		md;
} MbTime_s; 

size_t Mbt_Init(MbTime_s **pInst, MQLONG mdEnc, MQBYTE *buf);
void Mbt_Free(MbTime_s **pInst);
#ifdef __cplusplus
}
#endif
#endif
