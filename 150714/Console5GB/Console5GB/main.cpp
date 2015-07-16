/*---------------------------------------------------------------------------- -
*FileIoHelper.cpp
*---------------------------------------------------------------------------- -
*
*---------------------------------------------------------------------------- -
*All rights reserved by somma(fixbrain@gmail.com, unsorted@msn.com)
*---------------------------------------------------------------------------- -
*-01.09.2010 created
**-------------------------------------------------------------------------- - */

#include <Windows.h>
#include <crtdbg.h>
#include <strsafe.h>

#include "FileIoHelper.h"

int main(){
	LARGE_INTEGER l = { 0 };
	PFILE_CTX f = 0;

	OpenFileContext(L"4GBplus1.bin", true, f, &l, 10);
	CloseFileContext(f);

	f = 0;
	OpenFileContext(L"10mb.bin", true, f);
	CloseFileContext(f);
}