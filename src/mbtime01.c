#include <cmqc.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "mbtime01.h"
#include "macros.h"

// Too lazy to figure out why iconv wouldn't do this for me
// this function converts inbuf 
// char inbuf[] = {'\0', 'f', '\0', 'r', '\0', 'e', '\0', 'd'}
//   to
// char outbuf[] = {'f', 'r', 'e', 'd'}
static void xlate(MQBYTE *inbuf, size_t inbufsz, char* outbuf, size_t outbufsz) {
	if (outbufsz < inbufsz/2) return;
	memset(outbuf, 0, outbufsz);
	for (size_t i=0; i < inbufsz; i++) {
		if (*inbuf) {
			*outbuf++ = *inbuf;
		}
		inbuf++;
	}
}

// Initialize the MbTime_s struct from a buffer
// The caller must free the value pointed to by ppInst must be using
// Mbt_Free() 
size_t Mbt_Init(MbTime_s **ppInst, MQLONG mdEnc, MQBYTE *buf) {
	if (! ppInst) {
		return 0;
	}
	MbTime_s *inst = malloc(sizeof(MbTime_s));
	*ppInst = inst;
	memset(inst, 0, sizeof(MbTime_s));

	char *outBuf = NULL;
	size_t outLen = 500;
	outBuf = malloc(outLen);
	int pos = 0;
	memcpy(&inst->StrucLength, buf + pos, sizeof(uint32_t));
	inst->StrucLength =  MQLONG_TO_NATIVE(mdEnc, inst->StrucLength);
	pos += sizeof(inst->StrucLength);
	pos += sizeof(inst->unk01);
	pos += sizeof(inst->unk02);
	pos += sizeof(inst->unk03);
	pos += sizeof(inst->unk04);
	pos += sizeof(inst->unk05);
	pos += sizeof(inst->unk06);
	
	memcpy(&inst->Encoding, buf + pos, sizeof(inst->Encoding));
	inst->Encoding =  MQLONG_TO_NATIVE(mdEnc, inst->Encoding);
	pos += sizeof(inst->Encoding);

	memcpy(&inst->IdentifierLength, buf + pos, sizeof(inst->IdentifierLength));
	inst->IdentifierLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->IdentifierLength);
	pos += sizeof(inst->IdentifierLength);
	xlate(buf + pos, inst->IdentifierLength, outBuf, outLen);
	asprintf(&inst->Identifier, "%s", outBuf);
	pos += inst->IdentifierLength;

	memcpy(&inst->RootIdLength, buf + pos, sizeof(inst->RootIdLength));
	inst->RootIdLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->RootIdLength);
	pos += sizeof(inst->RootIdLength);
	xlate(buf + pos, inst->RootIdLength, outBuf, outLen);
	asprintf(&inst->RootId, "%s", outBuf);
	pos += inst->RootIdLength;

	memcpy(&inst->NextHdrLength, buf + pos, sizeof(inst->NextHdrLength));
	inst->NextHdrLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->NextHdrLength);
	pos += sizeof(inst->NextHdrLength);
	xlate(buf + pos, inst->NextHdrLength, outBuf, outLen);
	asprintf(&inst->NextHdr, "%s", outBuf);
	pos += inst->NextHdrLength;

	memcpy(&inst->PaddingLength, buf + pos, sizeof(inst->PaddingLength));
	inst->PaddingLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->PaddingLength);
	pos += sizeof(inst->PaddingLength);
	pos += inst->PaddingLength;

	memcpy(&inst->DomainLength, buf + pos, sizeof(inst->DomainLength));
	inst->DomainLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->DomainLength);
	pos += sizeof(inst->DomainLength);
	xlate(buf + pos, inst->DomainLength, outBuf, outLen);
	asprintf(&inst->Domain, "%s", outBuf);
	pos += inst->DomainLength;

	pos += sizeof(inst->unk08);
	pos += sizeof(inst->unk09);
	pos += sizeof(inst->unk10);

	memcpy(&inst->DateStrLength, buf + pos, sizeof(inst->DateStrLength));
	inst->DateStrLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->DateStrLength);
	pos += sizeof(inst->DateStrLength);
	xlate(buf + pos, inst->DateStrLength, outBuf, outLen);
	asprintf(&inst->DateStr, "%s", outBuf);
	pos += inst->DateStrLength;

	memcpy(&inst->TimeStrLength, buf + pos, sizeof(inst->TimeStrLength));
	inst->TimeStrLength =  MQLONG_TO_NATIVE(inst->Encoding, inst->TimeStrLength);
	pos += sizeof(inst->TimeStrLength);
	xlate(buf + pos, inst->TimeStrLength, outBuf, outLen);
	asprintf(&inst->TimeStr, "%s", outBuf);
	pos += inst->TimeStrLength;

	memcpy(&inst->md, buf + pos, sizeof(MQMD));
	free(outBuf);

	return inst->StrucLength;
}

void Mbt_Free(MbTime_s **ppInst) {
	if (ppInst && *ppInst) {
		MbTime_s *inst = *ppInst;	
		if (inst->Identifier) free(inst->Identifier);
		if (inst->RootId) free(inst->RootId);
		if (inst->NextHdr) free(inst->NextHdr);
		if (inst->Domain) free(inst->Domain);
		if (inst->DateStr) free(inst->DateStr);
		if (inst->TimeStr) free(inst->TimeStr);
		free(inst);
	}
	// Ensure that Mbt_Free is idempotent
	*ppInst = NULL;
}
