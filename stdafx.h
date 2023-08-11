#define _CRT_SECURE_NO_WARNINGS
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
#include "D3XD/d3dx9.h"

#pragma comment(lib, "Psapi.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "ntdll.lib")

using namespace std;



#include "crypt.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"
#include "vector.h"

#include "settings.h"
#include "ZeroGui.h"
#include "WindowHijacking.h"


#include "Overlay.h"
#include "offsets.h"
#include "Design.h"
#include "main.h"
#include "Framework.h"


