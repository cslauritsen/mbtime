#ifndef _MACROS_H_
#define _MACROS_H_
#include <cmqc.h>

//#define MIN(x,y) ((x) < (y) ? (x) : (y))
//#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define ENC_IS_NORMAL(x) (((x)& MQENC_INTEGER_MASK) == MQENC_INTEGER_NORMAL)
#define NATIVE_IS_NORMAL ((MQENC_NATIVE & MQENC_INTEGER_MASK) == MQENC_INTEGER_NORMAL)
#define ENC_IS_NATIVE(x) ( ((x) & MQENC_INTEGER_MASK) == (MQENC_NATIVE & MQENC_INTEGER_MASK) )
#define MQLONG_TO_NATIVE(e, l) ( ENC_IS_NATIVE((e)) ? (l) \
: (NATIVE_IS_NORMAL ? htonl((l)) : ntohl((l))) )

#endif
