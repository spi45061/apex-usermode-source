#pragma once


void draw_rectangle(float x, float y, float x2, float y2, ImColor color, float thickness) {
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + x2, y + y2), color, 0, -1, thickness);
	return;
}

void draw_text_outline(float x, float y, ImColor color, const char* string, ...) {
	char buf[512];
	va_list arg_list;

	ZeroMemory(buf, sizeof(buf));

	va_start(arg_list, string);
	vsnprintf(buf, sizeof(buf), string, arg_list);
	va_end(arg_list);

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x - 1, y), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x + 1, y), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y - 1), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y + 1), ImColor(0.0f, 0.0f, 0.0f, 1.0f), buf, 0, 0, 0);

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y), color, buf, 0, 0, 0);
	return;
}




namespace Settings {
	static bool Aimbot = 1;
	static float AimbotFOV = 150.0f;
	static float AimbotSmooth = 1.0f;
	static float triggerbot_distance = 20.f;


	static bool PlayerBox = 0;
	static bool Box3d = 0;
	static bool Cornerbox = 0;
	bool filledfov = false;
	
	static bool rsc = 0;

	static bool healthtext = 0;
	static bool BoundedBox = 1;
	static bool Skeleton = 0;
	static bool Snaplines = 0;
	static bool snap_from_cross = 0;
	static bool PlayerName = 1;
	static bool PlayerHealth = 0;
	static bool AimLine = 0;
	static bool Glow = 0;
	static bool DebugBones = 0;

	static bool SkydiveSpeed = 0;
	static bool backtrack = 0;
	static bool triange_box = 0;

	static bool Crosshair = 1;
	static bool ShowFov = 1;
	static bool TeamCheck = 1;
	static bool hitbox_selection;
	static bool head = false;
	static bool neck = true;
	static bool chest = false;
	static bool hips = false;
	static int crosshair_cricle_radius = 5;
	static int crosshair_line_length = 10;

	static bool triggerbot;
	static float trigger_time;

	Vector3 hitbox;
	int boney = 0;
	const char* aimBones[5] = { "Head", "Neck", "Chest", "Hip", "Feet" };
	char configname = *_("commcord");

	bool loot;
	bool lootbox;
	bool lootdistance;

	static float ESP[] = {255, 255, 255, 255};
	static int ESP_snap[] = { 255, 255, 255, 255 };
	static int Visible[] = { 0, 255, 0, 255 };
	static int Invisible[] = { 255, 255, 255, 255 };


}

namespace Addresses {
	uintptr_t LocalPlayer;
	uintptr_t EntityList;
	uintptr_t ViewRenderer;
	uintptr_t ViewMatrix;
	uintptr_t NameList;

	static int Width = 1920;
	static int Height = 1080;
}