#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <random>
#include <Uxtheme.h>
#include <dwmapi.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <thread>
#include "crypt.h"
#include "xstring.h"

float newXorStrcrosshairx = 1;
float newXorStrcrosshairy = 1;
float newXorStrcrosshairt = 1;
float newXorStraimfov = 1;
float newXorStraimsmooth = 1;
float newXorStraimdistance = 1;
int r = 1;
int g = 1;
int b = 1;
float rcs;
bool FileExists(const std::string& fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}
void WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}


std::string ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), XorStr("NULL").c_str(), buf, 100, file.c_str());
	return (std::string)buf;
}
std::string ReadStringFromIniXorStrFloat(std::string file, std::string app, std::string key, int floatXorStrcode)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), XorStr("NULL").c_str(), buf, 100, file.c_str());

	if (floatXorStrcode == 0)
	{
		system(XorStr("cls").c_str());
		std::cout << XorStr("\n loading error");
		Sleep(5000);
		exit(0);
	}
	else if (floatXorStrcode == 1) //crosshairx
	{
		newXorStrcrosshairx = std::stof(buf);
	}
	else if (floatXorStrcode == 2) //crosshairy
	{
		newXorStrcrosshairy = std::stof(buf);
	}
	else if (floatXorStrcode == 3) //crosshairthinkness
	{
		newXorStrcrosshairt = std::stof(buf);
	}
	else if (floatXorStrcode == 4) //aimfov
	{
		newXorStraimfov = std::stof(buf);
	}
	else if (floatXorStrcode == 5) //aimsmooth
	{
		newXorStraimsmooth = std::stof(buf);
	}
	else if (floatXorStrcode == 6) //aimdistance
	{
		newXorStraimdistance = std::stof(buf);
	}
	else if (floatXorStrcode == 7) //aimdistance
	{
		r = std::stof(buf);
	}
	else if (floatXorStrcode == 8) //aimdistance
	{
		g = std::stof(buf);
	}
	else if (floatXorStrcode == 9) //aimdistance
	{
		b = std::stof(buf);
	}
	else if (floatXorStrcode == 10) //aimdistance
	{
		rcs = std::stof(buf);
	}
}

void SaveConfig()
{
	if (!FileExists(XorStr("C:/config.ini")))
	{
		URLDownloadToFile(0, "https://cdn.discordapp.com/attachments/851828425835937863/863803941272027196/config.ini", "C:/config.ini", 0, 0);
		Sleep(500);
		//std::ofstream file{ _("C:\\Vanta\\config.ini").c_str() };
	}
	//Aimbot
	if (Settings::Aimbot)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("aimbot").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("aimbot").c_str());

	//Draw FOV
	if (Settings::ShowFov)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("drawfov").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("drawfov").c_str());

	//Snaplines
	if (Settings::Snaplines)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("snaplines").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("snaplines").c_str());

	//Distance
	if (Settings::AimLine)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("aimline").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("aimline").c_str());

	//Boxes
	if (Settings::BoundedBox)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("boxes").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("boxes").c_str());

	//filledboxes
	if (Settings::Cornerbox)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("cornerboxes").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("cornerboxes").c_str());

	if (Settings::triange_box)
		WriteStringToIni(XorStr("1"), XorStr("C:/config.ini"), XorStr("options"), XorStr("triangel").c_str());
	else
		WriteStringToIni(XorStr("0"), XorStr("C:/config.ini"), XorStr("options"), XorStr("triangel").c_str());

	if (Settings::PlayerHealth)
		WriteStringToIni(XorStr("1"), XorStr("C:/config.ini"), XorStr("options"), XorStr("health").c_str());
	else
		WriteStringToIni(XorStr("0"), XorStr("C:/config.ini"), XorStr("options"), XorStr("health").c_str());

	if (Settings::snap_from_cross)
		WriteStringToIni(XorStr("1"), XorStr("C:/config.ini"), XorStr("options"), XorStr("crossnap").c_str());
	else
		WriteStringToIni(XorStr("0"), XorStr("C:/config.ini"), XorStr("options"), XorStr("crossnap").c_str());

	//Crosshair
	if (Settings::Crosshair)
		WriteStringToIni(XorStr("1"),XorStr("C:/config.ini"), XorStr("options"), XorStr("crosshair").c_str());
	else
		WriteStringToIni(XorStr("0"),XorStr("C:/config.ini"), XorStr("options"), XorStr("crosshair").c_str());

	//AimFOV
	WriteStringToIni(std::to_string(Settings::AimbotFOV),XorStr("C:/config.ini"), XorStr("options"), XorStr("aimfov").c_str());

	//Smooth
	WriteStringToIni(std::to_string(Settings::AimbotSmooth),XorStr("C:/config.ini"), XorStr("options"), XorStr("smooth").c_str());

	//CrosshairX
	WriteStringToIni(std::to_string(Settings::crosshair_line_length),XorStr("C:/config.ini"), XorStr("options"), XorStr("crosshairy").c_str());

	//CrosshairThickness
	WriteStringToIni(std::to_string(Settings::crosshair_cricle_radius),XorStr("C:/config.ini"), XorStr("options"), XorStr("crosshaircircle").c_str());

	WriteStringToIni(std::to_string(Settings::Invisible[0]), XorStr("C:/config.ini"), XorStr("options"), XorStr("R").c_str());
	WriteStringToIni(std::to_string(Settings::Invisible[1]), XorStr("C:/config.ini"), XorStr("options"), XorStr("G").c_str());
	WriteStringToIni(std::to_string(Settings::Invisible[2]), XorStr("C:/config.ini"), XorStr("options"), XorStr("B").c_str());
	WriteStringToIni(std::to_string(Settings::rsc), XorStr("C:/config.ini"), XorStr("options"), XorStr("rcs").c_str());
}

//Load config
void LoadConfig()
{

	//Aimbot
	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("aimbot").c_str()) == XorStr("1").c_str())
		Settings::Aimbot = true;
	else
		Settings::Aimbot = false;

	//Draw FOV
	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("drawfov").c_str()) == XorStr("1").c_str())
		Settings::ShowFov = true;
	else
		Settings::ShowFov = false;

	//Snaplines
	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("snaplines").c_str()) == XorStr("1").c_str())
		Settings::Snaplines = true;
	else
		Settings::Snaplines = false;

	//Distance
	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("aimline").c_str()) == XorStr("1").c_str())
		Settings::AimLine = true;
	else
		Settings::AimLine = false;

	//Boxes
	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("boxes").c_str()) == XorStr("1").c_str())
		Settings::BoundedBox = true;
	else
		Settings::BoundedBox = false;

	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("cornerboxes").c_str()) == XorStr("1").c_str())
		Settings::Cornerbox = true;
	else
		Settings::Cornerbox = false;

	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("triangel").c_str()) == XorStr("1").c_str())
		Settings::triange_box = true;
	else
		Settings::triange_box = false;

	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("health").c_str()) == XorStr("1").c_str())
		Settings::PlayerHealth = true;
	else
		Settings::PlayerHealth = false;

	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("crossnap").c_str()) == XorStr("1").c_str())
		Settings::snap_from_cross = true;
	else
		Settings::snap_from_cross = false;

	//Crosshair
	if (ReadStringFromIni(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("crosshair").c_str()) == XorStr("1").c_str())
		Settings::Crosshair = true;
	else
		Settings::Crosshair = false;

	//CrosshairX

	//CrosshairY
	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("crosshairy").c_str(), 2);
	Settings::crosshair_line_length = newXorStrcrosshairy;

	//CrosshairThickness
	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("crosshaircircle").c_str(), 3);
	Settings::crosshair_cricle_radius = newXorStrcrosshairt;

	//AimFOV
	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("aimfov").c_str(), 4);
	Settings::AimbotFOV = newXorStraimfov;

	//AimSmooth
	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("smooth").c_str(), 5);
	Settings::AimbotSmooth = newXorStraimsmooth;

	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("R").c_str(), 7);
	Settings::Invisible[0] = r;

	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("G").c_str(), 8);
	Settings::Invisible[1] = g;

	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("B").c_str(), 9);
	Settings::Invisible[2] = b;

	ReadStringFromIniXorStrFloat(XorStr("C:/config.ini").c_str(), XorStr("options").c_str(), XorStr("rcs").c_str(), 10);
	Settings::rsc = rcs;

	
}
