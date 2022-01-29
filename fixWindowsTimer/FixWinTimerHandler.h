#pragma once
#include <Windows.h>
#include <limits.h>
#include <winnt.h>
#include <ntstatus.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <iostream>
#include <fstream>

typedef NTSTATUS(NTAPI* pSetTimerResolution)(ULONG RequestedResolution, BOOLEAN Set, PULONG ActualResolution);
class FixWinTimerHandler {

	
public:
	
	FixWinTimerHandler() {

		mainFunc();
		
	}

	int mainFunc()
	{
		wchar_t filePath[4160];
		HMODULE hModule = GetModuleHandle(NULL);
		if (hModule)
		{
			GetModuleFileNameW(hModule, filePath, (sizeof(filePath)));
		}
		// loads the needed windows lib
		const HINSTANCE hLibrary = LoadLibrary(L"NTDLL.dll");
		if (hLibrary)
		{
			pSetTimerResolution setFunction{};
			setFunction = (pSetTimerResolution)GetProcAddress(hLibrary, "NtSetTimerResolution");
			ULONG res{};
			// sets the timer to 1ms
			setFunction(10000, TRUE, &res);

			
		}
		else {
			// user doesn't have NTDLL.dll on his PC which means he's likely not on Windows
			printConsoleError();
			
		}
		HKEY hkExists;
		long lKeyOpen = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_READ,&hkExists);
		LONG lKeyExists = RegQueryValueExA(hkExists, "FixWindowsTimer", NULL, NULL, NULL, NULL);
		// If the registry key doesn't already exist ( the app is not installed in startup ) we install it
		if (lKeyExists != ERROR_SUCCESS)
		{
			writeKeyToRegistry(filePath);
		}
	}


	void printConsoleError() {
		AllocConsole();
		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
		std::cout << "NTDLL.DLL Could not be loaded" << std::endl;
		std::cout << "Exiting in 5 seconds...";
		Sleep(5000);
		exit(1);
	}
	void writeKeyToRegistry(wchar_t* filePath) {
		HKEY hk;
		LONG cStatus = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hk);
		if (cStatus == ERROR_SUCCESS)
		{
			long sStatus = RegSetValueEx(hk, L"FixWindowsTimer", 0, REG_SZ, (BYTE*)filePath, MAX_PATH);
			RegCloseKey(hk);
		}
	}
};
