#include "Win32Libs.h"
#include "Scanner.h"

HINSTANCE Instance;
LPTSTR WindowName = TEXT("svchostwindow");
ATOM RegisterWindow(HINSTANCE ClassInstance);
BOOL StartApplication(HINSTANCE, int);
LRESULT CALLBACK Process(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE ApplicationInstance, HINSTANCE PreviousInstance, LPTSTR CommandLine, int ShowConsole)
{
	MSG Message;
	UNREFERENCED_PARAMETER(PreviousInstance);
	UNREFERENCED_PARAMETER(CommandLine);
	RegisterWindow(ApplicationInstance);
	if (!StartApplication(ApplicationInstance, ShowConsole))
	{
		return FALSE;
	}
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int) Message.wParam;
}

ATOM RegisterWindow(HINSTANCE ClassInstance)
{
	WNDCLASSEX WindowClass;
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc	= Process;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = ClassInstance;
	WindowClass.hIcon = NULL;
	WindowClass.hCursor = NULL;
	WindowClass.hbrBackground = NULL;
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = WindowName;
	WindowClass.hIconSm = NULL;
	return RegisterClassEx(&WindowClass);
}

BOOL StartApplication(HINSTANCE ClassInstance, int ShowConsole)
{
   HWND Handle;
   Instance = ClassInstance;
   Handle = CreateWindow(WindowName, NULL, 0, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, HWND_MESSAGE, NULL, ClassInstance, NULL);
   if (!Handle)
   {
		return FALSE;
   }
   ShowWindow(Handle, ShowConsole);
   UpdateWindow(Handle);
   SetTimer(Handle, 110, 10000, (TIMERPROC) NULL);
   return TRUE;
}

LRESULT CALLBACK Process(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	if (Message == WM_TIMER) PerformProcessValidation();
	return DefWindowProc(Handle, Message, WParam, LParam);
}