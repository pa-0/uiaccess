# Get UIAccess through System token

This project is used to obtain UIAccess permissions, which allows your program window to obtain a higher Z order, such as higher than the task manager, and on the same layer as the on-screen keyboard. It can be used to solve the problem of the window being blocked when making a screen marking/recording tool.

## Effect comparison

Taking Task Manager as an example, first open "Bring to Top" of Task Manager. Its window Band is `ZBID_SYSTEM_TOOLS`, which is higher than the normal window Band. When UIAccess is not enabled, the window Z order is always lower than the task manager, even using `SetWindowPos(HWND_TOPMOST)`: 

![uia_off](https://github.com/user-attachments/assets/7a5820c0-35b8-4c59-beca-d1b843d44445)

After enabling UIAccess and calling `SetWindowPos(HWND_TOPMOST)`, the window Z order will be higher than the task manager: 

![uia_on](https://github.com/user-attachments/assets/52ec14cf-2a0e-4228-9d92-b33ebd05f919)

## Conditions and usage

The program needs to be run with elevated privileges, so it is best to set a list of administrator privileges, or start it through an elevated process. Otherwise, ULAccess cannot be obtained, and the function return value is `ERROR_NOT_FOUND`. After adding header files and source files, call `PrepareForUIAccess()` at the very beginning of the program. If the setting is successful, `ERROR_SUCCESS` is returned, otherwise an error code is returned.

## Program principle

Compared with the previous version, the problem of UIAccess setting failure when the user right "Replace process token" is turned off is fixed: the program starts the process twice instead of 3 times, and there is no need to start another process with System permissions, eliminating the IPC communication process.

The process is started with administrator privileges, and then checks whether it has UIAccess privileges. 
At this point, it has not yet obtained the privileges, so it traverses the process list and tries to obtain the token of `winlogon.exe` under the same session, and uses this token to create another token with `TokenUIAccess`, and then uses it to start another instance. This instance checks the UIAccess privilege, and the privileges are satisfied, and returns `ERROR_SUCCESS`, then the old process exits, and the new process with privileges continues to run.

## Introduction to Window Z Order

In Windows 7 and below, you can directly use `SetWindowPos(HWND_TOPHOST)` to put the window at the top, but starting from Windows 8, Microsoft introduced other window segments (Bands), and their order from low to high is as follows

```
ZBID_DESKTOP
ZBID_IMMERSIVE_BACKGROUND
ZBID_IMMERSIVE_APPCHROME
ZBID_IMMERSIVE_MOGO
ZBID_IMMERSIVE_INACTIVEMOBODY
ZBID_IMMERSIVE_NOTIFICATION
ZBID_IMMERSIVE_EDGY
ZBID_SYSTEM_TOOLS
ZBID_LOCK（仅Windows 10）
ZBID_ABOVELOCK_UX（仅Windows 10）
ZBID_IMMERSIVE_IHM
ZBID_GENUINE_WINDOWS
ZBID_UIACCESS
```

The default window segment is `ZBID_DESKTOP`, which means that no matter how `SetWindowPos` is called, the Z order of the window is always lower than that of windows with other higher segments set.

So why not set other window segments?

There are the following APIs in Windows that can change the window segment of a program:

```c
HWND WINAPI CreateWindowInBand(
	DWORD dwExStyle,
  	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam,
	DWORD dwBand
);
HWND WINAPI CreateWindowInBandEx(
	DWORD dwExStyle,
  	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam,
	DWORD dwBand,
	DWORD dwTypeFlags
);
BOOL WINAPI SetWindowBand(
	HWND hWnd, 
	HWND hwndInsertAfter, 
	DWORD dwBand
);
```

But the program that calls `CreateWindowInBand(Ex)` must be digitally signed with a Microsoft certificate, that is, only Windows built-in programs can use these APIs, which is what the Task Manager does. `SetWindowBand` needs to call a private API: `NtUserEnableIAMAccess`, which has a handle-like parameter (key), which can only be obtained through `NtUserAcquireIAMKey`. The condition for the successful call of `NtUserAcquireIAMKey` is that the calling thread must be the current desktop thread (that is, the thread that calls `SetShellWindows(Ex))`, and it can only be obtained once, otherwise the function will return `ERROR_ACCESS_DENIED`. You can't even inject `explorer.exe` to obtain the key because `explorer.exe` has already called `NtUserAcquireIAMKey` once. That is, only the desktop manager can use `SetWindowBand`.

Is there any other way? I noticed that the on-screen keyboard `(osk.exe)` and a VS tool `Inspect.exe` can also set the window higher than the task manager. After reverse engineering, I found that they are just `SetWindowPos(HWND_TOPHOST)`. Finally, I found that there is an item in the program list:

```
<requestedExecutionLevel level="asInvoker" uiAccess="true"/>
```

[MSDN](https://learn.microsoft.com/en-us/windows/security/threat-protection/security-policy-settings/user-account-control-allow-uiaccess-applications-to-prompt-for-elevation-without-using-the-secure-desktop) explains that this UIAccess permission is used to support accessibility services. Through it, the window of the elevated process can be accessed from the non-elevated process. For security reasons, if you want to enable it, you must meet the following conditions:

* The application must be digitally signed and can be verified using a digital certificate associated with the Trusted Root Certification Authorities store on the local computer. 
* The application must be installed in a local folder that can be written to only by administrators, such as the `Program Files` directory. Permitted directories include:
  * `%ProgramFiles%` and its subdirectories
  * `%WinDir%` and its subdirectories, except for a few subdirectories that standard users have write permissions to.

The `TokenUIAccess` property is available in the process token, which means that after the privilege is elevated, we can set this permission through `SetTokenInformation` to bypass the digital signature and the specified installation path.

But after some testing, I finally found that the `SeTcbPrivilege` privilege is required to complete this operation, so one solution is to "steal" a token from another system process, so that the privilege can be obtained. However, modifying the UIAccess of a running program is invalid, so in the end I can only start another process. Although this is a bit flawed, it is still more fault-tolerant than the previous injection into `explorer.exe` and more practical than digital signatures

## Reference

[Window z-order in Windows 10 – ADeltaX Blog](https://blog.adeltax.com/window-z-order-in-windows-10/)

