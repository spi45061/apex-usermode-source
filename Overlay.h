#pragma once
RECT GameRect;
MARGINS Margin = { -1 };
RECT rc2;
ID3D11Device* g_pd3dDevice;
ID3D11DeviceContext* g_pd3dDeviceContext;
IDXGISwapChain* g_pSwapChain;
ID3D11RenderTargetView* g_mainRenderTargetView;
HWND GameWnd;
HWND MyWnd;
WNDCLASSEX wClass;
MSG Message = { NULL };
#include "comms.h"

extern void render();

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
auto CreateRenderTarget()->VOID
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}
auto CleanupRenderTarget()->VOID
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}
auto CleanupDeviceD3D()->VOID
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

HRESULT DirectXInit(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapChainDesc.Windowed = TRUE;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Height = 0;
	SwapChainDesc.BufferDesc.Width = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = MyWnd;
	SwapChainDesc.SampleDesc.Count = 8;
	SwapChainDesc.SampleDesc.Quality = 0;

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &SwapChainDesc, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return false;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::GetIO().Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\Tahoma.ttf"), 16.0f);
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);

	ImGui_ImplWin32_Init(MyWnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	pBackBuffer->Release();

	SetWindowPos(MyWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}
auto SetupWindow()->BOOL
{
	while (!MyWnd) {
		MyWnd = SetUp::HiJackNotepadWindow();
		Sleep(100);
	}

	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(MyWnd, &margin);
	SetMenu(MyWnd, NULL);
	SetWindowLongPtr(MyWnd, GWL_STYLE, WS_VISIBLE);
	SetWindowLongPtr(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);

	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);

	SetWindowLong(MyWnd, GWL_EXSTYLE, GetWindowLong(MyWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);

	return true;
}

auto PresentHook()->WPARAM
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		POINT p;
		POINT xy;
		GetCursorPos(&p);
		io.MousePos.x = p.x;
		io.MousePos.y = p.y;

		if (MouseController::NtUserGetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		render();

	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	DestroyWindow(MyWnd);

	return Message.wParam;
}
