
#include <iostream>
#include <Windows.h>
void deleteKeyIfExists() {
	// Checks if appropriate registry key exists, if it exists it is deleted.
	HKEY hkExists;
	long lKeyOpen = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hkExists);
	LONG lKeyExists = RegQueryValueExA(hkExists, "FixWindowsTimer", NULL, NULL, NULL, NULL);
	if (lKeyExists == ERROR_SUCCESS)
	{
		HKEY hk = HKEY_CURRENT_USER;
		RegOpenKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hk);
		RegDeleteValue(hk, L"FixWindowsTimer");
		RegCloseKey(hk);
	}
} 
int main()
{
	deleteKeyIfExists();
}

