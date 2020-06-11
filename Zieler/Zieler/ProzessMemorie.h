#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class MemorieManager{
private:
	// für Prozesshandling
	DWORD dwProzID; //ProzessID
	HANDLE hProz;	//Prozesshandle

public:
	// speichern der dll's der exe
	MODULEENTRY32 ClientDll;
	MODULEENTRY32 EngineDll;
	// function für Prozess
	DWORD ClientDLL_Base, ClientDLL_Size;
	DWORD EngineDLL_Base, EngineDLL_Size;

	// kleine Funktionen
	DWORD GetProzID() { return dwProzID; }
	HANDLE GetProzHandle() { return hProz; }

	// construktor
	MemorieManager() {
		this->hProz = NULL;
		this->dwProzID = NULL;
		try {
			// prozess hooken
			if (!ProzessAnhaengen("csgo.exe")) throw 1;
			// dlls holen
			this->ClientDll = GetModule("client_panorama.dll");
			this->EngineDll = GetModule("engine.dll");
			this->ClientDLL_Base = (DWORD)this->ClientDll.modBaseAddr;
			this->EngineDLL_Base = (DWORD)this->EngineDll.modBaseAddr;
			// haben wir die dlls?
			if (this->ClientDLL_Base == 0x0) throw 2;
			if (this->EngineDLL_Base == 0x0) throw 3;
			// groesse bestimmen
			this->ClientDLL_Size = ClientDll.dwSize;
			this->EngineDLL_Size = EngineDll.dwSize;
		}
		catch (int iEx) {
			switch (iEx)
			{
			case 1: MessageBoxA(NULL, "CS:GO must be running", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
			case 2: MessageBoxA(NULL, "Couldn't find Client.dll", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
			case 3: MessageBoxA(NULL, "Couldn't find Engine.dll", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
			default: throw;
			}
		}
		catch (...) {
			MessageBoxA(NULL, "Unhandled exception thrown", "ERROR", MB_ICONSTOP | MB_OK);
			exit(0);
		}
	}

	// dekonstruktor
	~MemorieManager() {
		// prozess schliessen
		CloseHandle(this->hProz);
	}


	bool ProzessAnhaengen(char * ProzessName) {
		// ein Handle welcher eine exakte kopie eines Prozesses generiert
		// TH32CS_SNAPMODULE32 -> kompletter 32 bit Prozesss
		// NULL -> ProzessID des Prozesses zu kopieren
		HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		// Prozesseintrag 32 bit
		PROCESSENTRY32 prozessEintrag;
		prozessEintrag.dwSize = sizeof(prozessEintrag);
		
		// WCHAR -> 1x 16bit Unicode Zeichen
		const WCHAR* prozessNameChar;
		const WCHAR* prozessName;

		// Windows documentation:
		// Maps a character string to a UTF-16 (wide character) string.
		// The character string is not necessarily from a multibyte character set.
		int nChars = MultiByteToWideChar(CP_ACP, 0, ProzessName, -1, NULL, 0);
		prozessNameChar = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, ProzessName, -1, (LPWSTR)prozessNameChar, nChars);
		
		do {
			// Wenn der Prozessname mit dem gesuchten Prozessnamen
			// syntax error auch in vorlage
			if (!wcscmp(prozessEintrag.szExeFile, prozessNameChar)){
				// die Private variabel der ProzessID speichern
				this->dwProzID = prozessEintrag.th32ProcessID;
				// Handel schliessen, da die infos vorhanden sind
				CloseHandle(hPID);
				// Prozess als Handel nehmen
				this->hProz = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dwProzID);
				// aus der funktion mit erfolg
				return true;
			}
		} while (Process32Next(hPID, &prozessEintrag));
		// den handel schliessen bevor fehler
		CloseHandle(hPID);
		// Fail
		return false;
	}

	//Moduleintrag
	MODULEENTRY32 GetModule(char* ModuleName)
	{
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProzID);
		MODULEENTRY32 mEntry;
		mEntry.dwSize = sizeof(mEntry);

		const WCHAR *modNameChar;
		int nChars = MultiByteToWideChar(CP_ACP, 0, ModuleName, -1, NULL, 0);
		modNameChar = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, ModuleName, -1, (LPWSTR)modNameChar, nChars);

		do
			if (!wcscmp(mEntry.szModule, modNameChar))
			{
				CloseHandle(hModule);
				return mEntry;
			}
		while (Module32Next(hModule, &mEntry));

		CloseHandle(hModule);
		mEntry.modBaseAddr = 0x0;
		return mEntry;
	}

	// read function mit Template
	// so sind wir nich gebunden an datentyp
	template <class c>
	c Read(DWORD dwAddresse) {
		c val;
		ReadProcessMemory(hProz, (LPVOID)dwAddresse, &val,  sizeof(c), NULL);
		return val;
	}

	template<class c>
	BOOL Write(DWORD dwAddresse, c valueToWrite) {
		return WriteProcessMemory(hProz, (LPVOID)dwAddresse, &valueToWrite, sizeof(c), NULL);

	}

};