// ConsoleTestApplication1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <Windows.h>
#include <strsafe.h>
#include <stdint.h>

/**
* @brief
* @param
* @see
* @remarks
* @code
* @endcode
* @return
**/
bool is_file_existsW(_In_ const wchar_t* file_path)
{
	//_ASSERTE(NULL != file_path);
	//_ASSERTE(TRUE != IsBadStringPtrW(file_path, MAX_PATH));
	if ((NULL == file_path) || (TRUE == IsBadStringPtrW(file_path, MAX_PATH))) return false;

	WIN32_FILE_ATTRIBUTE_DATA info = { 0 };

	//
	// CreateFile()�� �ƴ� GetFileAttributesEx()�� �̿��ϸ� ������ �ٸ� process�� ���� lock�Ǿ� �־
	// ���� ���翩�θ� ��Ȯ�� üũ�� �� �ִ�.
	//
	if (GetFileAttributesExW(file_path, GetFileExInfoStandard, &info) == 0)
		return false;
	else
		return true;
}

/**
* @brief
* @param
* @see
* @remarks
* @code
* @endcode
* @return
**/
void print(_In_ const char* fmt, _In_ ...)
{
	char log_buffer[2048];
	va_list args;

	va_start(args, fmt);
	HRESULT hRes = StringCbVPrintfA(log_buffer, sizeof(log_buffer), fmt, args);
	if (S_OK != hRes)
	{
		fprintf(
			stderr,
			"%s, StringCbVPrintfA() failed. res = 0x%08x",
			__FUNCTION__,
			hRes
			);
		return;
	}

	OutputDebugStringA(log_buffer);
	fprintf(stdout, "%s \n", log_buffer);
}


/**
* @brief
* @param
* @see
* @remarks
* @code
* @endcode
* @return
**/
bool create_bob_txt()
{
	// current directory �� ���Ѵ�.
	wchar_t *buf = NULL;
	uint32_t buflen = 0;
	buflen = GetCurrentDirectoryW(buflen, buf);
	if (0 == buflen)
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		return false;
	}

	buf = (PWSTR)malloc(sizeof(WCHAR) * buflen);
	if (0 == GetCurrentDirectoryW(buflen, buf))
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		free(buf);
		return false;
	}

	// current dir \\ bob.txt ���ϸ� ����
	wchar_t file_name[260];
	if (!SUCCEEDED(StringCbPrintfW(
		file_name,
		sizeof(file_name),
		L"%ws\\bob.txt",
		buf)))
	{
		print("err, can not create file name");
		free(buf);
		return false;
	}
	free(buf); buf = NULL;

	if (true == is_file_existsW(file_name))
	{
		::DeleteFileW(file_name);
	}

	// ���� ����
	HANDLE file_handle = CreateFileW(
		file_name,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
		return false;
	}

	// ���Ͽ� ������ ����
	DWORD bytes_written = 0;
	wchar_t string_buf[1024];
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"���ع��� ��λ��� ������ �⵵�� �ϴ����� �����ϻ� �츮���󸸼�")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}
	
	char string_bufaa[1024]; // ��ȯ�� UTF-8 char ���� ����
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, NULL, 0, NULL, NULL); // UTF8��ȯ�� �ʿ��� ���ڼ�
	WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, string_bufaa, size_needed, NULL, NULL); // UTF8 ��ȯ
	
	if (!WriteFile(file_handle, string_bufaa, size_needed-1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	// ����� ����
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"All work and no play makes jack a dull boy.")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	size_needed = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, string_bufaa, size_needed, NULL, NULL);
	
	if (!WriteFile(file_handle, string_bufaa, size_needed - 1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	char string_bufa[1024];
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"���ع��� ��λ��� ������ �⵵�� �ϴ����� �����ϻ� �츮���󸸼�")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	size_needed = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, string_bufaa, size_needed, NULL, NULL);

	if (!WriteFile(file_handle, string_bufaa, size_needed - 1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	// ����� ����
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"All work and no play makes jack a dull boy.")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}
	
	size_needed = WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, string_buf, -1, string_bufaa, size_needed, NULL, NULL);

	if (!WriteFile(file_handle, string_bufaa, size_needed - 1, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	// current dir \\ bob2.txt ���ϸ� ����
	buf = (PWSTR)malloc(sizeof(WCHAR) * buflen);
	if (0 == GetCurrentDirectoryW(buflen, buf))
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		free(buf);
		return false;
	}
	wchar_t file_name2[260];
	if (!SUCCEEDED(StringCbPrintfW(
		file_name2,
		sizeof(file_name2),
		L"%ws\\bob2.txt",
		buf)))
	{
		print("err, can not create file name");
		free(buf);
		return false;
	}
	free(buf); buf = NULL;
	
	// ���� ����
	CopyFile(file_name, file_name2, false);

	// 2���� �б�
	HANDLE f2 = CreateFile(file_name2, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD fs = GetFileSize(f2, NULL);

	/* 1. ReadFile�� �����б�
	ReadFile(f2, string_bufaa, fs, NULL, NULL);
	//*/

	//* 2. MemoryMapedIO �� �����б�
	HANDLE hFm = CreateFileMapping(f2, NULL, PAGE_READONLY, 0, 0, NULL);
	LPVOID lpFile = MapViewOfFile(hFm, FILE_MAP_READ, 0, 0, 0);

	memcpy(string_bufaa, lpFile, fs);
	string_bufaa[fs] = '\0';

	UnmapViewOfFile(lpFile);
	CloseHandle(hFm);
	//*/

	// UTF-8 to wide String���� ��ȯ�Ͽ� ���
	size_needed = MultiByteToWideChar(CP_UTF8, 0, string_bufaa, fs, NULL, 0);
	MultiByteToWideChar(CP_UTF8, 0, string_bufaa, fs, string_buf, size_needed);
	string_buf[size_needed] = L'\0';
	// wide string to mulity byte
	size_needed = WideCharToMultiByte(CP_ACP, 0, string_buf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, string_buf, -1, string_bufaa, size_needed, NULL, NULL);

	printf("%s", string_bufaa);

	// ���� �ݱ�
	CloseHandle(file_handle);
	CloseHandle(f2);

	// �Ϸ� �� ���� �����
	if (true == is_file_existsW(file_name))
	{
		::DeleteFileW(file_name);
	}
	if (true == is_file_existsW(file_name2))
	{
		::DeleteFileW(file_name2);
	}
	return true;

}

int _tmain(int argc, _TCHAR* argv[])
{
	create_bob_txt();
	return 0;
}

