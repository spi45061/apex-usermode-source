#pragma once
#include <io.h>
#include "comms.h"
#include "config.h"


static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
bool MenuIsOpen = true;
static int tab = 1;


bool aimbottt = false;
bool aimkey = false;
bool aimbotpredticiton = false;
bool noswap = false;
bool aimbotvischeck = false;
bool ignoredowned = false;
bool aimatfriendlies = false;
int prioritytype = 3;
bool drawcircle = false;
bool silentaim = false;
bool autoshoot = false;
int bone = 5;

bool ImGui::Checkbox(const char* label, bool* v)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	const float square_sz = GetFrameHeight();
	ImVec2 pos = window->DC.CursorPos;

	const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
	{
		*v = !(*v);
		MarkItemEdited(id);
	}


	const ImRect check_bb(pos, ImVec2(pos.x, pos.y) + ImVec2(square_sz * 1.5, square_sz * 0.8));
	RenderNavHighlight(total_bb, id);
	//window->DrawList->AddCircleFilled(check_bb.GetCenter(), 10, GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg));
	//window->DrawList->AddCircle(check_bb.GetCenter(), 11, GetColorU32(ImGuiCol_CheckMark),12,2.f);
	//RenderFrame(ImVec2(check_bb.Min.x, check_bb.Min.y) , ImVec2(check_bb.Max.x, check_bb.Max.y), GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), true, 4.f);
	//window->DrawList->AddRectFilled(check_bb.Min, check_bb.Max, GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg));

	auto col = GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);

	//Draw First Box
	ImVec2 UpperLeft(check_bb.GetTL().x, check_bb.GetTL().y + 2.f);
	ImVec2 LowerRight(check_bb.GetBR().x, check_bb.GetBR().y + 2.f);
	ImRect newRect(UpperLeft, LowerRight);
	window->DrawList->AddRectFilled(newRect.Min, newRect.Max, ImColor(52, 61, 70), 10);

	//Setup new rect for mid square + circle
	ImVec2 sUpperLeft(check_bb.GetTL().x, check_bb.GetTL().y + 2.f);
	ImVec2 sLowerRight(check_bb.GetCenter().x, check_bb.GetBR().y + 2.f);
	ImRect sRect(sUpperLeft, sLowerRight);
	window->DrawList->AddRectFilled(sRect.Min, sRect.Max, ImColor(255, 255, 255), 10);



	ImU32 check_col = GetColorU32(ImGuiCol_CheckMark);
	if (*v) {

		//reset canvas
		window->DrawList->AddRectFilled(ImVec2(newRect.Min.x - 1.f, newRect.Min.y - 1.f), ImVec2(newRect.Max.x + .5f, newRect.Max.y + 1.f), ImColor(58, 159, 191), 10);

		//create new rectangle for second half, third rect
		ImVec2 tUpperLeft(check_bb.GetCenter().x, check_bb.GetTL().y + 2.f);
		ImVec2 tLowerRight(check_bb.GetBR().x, check_bb.GetBR().y + 2.f);
		ImRect tRect(tUpperLeft, tLowerRight);
		window->DrawList->AddRectFilled(tRect.Min, tRect.Max, ImColor(255, 255, 255), 10);


	}
	//window->DrawList->AddCircleFilled(check_bb.GetCenter(), 7, check_col);

	if (label_size.x > 0.0f)
		RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
	return pressed;
}
bool ColorPicker(float* col, bool alphabar)
{
	const int EDGE_SIZE = 200; // = int(ImGui::GetWindowWidth() * 0.75f);
	const ImVec2 SV_PICKER_SIZE = ImVec2(EDGE_SIZE, EDGE_SIZE);
	const float SPACING = ImGui::GetStyle().ItemInnerSpacing.x;
	const float HUE_PICKER_WIDTH = 20.f;
	const float CROSSHAIR_SIZE = 7.0f;

	ImColor color(col[0], col[1], col[2]);
	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	float hue, saturation, value;
	ImGui::ColorConvertRGBtoHSV(color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

	ImColor colors[] = {
			ImColor(255, 0, 0),
			ImColor(255, 255, 0),
			ImColor(0, 255, 0),
			ImColor(0, 255, 255),
			ImColor(0, 0, 255),
			ImColor(255, 0, 255),
			ImColor(255, 0, 0)
	};

	for (int i = 0; i < 6; i++)
	{
		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH,
				picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
			colors[i],
			colors[i],
			colors[i + 1],
			colors[i + 1]
		);
	}

	draw_list->AddLine(
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING - 2, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + 2 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImColor(255, 255, 255)
	);

	if (alphabar)
	{
		float alpha = col[3];

		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + HUE_PICKER_WIDTH, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + 2 * HUE_PICKER_WIDTH, picker_pos.y + SV_PICKER_SIZE.y),
			ImColor(0, 0, 0), ImColor(0, 0, 0), ImColor(255, 255, 255), ImColor(255, 255, 255)
		);

		draw_list->AddLine(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING - 2) + HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING + 2) + 2 * HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
			ImColor(255.f - alpha, 255.f, 255.f)
		);
	}

	const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
	const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	ImVec4 cHueValue(1, 1, 1, 1);
	ImGui::ColorConvertHSVtoRGB(hue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
	ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

	draw_list->AddRectFilledMultiColor(
		ImVec2(picker_pos.x, picker_pos.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		c_oColorWhite,
		oHueColor,
		oHueColor,
		c_oColorWhite
	);

	draw_list->AddRectFilledMultiColor(
		ImVec2(picker_pos.x, picker_pos.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		c_oColorBlackTransparent,
		c_oColorBlackTransparent,
		c_oColorBlack,
		c_oColorBlack
	);

	float x = saturation * SV_PICKER_SIZE.x;
	float y = (1 - value) * SV_PICKER_SIZE.y;
	ImVec2 p(picker_pos.x + x, picker_pos.y + y);
	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.x < 0)
			mouse_pos_in_canvas.x = 0;
		else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1)
			mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

		if (mouse_pos_in_canvas.y < 0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
		saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
		value_changed = true;
	}

	// hue bar logic
	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING + SV_PICKER_SIZE.x, picker_pos.y));
	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.y < 0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
		value_changed = true;
	}

	if (alphabar)
	{
		ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING * 2 + HUE_PICKER_WIDTH + SV_PICKER_SIZE.x, picker_pos.y));
		ImGui::InvisibleButton("alpha_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

		if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
		{
			ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

			if (mouse_pos_in_canvas.y < 0)
				mouse_pos_in_canvas.y = 0;
			else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
				mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

			float alpha = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
			col[3] = alpha;
			value_changed = true;
		}
	}

	color = ImColor::HSV(hue >= 1 ? hue - 10 * 1e-6 : hue, saturation > 0 ? saturation : 10 * 1e-6, value > 0 ? value : 1e-6);
	col[0] = color.Value.x;
	col[1] = color.Value.y;
	col[2] = color.Value.z;

	bool widget_used;
	ImGui::PushItemWidth((alphabar ? SPACING + HUE_PICKER_WIDTH : 0) + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH - 2 * ImGui::GetStyle().FramePadding.x);
	widget_used = alphabar ? ImGui::ColorEdit4("", col) : ImGui::ColorEdit3("", col);
	ImGui::PopItemWidth();

	float new_hue, new_sat, new_val;
	ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], new_hue, new_sat, new_val);

	if (new_hue <= 0 && hue > 0)
	{
		if (new_val <= 0 && value != new_val)
		{
			color = ImColor::HSV(hue, saturation, new_val <= 0 ? value * 0.5f : new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
		else if (new_sat <= 0)
		{
			color = ImColor::HSV(hue, new_sat <= 0 ? saturation * 0.5f : new_sat, new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
	}

	return value_changed | widget_used;
}

auto menu()->VOID
{
	

	if (MenuIsOpen) {
		ImGuiIO& io = ImGui::GetIO();
		bool t;
		ImGui::SetNextWindowSize(ImVec2(600.000f, 400.000f), ImGuiCond_Once);
		ImGui::Begin(_("Comm Cord 100p"), NULL, ImGuiWindowFlags_AlwaysUseWindowPadding);

	
		

		
		
			ImGui::Checkbox(_("Aimbot"), &Settings::Aimbot);
			ImGui::Checkbox(_("Team Check"), &Settings::TeamCheck);
			ImGui::SliderFloat(_("Smoothing"), &Settings::AimbotSmooth, 1, 10, 0, 0);
			ImGui::Checkbox(_("FOV"), &Settings::ShowFov);
			ImGui::Checkbox(_("Filled FOV"), &Settings::filledfov);
			ImGui::SliderFloat(_("FOV size"), &Settings::AimbotFOV, 1.0f, 500.0f, "%.3f", 0);
			
			ImGui::Checkbox(_("Hitbox Selection"), &Settings::hitbox_selection);
			if (Settings::hitbox_selection) {
				ImGui::Checkbox(_("Head"), &Settings::head);
				if (Settings::head) {
					Settings::chest = false;
					Settings::neck = false;
					Settings::hips = false;
				}
				ImGui::Checkbox(_("Neck"), &Settings::neck);
				if (Settings::neck) {
					Settings::chest = false;
					Settings::head = false;
					Settings::hips = false;
				}
				ImGui::Checkbox(_("Chest"), &Settings::chest);
				if (Settings::chest) {
					Settings::neck = false;
					Settings::head = false;
					Settings::hips = false;
				}
				ImGui::Checkbox(_("Hips"), &Settings::hips);
				if (Settings::hips) {
					Settings::neck = false;
					Settings::head = false;
					Settings::chest = false;
				}
			}
			ImGui::Checkbox(_("Zero Recoil (Y)"), &Settings::rsc);
			if (ImGui::IsItemHovered()) {
				ImGui::TextWrapped(_("Uses a weird method only works when aiming in on the person and shooting"));
			}
			ImGui::Checkbox(_("Triggerbot"), &Settings::triggerbot);
			ImGui::SliderFloat(_("Trigger Time"), &Settings::trigger_time, 0, 50, 0, 0);
			ImGui::SliderFloat(_("Trigger Distance method"), &Settings::triggerbot_distance, 0, 40, 0, 0);
		
			ImGui::Checkbox(_("3D Box"), &Settings::Box3d);
			ImGui::Checkbox(_("health text"), &Settings::healthtext);
			ImGui::Checkbox(_("AimLine (UNTESTED)"), &Settings::AimLine);
			ImGui::Checkbox(_("Snaplines"), &Settings::Snaplines);
			ImGui::Checkbox(_("Snaplines From Crosshair"), &Settings::snap_from_cross);
			ImGui::SliderInt(_("Distance"), &visdistance, 1.0f, 250.0f, 0);
			ImGui::Checkbox(_("2d box"), &Settings::BoundedBox);
			ImGui::Checkbox(_("Health"), &Settings::PlayerHealth);
			ImGui::Checkbox(_("Triange Esp"), &Settings::triange_box);
			ImGui::Text("Esp Color (Not Visible)");
			ImGui::SliderInt(("R"), &Settings::Invisible[0], 0, 255, "%d", 0);
			ImGui::SliderInt(("G"), &Settings::Invisible[1], 0, 255, "%d", 0);
			ImGui::SliderInt(("B"), &Settings::Invisible[2], 0, 255, "%d", 0);
			ImGui::Text("Esp Color (Visible)");
			ImGui::SliderInt(("R2"), &Settings::Visible[0], 0, 255, "%d", 0);
			ImGui::SliderInt(("G2"), &Settings::Visible[1], 0, 255, "%d", 0);
			ImGui::SliderInt(("B2"), &Settings::Visible[2], 0, 255, "%d", 0);
		
		
			ImGui::Checkbox(_("Crosshair"), &Settings::Crosshair);
			ImGui::SliderInt(_("Crosshair Cricle Radius"), &Settings::crosshair_cricle_radius, 0, 20, "%d");
			ImGui::SliderInt(_("Crosshair Line Radius"), &Settings::crosshair_line_length, 0, 30, "%d");

			if (ImGui::Button(_("Save Config"), ImVec2(100, 50))) {
				SaveConfig();
			}
			ImGui::SameLine();
			if (ImGui::Button(_("Load Config"), ImVec2(100, 50))) {
				LoadConfig();
			}


		
			
			ImGui::Checkbox(_("Third-Person"), &thirdpersom);
			ImGui::Checkbox(_("Glow"), &Settings::Glow);
			ImGui::Checkbox(_("Bullet Tp"), &bullettp);
			ImGui::Checkbox(_("Nospread"), &nospread);
			if (ImGui::IsItemHovered()) {
				ImGui::TextWrapped(_("Once turned on cannot be turned off until you turn off the cheat only works for visible players"));
			}
			ImGui::Text(_("More Coming Soon"));


		
	}
	ImGui::End();
}


auto render()->VOID
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::StyleColorsDark();

	auto& Style = ImGui::GetStyle();

	Style.WindowPadding = ImVec2(12.000f, 8.000f);
	Style.WindowRounding = 12.000f;
	Style.WindowTitleAlign = ImVec2(0.030f, 0.500f);
	Style.ChildRounding = 12.000f;
	Style.PopupRounding = 12.000f;
	Style.FrameRounding = 12.000f;
	Style.ScrollbarRounding = 12.000f;
	Style.GrabRounding = 12.000f;
	Style.LogSliderDeadzone = 12.000f;
	Style.TabRounding = 12.000f;
	Style.DisplaySafeAreaPadding = ImVec2(2.000f, 3.000f);

	if (Settings::ShowFov) {
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), Settings::AimbotFOV, ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 100);
	}

	if (Settings::filledfov)
	{
		ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), Settings::AimbotFOV, ImColor(0,0,0, 100), 100);
	}
	
	if (Settings::Crosshair) {
		ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), Settings::crosshair_cricle_radius, ImColor(32, 0, 100));
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2((ImGui::GetIO().DisplaySize.x / 2) + Settings::crosshair_line_length, ImGui::GetIO().DisplaySize.y / 2), ImVec2((ImGui::GetIO().DisplaySize.x / 2) - Settings::crosshair_line_length, ImGui::GetIO().DisplaySize.y / 2), ImColor(100, 0, 0), 2);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2((ImGui::GetIO().DisplaySize.x / 2) , (ImGui::GetIO().DisplaySize.y / 2) + Settings::crosshair_line_length), ImVec2((ImGui::GetIO().DisplaySize.x / 2) , (ImGui::GetIO().DisplaySize.y / 2) - Settings::crosshair_line_length), ImColor(100, 0, 0), 2);
	}
	
	

	menu();
	ActorLoop();

	ImGui::Render();
	ImVec4 clear_color = ImVec4(0., 0., 0., 0.);
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	g_pSwapChain->Present(1, 0);
	
}
