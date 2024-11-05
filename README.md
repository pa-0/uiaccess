# Obtain UIAccess with a System token
[<svg class="octicon octicon-link" viewbox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg>](https://github.com/killtimer0/uiaccess#%E9%80%9A%E8%BF%87system%E4%BB%A4%E7%89%8C%E8%8E%B7%E5%8F%96uiaccess)

This project is used to obtain UIAccess permissions, which allows you to get a higher Z-order in your program window, such as higher than the Task Manager, etc., on the same level as the on-screen keyboard. It can be used to solve the problem of the window being occluded when making screen markers/recording tools.

## Comparison of results
[<svg class="octicon octicon-link" viewbox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg>](https://github.com/killtimer0/uiaccess#%E6%95%88%E6%9E%9C%E5%AF%B9%E6%AF%94)

<font _mstmutation="1" _msttexthash="9320948" _msthash="271" style="box-sizing: border-box;">Take Task Manager as an example, first open the "Put on top" of Task Manager, and its window Band is higher than the regular window Band.</font>`ZBID_SYSTEM_TOOLS`

<font _mstmutation="1" _msttexthash="8423857" _msthash="272" style="box-sizing: border-box;">When UIAccess is not enabled, the window Z-order is always lower than that of Task Manager, regardless of whether it is or not:</font>`SetWindowPos(HWND_TOPMOST)`

<animated-image _msthidden="8" data-catalyst="" style="box-sizing: border-box; max-width: 100%; display: inline-block;"><a target="_blank" rel="noopener noreferrer nofollow" href="https://raw.githubusercontent.com/killtimer0/uiaccess/master/img/uia_off.gif" data-target="animated-image.originalLink" _msthidden="1" style="box-sizing: border-box; background-color: transparent; color: var(--fgColor-accent, var(--color-accent-fg)); text-decoration: underline; text-underline-offset: 0.2rem;"><img src="https://raw.githubusercontent.com/killtimer0/uiaccess/master/img/uia_off.gif" alt="Before activation" data-target="animated-image.originalImage" _mstalt="7545382" _msthash="273" _mstvisible="0" style="box-sizing: content-box; border-style: none; display: inline-block; width: 682px; max-width: 100%;"></a></animated-image>

<font _mstmutation="1" _msttexthash="5410912" _msthash="274" style="box-sizing: border-box;">When UIAccess is enabled and called, the window Z-order will be higher than that of the Task Manager:</font>`SetWindowPos(HWND_TOPMOST)`

<animated-image _msthidden="8" data-catalyst="" style="box-sizing: border-box; max-width: 100%; display: inline-block;"><a target="_blank" rel="noopener noreferrer nofollow" href="https://raw.githubusercontent.com/killtimer0/uiaccess/master/img/uia_on.gif" data-target="animated-image.originalLink" _msthidden="1" style="box-sizing: border-box; background-color: transparent; color: var(--fgColor-accent, var(--color-accent-fg)); text-decoration: underline; text-underline-offset: 0.2rem;"><img src="https://raw.githubusercontent.com/killtimer0/uiaccess/master/img/uia_on.gif" alt="Once enabled" data-target="animated-image.originalImage" _mstalt="7597915" _msthash="275" _mstvisible="0" style="box-sizing: content-box; border-style: none; display: inline-block; width: 682px; max-width: 100%;"></a></animated-image>

## Conditions and Usage
[<svg class="octicon octicon-link" viewbox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg>](https://github.com/killtimer0/uiaccess#%E6%9D%A1%E4%BB%B6%E5%92%8C%E7%94%A8%E6%B3%95)

<font _mstmutation="1" _msttexthash="97701357" _msthash="278" style="box-sizing: border-box;">The program needs to be elevated to run (), so it is better to set up a manifest to request administrator privileges, or start it through a process that has elevated privileges, otherwise you will not be able to get UIAccess, and the function will return a value. After adding the header file and the source file, you can call it at the very beginning of the program, and return it if the setting is successful, otherwise an error code will be returned.</font>`elevated``ERROR_NOT_FOUND``PrepareForUIAccess()``ERROR_SUCCESS`

## Principles of the program
[<svg class="octicon octicon-link" viewbox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg>](https://github.com/killtimer0/uiaccess#%E7%A8%8B%E5%BA%8F%E5%8E%9F%E7%90%86)

> 
> Compared with the previous version, the UIAccess setting fails when the user permission "Replace Process Token" is turned off; The program was changed from starting the process three times to two times, and another process without the need to start the System privilege eliminated the IPC communication process.

<font _mstmutation="1" _msttexthash="120427216" _msthash="282" style="box-sizing: border-box;">The process starts with administrator privileges and then detects if it has UIAccess privileges. It doesn't have permission yet, so it iterates through the list of processes, tries to get a token under the same session, uses that token to create another token it has, and then uses it to start another instance. This instance detects the UIAccess permission, the permission has been satisfied, returns, and then the old process exits, and the new process with the permission continues to run.</font>`winlogon.exe``TokenUIAccess``ERROR_SUCCESS`

## Introduction to the Z-order of the window
[<svg class="octicon octicon-link" viewbox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg>](https://github.com/killtimer0/uiaccess#%E7%AA%97%E5%8F%A3z%E5%BA%8F%E7%9A%84%E4%BB%8B%E7%BB%8D)

<font _mstmutation="1" _msttexthash="22559134" _msthash="285" style="box-sizing: border-box;">In Windows 7 and below, you can use it directly to make the window at the top level. But starting with Windows 8, Microsoft has introduced other Windows Bands, and their order from lowest to highest is as follows:</font>`SetWindowPos(HWND_TOPMOST)`

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

<clipboard-copy aria-label="Copy" class="ClipboardButton btn btn-invisible js-clipboard-copy m-2 p-0 d-flex flex-justify-center flex-items-center" data-copy-feedback="Copied!" data-tooltip-direction="w" value="ZBID_DESKTOP
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
ZBID_UIACCESS" tabindex="0" role="button" style="box-sizing: border-box; position: relative; display: flex !important; padding: 0px !important; font-size: 14px; font-weight: var(--base-text-weight-medium, 500); line-height: 20px; white-space: nowrap; vertical-align: middle; cursor: pointer; user-select: none; border: 0px; border-radius: 6px; appearance: none; color: var(--fgColor-accent, var(--color-accent-fg)); background-color: transparent; box-shadow: none; transition: color 80ms cubic-bezier(0.33, 1, 0.68, 1), background-color, box-shadow, border-color; justify-content: center !important; align-items: center !important; margin: var(--base-size-8, 8px) !important; width: var(--control-small-size, 28px); height: var(--control-small-size, 28px);"><svg aria-hidden="true" height="16" viewbox="0 0 16 16" version="1.1" width="16" data-view-component="true" class="octicon octicon-copy js-clipboard-copy-icon"><path d="M0 6.75C0 5.784.784 5 1.75 5h1.5a.75.75 0 0 1 0 1.5h-1.5a.25.25 0 0 0-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 0 0 .25-.25v-1.5a.75.75 0 0 1 1.5 0v1.5A1.75 1.75 0 0 1 9.25 16h-7.5A1.75 1.75 0 0 1 0 14.25Z"></path><path d="M5 1.75C5 .784 5.784 0 6.75 0h7.5C15.216 0 16 .784 16 1.75v7.5A1.75 1.75 0 0 1 14.25 11h-7.5A1.75 1.75 0 0 1 5 9.25Zm1.75-.25a.25.25 0 0 0-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 0 0 .25-.25v-7.5a.25.25 0 0 0-.25-.25Z"></path></svg></clipboard-copy>

<font _mstmutation="1" _msttexthash="16053401" _msthash="286" style="box-sizing: border-box;">The default window segment is that this results in the Z-order of the window always being lower than that of the window that has been set to other higher-level segments anyway.</font>`ZBID_DESKTOP``SetWindowPos`

So why not set up other window segments?

There are the following APIs in Windows that can be used to change the window segment of a program:

```c
HWND WINAPI CreateWindowInBand(DWORD dwExStyle,
  	LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam,DWORD dwBand
);
HWND WINAPI CreateWindowInBandEx(DWORD dwExStyle,
  	LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam,DWORD dwBand,DWORD dwTypeFlags
);
BOOL WINAPI SetWindowBand(HWND hWnd, HWND hwndInsertAfter, DWORD dwBand
);
```

<clipboard-copy aria-label="Copy" class="ClipboardButton btn btn-invisible js-clipboard-copy m-2 p-0 d-flex flex-justify-center flex-items-center" data-copy-feedback="Copied!" data-tooltip-direction="w" value="HWND WINAPI CreateWindowInBand(DWORD dwExStyle,
  	LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam,DWORD dwBand
);
HWND WINAPI CreateWindowInBandEx(DWORD dwExStyle,
  	LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam,DWORD dwBand,DWORD dwTypeFlags
);
BOOL WINAPI SetWindowBand(HWND hWnd, HWND hwndInsertAfter, DWORD dwBand
);" tabindex="0" role="button" style="box-sizing: border-box; position: relative; display: flex !important; padding: 0px !important; font-size: 14px; font-weight: var(--base-text-weight-medium, 500); line-height: 20px; white-space: nowrap; vertical-align: middle; cursor: pointer; user-select: none; border: 0px; border-radius: 6px; appearance: none; color: var(--fgColor-accent, var(--color-accent-fg)); background-color: transparent; box-shadow: none; transition: color 80ms cubic-bezier(0.33, 1, 0.68, 1), background-color, box-shadow, border-color; justify-content: center !important; align-items: center !important; margin: var(--base-size-8, 8px) !important; width: var(--control-small-size, 28px); height: var(--control-small-size, 28px);"><svg aria-hidden="true" height="16" viewbox="0 0 16 16" version="1.1" width="16" data-view-component="true" class="octicon octicon-copy js-clipboard-copy-icon"><path d="M0 6.75C0 5.784.784 5 1.75 5h1.5a.75.75 0 0 1 0 1.5h-1.5a.25.25 0 0 0-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 0 0 .25-.25v-1.5a.75.75 0 0 1 1.5 0v1.5A1.75 1.75 0 0 1 9.25 16h-7.5A1.75 1.75 0 0 1 0 14.25Z"></path><path d="M5 1.75C5 .784 5.784 0 6.75 0h7.5C15.216 0 16 .784 16 1.75v7.5A1.75 1.75 0 0 1 14.25 11h-7.5A1.75 1.75 0 0 1 5 9.25Zm1.75-.25a.25.25 0 0 0-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 0 0 .25-.25v-7.5a.25.25 0 0 0-.25-.25Z"></path></svg></clipboard-copy>

<font _mstmutation="1" _msttexthash="199103086" _msthash="289" style="box-sizing: border-box;">However, the programs that are called must be digitally signed with Microsoft's certificates, which means that only programs built into Windows can use these APIs, which is exactly what Task Manager does. Instead, you need to call the private API:, which has a handle-like key, which can only be obtained by getting it. The condition for the success of the call is that the calling thread must be the current desktop thread (i.e., the calling thread), and it can only be obtained once, otherwise the function will be, and you can't even inject to get the key, because it has already been called once. In other words, only desktop managers can use it.</font>`CreateWindowInBand(Ex)``SetWindowBand``NtUserEnableIAMAccess``NtUserAcquireIAMKey``NtUserAcquireIAMKey``SetShellWindows(Ex)``ERROR_ACCESS_DENIED``explorer.exe``explorer.exe``NtUserAcquireIAMKey``SetWindowBand`

<font _mstmutation="1" _msttexthash="35132019" _msthash="290" style="box-sizing: border-box;">Is there any other way? Notice the on-screen keyboard() and VS a tool window that can also be set to a higher window than the Task Manager. Reverse work and it turns out that they are nothing more than that, and it turns out that there is one item in the list of programs:</font>`osk.exe``Inspect.exe``SetWindowPos(HWND_TOPMOST)`

```
<requestedExecutionLevel level="asInvoker" uiAccess="true"/>
```

<clipboard-copy aria-label="Copy" class="ClipboardButton btn btn-invisible js-clipboard-copy m-2 p-0 d-flex flex-justify-center flex-items-center" data-copy-feedback="Copied!" data-tooltip-direction="w" value="<requestedExecutionLevel level=&quot;asInvoker&quot; uiAccess=&quot;true&quot;/>" tabindex="0" role="button" style="box-sizing: border-box; position: relative; display: flex !important; padding: 0px !important; font-size: 14px; font-weight: var(--base-text-weight-medium, 500); line-height: 20px; white-space: nowrap; vertical-align: middle; cursor: pointer; user-select: none; border: 0px; border-radius: 6px; appearance: none; color: var(--fgColor-accent, var(--color-accent-fg)); background-color: transparent; box-shadow: none; transition: color 80ms cubic-bezier(0.33, 1, 0.68, 1), background-color, box-shadow, border-color; justify-content: center !important; align-items: center !important; margin: var(--base-size-8, 8px) !important; width: var(--control-small-size, 28px); height: var(--control-small-size, 28px);"><svg aria-hidden="true" height="16" viewbox="0 0 16 16" version="1.1" width="16" data-view-component="true" class="octicon octicon-copy js-clipboard-copy-icon"><path d="M0 6.75C0 5.784.784 5 1.75 5h1.5a.75.75 0 0 1 0 1.5h-1.5a.25.25 0 0 0-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 0 0 .25-.25v-1.5a.75.75 0 0 1 1.5 0v1.5A1.75 1.75 0 0 1 9.25 16h-7.5A1.75 1.75 0 0 1 0 14.25Z"></path><path d="M5 1.75C5 .784 5.784 0 6.75 0h7.5C15.216 0 16 .784 16 1.75v7.5A1.75 1.75 0 0 1 14.25 11h-7.5A1.75 1.75 0 0 1 5 9.25Zm1.75-.25a.25.25 0 0 0-.25.25v7.5c0 .138.112.25.25.25h7.5a.25.25 0 0 0 .25-.25v-7.5a.25.25 0 0 0-.25-.25Z"></path></svg></clipboard-copy>

[MSDN](https://learn.microsoft.com/en-us/windows/security/threat-protection/security-policy-settings/user-account-control-allow-uiaccess-applications-to-prompt-for-elevation-without-using-the-secure-desktop) explains that this UIAccess permission is used to support accessibility services, allowing it to access the window of the elevated process under the non-elevated process. For security reasons, if you want to enable it, you must meet:

- The application must have a digital signature that can be verified with a digital certificate associated with the trusted root certification authority store on the local computer.
- <font _mstmutation="1" _msttexthash="11725493" _msthash="293" style="box-sizing: border-box;">The application must be installed in a local folder, such as a directory, that can only be written by an administrator. Allowed directories include:<span> </span></font>`Program Files`
    - `%ProgramFiles%`<font _mstmutation="1" _msttexthash="463307" _msthash="294" style="box-sizing: border-box;">and its subdirectories</font>
    - `%WinDir%`<font _mstmutation="1" _msttexthash="6042465" _msthash="295" style="box-sizing: border-box;">and its subdirectories, except for a few subdirectories where standard users have write permissions.</font>

<font _mstmutation="1" _msttexthash="20344454" _msthash="296" style="box-sizing: border-box;">This property is present in the process token, which means that we can bypass the digital signature and the specified installation path by setting this permission after the privilege escalation.</font>`TokenUIAccess``SetTokenInformation`

<font _mstmutation="1" _msttexthash="95879342" _msthash="297" style="box-sizing: border-box;">But after some testing, I finally found out that in order to do this, I had to have permissions, so one solution was to "steal" a token from other system processes so that I could get permissions. However, UIAccess is ineffective in modifying a running program, so you end up having to start a new process. Although this is a bit flawed, it is still better than the previous injection fault tolerance and more practical than digital signatures.</font>`SeTcbPrivilege``explorer.exe`

## reference
[<svg class="octicon octicon-link" viewbox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z"></path></svg>](https://github.com/killtimer0/uiaccess#%E5%8F%82%E8%80%83)

[Window z-order in Windows 10 – ADeltaX Blog](https://blog.adeltax.com/window-z-order-in-windows-10/), Chinese version: [Form Z-order in Windows 10](https://blog.csdn.net/weixin_43820461/article/details/107610331)
