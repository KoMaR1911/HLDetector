
#include <Windows.h>
#include <iostream>
#include "XOR.h"
#include "Lazy_Import.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")

typedef struct _FILE_STANDARD_INFORMATION {
	LARGE_INTEGER AllocationSize;
	LARGE_INTEGER EndOfFile;
	ULONG	      NumberOfLinks;
	BOOLEAN	      DeletePending;
	BOOLEAN	      Directory;
} FILE_STANDARD_INFORMATION, * PFILE_STANDARD_INFORMATION;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES* POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK
{
	union
	{
		NTSTATUS Status;
		PVOID Pointer;
	};
	ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

typedef NTSTATUS(NTAPI* fNtOpenFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions);

fNtOpenFile nfNtOpenFile;

NTSTATUS NTAPI hkNtOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions)
{

	auto STATUS = nfNtOpenFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, ShareAccess, OpenOptions);

	if (ObjectAttributes != nullptr)
	{
		if (ObjectAttributes->ObjectName != nullptr && ObjectAttributes->ObjectName->Buffer != nullptr)
		{
			std::wstring a = XorStringW(L"\\data\\images\\");
			std::wstring b = XorStringW(L"\\data\\config\\");
			std::wstring c = XorStringW(L"HLBot");

			//	printf("Hook NtOpenFile: %ws \n", ObjectAttributes->ObjectName->Buffer);

			if ((std::wcsstr(ObjectAttributes->ObjectName->Buffer, a.c_str())) || (std::wcsstr(ObjectAttributes->ObjectName->Buffer, b.c_str()) || (std::wcsstr(ObjectAttributes->ObjectName->Buffer, c.c_str()))))
			{
				LI_FN(ExitProcess)(0);
				LI_FN(__fastfail)(0);
			}
		}

	}

	return STATUS;

}


int main()
{
	auto oNtOpenFile = fNtOpenFile(GetProcAddress(GetModuleHandleA(XorString("ntdll.dll")), XorString("NtOpenFile")));

#ifdef DEBUG
	std::cout << "NtOpenFile offset: " << oNtOpenFile << "\n";
#endif // DEBUG



	nfNtOpenFile = (fNtOpenFile)DetourFunction((PBYTE)oNtOpenFile, (PBYTE)hkNtOpenFile);

#ifdef DEBUG
	std::cout << "NtOpenFile hooked! \n ";
#endif // DEBUG
 
}
