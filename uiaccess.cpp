#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <tchar.h>

//uiaccess https://github.com/killtimer0/uiaccess
DWORD DuplicateWinloginToken(DWORD dwSessionId, DWORD dwDesiredAccess, PHANDLE phToken) {
	DWORD dwErr;
	PRIVILEGE_SET ps;
	ps.PrivilegeCount = 1;
	ps.Control = PRIVILEGE_SET_ALL_NECESSARY;

	if (!LookupPrivilegeValue(NULL, SE_TCB_NAME, &ps.Privilege[0].Luid))
		return GetLastError();

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return GetLastError();

	BOOL bCont, bFound = FALSE;
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	dwErr = ERROR_NOT_FOUND;

	for (bCont = Process32First(hSnapshot, &pe); bCont; bCont = Process32Next(hSnapshot, &pe)) { //loop system processes
		HANDLE hProcess;
		if (0 != _tcsicmp(pe.szExeFile, TEXT("winlogon.exe"))) //if not our target, continue.
			continue;

		hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ProcessID);
		if (!hProcess)
			continue;

		HANDLE hToken;
		DWORD dwRetLen, sid;
		if (OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE, &hToken)) {
			BOOL fTcb;
			if (PrivilegeCheck(hToken, &ps, &fTcb) && fTcb) {
				if (GetTokenInformation(hToken, TokenSessionId, &sid, sizeof(sid), &dwRetLen) && sid == dwSessionId) {
					bFound = TRUE;
					if (DuplicateTokenEx(hToken, dwDesiredAccess, NULL, SecurityImpersonation, TokenImpersonation, phToken)) {
						dwErr = ERROR_SUCCESS;
					} else {
						dwErr = GetLastError();
					}
				}
			}
			CloseHandle(hToken);
		}
		CloseHandle(hProcess);
		if (bFound) { break; } //MessageBoxA(NULL, "winlogon.exe system token found.", "Debug Window", MB_ICONINFORMATION | MB_OK);
	}

	CloseHandle(hSnapshot);
	return dwErr;
}

DWORD CreateUIAccessToken(PHANDLE phToken) {
	DWORD dwSessionId, dwRetLen, dwErr;
	HANDLE hTokenSelf, hTokenSystem;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE, &hTokenSelf))
		return GetLastError();

	if (!GetTokenInformation(hTokenSelf, TokenSessionId, &dwSessionId, sizeof(dwSessionId), &dwRetLen))
		return GetLastError();

	dwErr = DuplicateWinloginToken(dwSessionId, TOKEN_IMPERSONATE, &hTokenSystem);
	if (ERROR_SUCCESS != dwErr)
		return ERROR_NOT_FOUND;

	if (SetThreadToken(NULL, hTokenSystem)) {
		if (DuplicateTokenEx(hTokenSelf, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT, NULL, SecurityAnonymous, TokenPrimary, phToken)) {
			BOOL bUIAccess = TRUE;
			if (!SetTokenInformation(*phToken, TokenUIAccess, &bUIAccess, sizeof(bUIAccess))) {
				dwErr = GetLastError();
				CloseHandle(*phToken);
			} //else { MessageBoxA(NULL, "Ui Accesss Token Duplicated.", "Debug Window", MB_ICONINFORMATION | MB_OK); }
		} else {
			dwErr = GetLastError();
		}
		RevertToSelf();
	} else {
		dwErr = GetLastError();
	}
	CloseHandle(hTokenSystem);
	CloseHandle(hTokenSelf);
	return dwErr;
}

DWORD PrepareForUIAccess() {
	DWORD dwErr, dwUIAccess;
	HANDLE hTokenUIAccess, hToken;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		DWORD dwRetLen;
		if (GetTokenInformation(hToken, TokenUIAccess, &dwUIAccess, sizeof(dwUIAccess), &dwRetLen)) {
			if (dwUIAccess) { 
				//redirect program flow after process has been respawned with duplicated UI Access token
				//MessageBoxA(NULL, "New Process Instance Spawned with Ui Access", "Debug Window", MB_ICONINFORMATION | MB_OK); 
				return ERROR_SUCCESS; 
			}
		} else { 
			return GetLastError(); 
		}
		CloseHandle(hToken);
	} else {
		return GetLastError();
	}

	dwErr = CreateUIAccessToken(&hTokenUIAccess);
	if (dwErr != ERROR_SUCCESS)
		return GetLastError();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	GetStartupInfo(&si);
	if (CreateProcessAsUser(hTokenUIAccess, NULL, GetCommandLine(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		CloseHandle(pi.hProcess), CloseHandle(pi.hThread);
		ExitProcess(0);
	} else {
		return GetLastError();
	}

	CloseHandle(hTokenUIAccess);
	return dwErr;
}

typedef BOOL(WINAPI* GetWindowBand)(HWND hWnd, PDWORD pdwBand);
typedef HWND(WINAPI* CreateWindowInBand)(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam, DWORD band);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hWnd, message, wParam, lParam); }

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	GetWindowBand pGetWindowBand = (GetWindowBand)GetProcAddress(LoadLibraryA("user32.dll"), "GetWindowBand");
	CreateWindowInBand pCreateWindowInBand = (CreateWindowInBand)GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowInBand");
	try {
		DWORD dwErr = PrepareForUIAccess();
		if (ERROR_SUCCESS != dwErr)
			throw 1;

		WNDCLASS wc = { }; wc.lpfnWndProc = WndProc; wc.hInstance = hInstance; wc.lpszClassName = L"uiaccess Overlay";  ATOM res = RegisterClass(&wc);
		HWND OverlayWindow = pCreateWindowInBand(WS_EX_TOPMOST | WS_EX_NOACTIVATE, wc.lpszClassName, L"uiaccess Overlay", WS_OVERLAPPEDWINDOW, 10, 10, 1200, 800, NULL, NULL, wc.hInstance, NULL, 0x02);
		SetWindowPos(NULL, HWND_TOPMOST, 100, 100, 1280, 800, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		ShowWindow(OverlayWindow, SW_NORMAL);
		UpdateWindow(OverlayWindow);

		DWORD bandCheck;
		if (pGetWindowBand(OverlayWindow, &bandCheck)) {
			std::string out = "Windows Z-Band Level: " + std::to_string(bandCheck);
			MessageBoxA(NULL, out.c_str(), "Debug Window", MB_ICONINFORMATION | MB_OK);
		} else {
			std::string out = "Failed validating GetWindowBand: " + std::to_string(GetLastError());
			MessageBoxA(NULL, out.c_str(), "Debug Window", MB_ICONSTOP | MB_OK);
		}
	} catch (...) {
		MessageBoxA(NULL, "Failed Preparing for UI Access", "Debug Window", MB_ICONSTOP | MB_OK);
	}
	return 1;
}