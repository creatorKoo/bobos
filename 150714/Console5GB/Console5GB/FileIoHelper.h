/*-----------------------------------------------------------------------------
 * FileIoHelper.h
 *-----------------------------------------------------------------------------
 * 파일 사이즈가 4GB 가 넘는 경우 사용이 불가능
 * 4GB 이상의 파일에 대한 IO 처리가 필요한 경우 FileIoHelperClass.h 모듈을 
 * 이용할 것
 *-----------------------------------------------------------------------------
 * All rights reserved by somma (fixbrain@gmail.com, unsorted@msn.com)
 *-----------------------------------------------------------------------------
 * - 01.09.2010 created
**---------------------------------------------------------------------------*/

#include <stdio.h>

#ifndef _fileio_helper_h_
#define _fileio_helper_h_

#define log_err printf(
#define log_end );

bool is_file_existsW(_In_ const wchar_t* file_path);

typedef struct _FILE_CTX
{
    HANDLE  FileHandle;
    DWORD   FileSize;
    HANDLE  FileMap;
    PCHAR   FileView;

}FILE_CTX, *PFILE_CTX;
 
bool OpenFileContext(IN PCWSTR FilePath, IN bool ReadOnly, OUT PFILE_CTX& Ctx, IN PLARGE_INTEGER pOffset = 0, DWORD dwoffsetSize = 0);
void CloseFileContext(IN PFILE_CTX& Ctx);

class SmrtFileCtx
{
public:
	SmrtFileCtx(PFILE_CTX ctx) : mCtx(ctx) {}
	~SmrtFileCtx(){ CloseFileContext(mCtx);}
private:
	PFILE_CTX mCtx;
};
#endif//_dtagent_helper_h_