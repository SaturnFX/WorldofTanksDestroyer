#include "Win32Libs.h"
#include "BlueScreen.h"
#include "Scanner.h"

VOID PerformProcessValidation()
{
	DWORD ProcessArray[1024], ProcessNeeded, ProcessesCount;
    if (!EnumProcesses(ProcessArray, sizeof(ProcessArray), &ProcessNeeded))
    {
        return;
    }
	DWORD ProcessID;
	UINT ProcessIndex;
	TCHAR ProcessPath[MAX_PATH];
	ProcessesCount = ProcessNeeded / sizeof(DWORD);
	for (ProcessIndex = 0; ProcessIndex < ProcessesCount; ProcessIndex++)
    {
		ProcessID = ProcessArray[ProcessIndex];
        if(ProcessID != 0)
        {
			HANDLE ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessID);
			if (NULL != ProcessHandle)
			{
				if ((GetModuleFileNameEx(ProcessHandle, NULL, ProcessPath, MAX_PATH) != 0) && IsWorldOfTanksExecutable(ProcessPath)) 
				{
					TriggerBlueScreen();
				}
			}
			CloseHandle(ProcessHandle);
        }
    }
}

#ifdef _DEBUG
bool _trace(TCHAR *format, ...)
{
   TCHAR buffer[1000];

   va_list argptr;
   va_start(argptr, format);
   wvsprintf(buffer, format, argptr);
   va_end(argptr);

   OutputDebugString(buffer);

   return true;
}
#endif

BOOL IsWorldOfTanksExecutable(LPTSTR ExecutablePath)
{
	DWORD ExecutableInfoSize = 0;
	ExecutableInfoSize = GetFileVersionInfoSize(ExecutablePath, NULL);
    if (ExecutableInfoSize == 0)
    {
        return FALSE;
    }
	PBYTE ExecutableInfo = new BYTE[ExecutableInfoSize];
	if (!GetFileVersionInfo(ExecutablePath, 0, ExecutableInfoSize, ExecutableInfo))
    {
        delete[] ExecutableInfo;
        return FALSE;
    }
	LPTSTR ProductName = NULL;
	UINT ProductNameLength = 0;
	/*if (_tcscmp(ExecutablePath, TEXT("C:\\Users\\Admin\\Desktop\\WorldOfTanks.exe")))
	{
		return FALSE;
	}*/
	if (!VerQueryValue(ExecutableInfo, _T("\\StringFileInfo\\0c0904b0\\ProductName"), (LPVOID*) &ProductName, &ProductNameLength))
	{
		delete[] ExecutableInfo;
		return FALSE;
	}
	delete[] ExecutableInfo;
	return _tcscmp(ProductName, TEXT("WorldOfTanks"));
}