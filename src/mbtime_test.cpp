#include <string>
#include <iostream>
#include "mbtime01.h"
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <cmqc.h>
#include <unistd.h>

using namespace std;
// Pass in the name of a raw MQ message (with headers) saved to a file
int main(int argc, char** argv) {

	if (argc < 2) return 1;

	size_t length = 350;
	off64_t offset = 0;
	int prot = PROT_READ;
	int flags = MAP_PRIVATE;
	int fd;

	fd = open(argv[1], O_RDONLY);
	char * buf = (char*) mmap64(NULL, length, prot, flags, fd, offset);

	MQMD *pMd = (MQMD*) buf;

	cout << "Mapped " << length << " bytes from file " << argv[1] << endl;

	cout << "=============MQMD========================" << endl;
	cout << "Encoding:           " << pMd->Encoding << endl;

	MbTime_s *mbt = NULL;
	size_t mbt_sz = Mbt_Init(&mbt, pMd->Encoding, (MQBYTE*) (buf+sizeof(MQMD)));

	cout << "Call to Mbt_Init returned: " << mbt_sz << endl;
	cout << "=============MBTIME======================" << endl;
	cout << "StrucLength:        " << mbt->StrucLength << endl;
	cout << "Encoding:           " << mbt->Encoding << endl;
	cout << "Identifier:         " << mbt->Identifier << endl;
	cout << "RootId:             " << mbt->RootId << endl;
	cout << "NextHdr:            " << mbt->NextHdr << endl;
	cout << "Domain:             " << mbt->Domain << endl;
	cout << "DateStr:            " << mbt->DateStr << endl;
	cout << "TimeStr:            " << mbt->TimeStr << endl;
	cout << "=========================================" << endl;
	cout << "MQMD.ReplyToQ:      " << mbt->md.ReplyToQ   << endl;

	Mbt_Free(&mbt);

//	munmap(buf, length);
	close(fd);
}
