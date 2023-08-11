#pragma once
#include "comms.h"
#include "offsets2.h"




static int visdistance = 250.f;
int loot_distance = 150;
bool cornerbox = true;
bool crosshair = true;
bool streamproof = false;
bool ThirdPerson = false;
bool fovcircle = true;

bool exploits = true;
bool thirdpersom = false;
bool airstuck = false;
bool infrifle = false;
static bool bullettp = false;
static bool nospread = false;
uintptr_t Entity;
int i;
int Width;
int Height;


void __cdecl WorldCache(void*) {
	while (true) {
		Addresses::ViewRenderer = Km.Rpm<uint64_t>(Km.module + OFFSET_RENDER);
		Addresses::ViewMatrix = Km.Rpm<uint64_t>(Addresses::ViewRenderer + OFFSET_MATRIX);
		Addresses::LocalPlayer = Km.Rpm<uintptr_t>(Km.module + OFFSET_LOCAL_ENT);
		Addresses::NameList = Km.Rpm<uintptr_t>(Km.module + OFFSET_NAME_LIST);
	}
	
}

float ToMeters(float x)
{
	return x / 39.62f;
}






auto ActorLoop()->VOID {
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(15, 15), ImColor(255, 0, 0, 255), _("Comm Cord FREE PASTA"));
	
	for (int i = 0; i < 65; i++)
	{

		uintptr_t Entity = GetEntityById(i);

		float closestDistance = FLT_MAX;
		uintptr_t closestPawn = NULL;
		if (Entity == 0)
			continue;
		uintptr_t EntityHandle = Km.Rpm<uintptr_t>(Entity + OFFSET_NAME);
		std::string Identifier = Km.Rpm<std::string>(EntityHandle);
		LPCSTR IdentifierC = Identifier.data();
		if (strcmp(IdentifierC, _("Player")))
		{
			Vector3 head2 = GetEntityBonePosition(Entity, 8);  Vector3 Head = ProjectWorldToScreen(head2); if (Head.z <= 0.f) continue;
			Vector3 neck2 = GetEntityBonePosition(Entity, 7); Vector3 Neck = ProjectWorldToScreen(neck2); if (Neck.z <= 0.f) continue;
			Vector3 chest2 = GetEntityBonePosition(Entity, 5); Vector3 Chest = ProjectWorldToScreen(chest2); if (Chest.z <= 0.f) continue;
			Vector3 hips2 = GetEntityBonePosition(Entity, 0); Vector3 Hips = ProjectWorldToScreen(hips2); if (Hips.z <= 0.f) continue;
			Vector3 bottom2 = Km.Rpm<Vector3>(Entity + OFFSET_ORIGIN);  Vector3 Bottom = ProjectWorldToScreen(bottom2);
			Vector3 localpos = Km.Rpm<Vector3>(Addresses::LocalPlayer + OFFSET_ORIGIN);


			float dist = Km.Rpm<Vector3>(Addresses::LocalPlayer + 0x14c).DistTo(head2);
			float distM = ToMeters(dist);
			int EntityDBNO = Km.Rpm<int>(Entity + OFFSET_BLEED_OUT_STATE);
			int PlayerTeamIndex = Km.Rpm<int>(Addresses::LocalPlayer + OFFSET_TEAM);
			int EntityTeamIndex = Km.Rpm<int>(Entity + OFFSET_TEAM);
			int EntityHealth = Km.Rpm<int>(Entity + OFFSET_HEALTH);

			if (exploits)
			{
				if (thirdpersom)
				{
					Km.Wpm<int>(Km.module + OFFSET_THIRDPERSON, true);
					Km.Wpm<int>(Entity + OFFSET_THIRDPERSON_SV, true);
				}
				else
				{
					Km.Wpm<int>(Km.module + OFFSET_THIRDPERSON, false);
					Km.Wpm<int>(Entity + OFFSET_THIRDPERSON_SV, false);
				}

				if (airstuck)
				{
					if (MouseController::GetAsyncKeyState(VK_SHIFT))
					{
						Km.Wpm<float>(Km.module + OFFSET_TIMESCALE, 0); //host_timescale
					}
					else
					{
						Km.Wpm<float>(Km.module + OFFSET_TIMESCALE + 0x68, 1); //host_timescale
					}
				}

				if (infrifle)
				{
					DWORD64 EntityNerds = Km.Rpm<DWORD64>(Km.module + OFFSET_LOCAL_ENT);
					DWORD64 LastWeapon = Km.Rpm<DWORD64>(EntityNerds + OFFSET_WEAPON) & 0xFFFF;
					DWORD64 Weapon = Km.Rpm<DWORD64>(Km.module + OFFSET_ENTITYLIST + (LastWeapon << 5));
					float BulletSpeed = Km.Rpm<float>(Weapon + 0x1ef0); // CWeaponX!m_flProjectileSpeed
					int ammoInclip = Km.Rpm<int>(Weapon + OFFSET_AMMO);
					if (ammoInclip != 0 && BulletSpeed == 1 && MouseController::GetAsyncKeyState(VK_LBUTTON)) {
						Km.Wpm<float>(Km.module + 0x014ad600 + 0x68, 0.000000000000000000000000000000000000000001);  //host_timescale
					}
					else
					{
						Km.Wpm<float>(Km.module + 0x014ad600 + 0x68, 1);
					}
				}
				if (bullettp) {
					uintptr_t CProjectile = Km.Rpm<uintptr_t>(Km.module + 0x02048c68);
					uintptr_t BulletLoc = CProjectile + 0x1684; //m_launchOrigin 
					uintptr_t LocalAngles = CProjectile + 0x494;//m_localAngles
					uintptr_t WeaponSrc = CProjectile + 0x1668;//m_weaponSource
					
						if (GetAsyncKeyState(VK_LEFT) & 1 && isVisible(Entity, i)) {
						
							Aimbot(closestPawn, Neck.x, Neck.y); //something with CProjectile_LocalAngles for better experience
							Km.Wpm<int>(WeaponSrc, 1);
							Km.Wpm<Vector3>(BulletLoc, Vector3{ neck2.x, neck2.y, neck2.z });
							
						}
				}
				if (nospread) {
					uintptr_t CWeaponX = Km.module + 0x020573e8;
					uintptr_t SpreadMove = CWeaponX + 0x16c0;
					uintptr_t SpreadADS = CWeaponX + 0x16cc;
					Km.Wpm<float>(SpreadMove, 0.01f);
					Km.Wpm<float>(SpreadADS, 0.01f);
				}
			}
			if (isVisible(Entity, i)) {
				Settings::ESP_snap[0] = Settings::Visible[0];
				Settings::ESP_snap[1] = Settings::Visible[1];
				Settings::ESP_snap[2] = Settings::Visible[2];
			}
			else {
				Settings::ESP_snap[0] = Settings::Invisible[0];
				Settings::ESP_snap[1] = Settings::Invisible[1];
				Settings::ESP_snap[2] = Settings::Invisible[2];
			}

			float ActorHeight = (float)(Head.y - Bottom.y);
			float ActorWidth = ActorHeight * 0.780;

			//if (distM <= visdistance)
			if (Settings::TeamCheck) {
				if (EntityTeamIndex != PlayerTeamIndex) //!EntityDBNO && EntityHealth != 0
				{
					if (Settings::Glow)
					{
						Km.Wpm<int>(Entity + OFFSET_GLOW_ENABLE, 7);
						Km.Wpm<int>(Entity + OFFSET_GLOW_THROUGH_WALLS, 2);
						Km.Wpm<int>(Entity + OFFSET_GLOW_T1, 16256);
						Km.Wpm<int>(Entity + OFFSET_GLOW_T2, 1193322764);
						///Km.Wpm<GlowMode>(Entity + Offsets::Glow_Type, { 101,101,46, 90 }); // glow type: GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
						if (isVisible(Entity, i)) {
							Km.Wpm<float>(Entity + 0x1D0, Settings::Visible[0]);//r
							Km.Wpm<float>(Entity + 0x1D4, Settings::Visible[1]);//g						
							Km.Wpm<float>(Entity + 0x1D8, Settings::Visible[2]);//b
						}
						else {
							Km.Wpm<float>(Entity + 0x1D0, Settings::Invisible[0]);
							Km.Wpm<float>(Entity + 0x1D4, Settings::Invisible[1]);
							Km.Wpm<float>(Entity + 0x1D8, Settings::Invisible[2]);
						}
					}
					if (Settings::snap_from_cross) {
						Settings::Snaplines = false;
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImVec2(Head.x, Head.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]));
					}

					if (Settings::Snaplines)
					{
						Settings::snap_from_cross = false;
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y), ImVec2(Head.x, Head.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]));
					}

					if (Settings::PlayerHealth)
					{
						float ActorHeight = (float)(Head.y - Bottom.y);
						int Health = Km.Rpm<int>(Entity + OFFSET_HEALTH);
						int Shield = Km.Rpm<int>(Entity + OFFSET_SHIELD);
						int MaxShield = Km.Rpm<int>(Entity + OFFSET_SHEILD_MAX);
						int ShieldType = Km.Rpm<int>(Entity + OFFSET_SHEILD_TYPE);
						std::string health = std::to_string(Health).c_str();
						auto size = ImGui::CalcTextSize(health.c_str());
						//SeerHealth(Head.x - size.x / 2.f, Head.y - 20, Shield, MaxShield, ShieldType, Health);
						int size3 = Head.y - Hips.y;
						ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(Head.x + 10, (Hips.y + (size3 * (Health / 100)))), ImVec2(Head.x + 30, (Head.y + (size3 * (Health / 100)))), ImVec2(Head.x + 30, Hips.y), ImVec2(Head.x + 10, Hips.y), ImColor(17, 226, 31, 1));
						ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(Head.x - 10, Hips.y + (size3 * (Shield / MaxShield))), ImVec2(Head.x - 30, Head.y + (size3 * (Shield / MaxShield))), ImVec2(Head.x - 30, Hips.y), ImVec2(Head.x - 10, Hips.y), ImColor(0, 255, 250, 1));
					}

					if (Settings::Box3d)
					{
						Render_Head_Angle(bottom2.x, bottom2.y, bottom2.z, head2.x, head2.y, head2.z);
					}
					if (Settings::BoundedBox) {
						ImGui::GetBackgroundDrawList()->AddQuad(ImVec2(Head.x + 10, Head.y), ImVec2(Head.x - 10, Head.y), ImVec2(Bottom.x - 10, Bottom.y), ImVec2(Bottom.x + 10, Bottom.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 1);
					}
					if (Settings::triange_box) {
						ImGui::GetBackgroundDrawList()->AddTriangle(ImVec2(Head.x, Head.y + 10), ImVec2(Bottom.x + 30, Bottom.y), ImVec2(Bottom.x - 30, Bottom.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]));
					}
					if (Settings::AimLine) {
						if (Head.x != 0 || Head.y != 0 || Head.z != 0) {
							if ((GetCrossDistance(Head.x, Head.y, Width / 2, Height / 2) <= Settings::AimbotFOV)) {
								ImGui::GetBackgroundDrawList()->AddLine({ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1) / 2 }, { (float)Head.x, (float)Head.y }, ImColor(166, 2, 3), 2);

							}
						}
					}
					if (Settings::Aimbot) {
						auto dx = Head.x - (ImGui::GetIO().DisplaySize.x / 2);
						auto dy = Head.y - (ImGui::GetIO().DisplaySize.y / 2);
						auto dist = sqrtf(dx * dx + dy * dy) / 100.0f;
						if (dist < Settings::AimbotFOV && dist < closestDistance) {
							closestDistance = dist;
							closestPawn = Entity;
						}
					}
					if (Settings::head) {
						Settings::hitbox = Head;
					}
					else if (Settings::neck) {
						Settings::hitbox = Neck;
					}
					else if (Settings::chest) {
						Settings::hitbox = Chest;
					}
					else if (Settings::hips) {
						Settings::hitbox = Hips;
					}
					else {
						Settings::hitbox = Neck;
					}
					if (Settings::Aimbot && MouseController::GetAsyncKeyState(VK_RBUTTON) && isVisible(Entity, i)) {
						if ((GetCrossDistance(Head.x, Head.y, ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2) <= Settings::AimbotFOV)) {
							Aimbot(closestPawn, Settings::hitbox.x, Settings::hitbox.y);
						}
					}


				}
			}
			else
			{
				if (Settings::Glow)
				{
					Km.Wpm<int>(Entity + OFFSET_GLOW_ENABLE, 7);
					Km.Wpm<int>(Entity + OFFSET_GLOW_THROUGH_WALLS, 2);
					Km.Wpm<int>(Entity + OFFSET_GLOW_T1, 16256);
					Km.Wpm<int>(Entity + OFFSET_GLOW_T2, 1193322764);
					///Km.Wpm<GlowMode>(Entity + Offsets::Glow_Type, { 101,101,46, 90 }); // glow type: GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
					if (isVisible(Entity, i)) {
						Km.Wpm<float>(Entity + 0x1D0, Settings::Visible[0]);//r
						Km.Wpm<float>(Entity + 0x1D4, Settings::Visible[1]);//g						
						Km.Wpm<float>(Entity + 0x1D8, Settings::Visible[2]);//b
					}
					else {
						Km.Wpm<float>(Entity + 0x1D0, Settings::Invisible[0]);
						Km.Wpm<float>(Entity + 0x1D4, Settings::Invisible[1]);
						Km.Wpm<float>(Entity + 0x1D8, Settings::Invisible[2]);
					}
				}
				if (Settings::snap_from_cross) {
					Settings::Snaplines = false;
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImVec2(Head.x, Head.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]));
				}

				if (Settings::Snaplines)
				{
					Settings::snap_from_cross = false;
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y), ImVec2(Head.x, Head.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]));
				}
				if (Settings::healthtext) {
					int Health = Km.Rpm<int>(Entity + OFFSET_HEALTH);
					int Shield = Km.Rpm<int>(Entity + OFFSET_SHIELD);
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(Head.x, Head.y + 20), ImColor(0, 0, 0, 0), _("Total heatlh: "));
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(Head.x + 50, Head.y + 20), ImColor(0, 0, 0, 0), (const char*)Health + Shield);
				}
				if (Settings::PlayerHealth)
				{
					float ActorHeight = (float)(Head.y - Bottom.y);
					int Health = Km.Rpm<int>(Entity + OFFSET_HEALTH);
					int Shield = Km.Rpm<int>(Entity + OFFSET_SHIELD);
					int MaxShield = Km.Rpm<int>(Entity + OFFSET_SHEILD_MAX);
					int ShieldType = Km.Rpm<int>(Entity + OFFSET_SHEILD_TYPE);
					//std::string health = std::to_string(Health).c_str();
					//auto size = ImGui::CalcTextSize(health.c_str());
					//SeerHealth(Head.x - size.x / 4.f, Head.y - 20, Shield, MaxShield, ShieldType, Health);
					int size3 = Head.y - Hips.y;
					ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(Head.x + 10, (Hips.y + (size3 * (Health / 100)))), ImVec2(Head.x + 30, (Head.y + (size3 * (Health / 100)))), ImVec2(Head.x + 30, Hips.y), ImVec2(Head.x + 10, Hips.y), ImColor(17, 226, 31, 1));
					ImGui::GetBackgroundDrawList()->AddQuadFilled(ImVec2(Head.x - 10, Hips.y + (size3 * (Shield / MaxShield))), ImVec2(Head.x - 30, Head.y + (size3 * (Shield / MaxShield))), ImVec2(Head.x - 30, Hips.y), ImVec2(Head.x - 10, Hips.y), ImColor(0, 255, 250, 1));
				}

				if (Settings::Box3d)
				{
					Render_Head_Angle(bottom2.x, bottom2.y, bottom2.z, head2.x, head2.y, head2.z);
				}
				if (Settings::BoundedBox) {
					ImGui::GetBackgroundDrawList()->AddQuad(ImVec2(Head.x + 10, Head.y), ImVec2(Head.x - 10, Head.y), ImVec2(Bottom.x - 10, Bottom.y), ImVec2(Bottom.x + 10, Bottom.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 1);
				}
				if (Settings::triange_box) {
					ImGui::GetBackgroundDrawList()->AddTriangle(ImVec2(Head.x, Head.y + 10), ImVec2(Bottom.x + 30, Bottom.y), ImVec2(Bottom.x - 30, Bottom.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]));
				}
				if (Settings::AimLine) {
					if (Head.x != 0 || Head.y != 0 || Head.z != 0) {
						if ((GetCrossDistance(Head.x, Head.y, Width / 2, Height / 2) <= Settings::AimbotFOV)) {
							ImGui::GetBackgroundDrawList()->AddLine({ (float)GetSystemMetrics(0) / 2, (float)GetSystemMetrics(1) / 2 }, { (float)Head.x, (float)Head.y }, ImColor(166, 2, 3), 2);

						}
					}
				}
				if (Settings::Aimbot) {
					auto dx = Head.x - (ImGui::GetIO().DisplaySize.x / 2);
					auto dy = Head.y - (ImGui::GetIO().DisplaySize.y / 2);
					auto dist = sqrtf(dx * dx + dy * dy) / 100.0f;
					if (dist < Settings::AimbotFOV && dist < closestDistance) {
						closestDistance = dist;
						closestPawn = Entity;
					}
				}
				if (Settings::head) {
					Settings::hitbox = Head;
				}
				else if (Settings::neck) {
					Settings::hitbox = Neck;
				}
				else if (Settings::chest) {
					Settings::hitbox = Chest;
				}
				else if (Settings::hips) {
					Settings::hitbox = Hips;
				}
				else {
					Settings::hitbox = Neck;
				}
				if (Settings::Aimbot && MouseController::GetAsyncKeyState(VK_RBUTTON) && isVisible(Entity, i)) {
					if ((GetCrossDistance(Head.x, Head.y, ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2) <= Settings::AimbotFOV)) {
						Aimbot(closestPawn, Settings::hitbox.x, Settings::hitbox.y);
					}
				}
			}
		}
	}
}
void gay() {
	if (Settings::Aimbot && MouseController::GetAsyncKeyState(VK_RBUTTON) && MouseController::GetAsyncKeyState(VK_LBUTTON) && isVisible(Entity, i) && Settings::rsc) {
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x != Settings::hitbox.x || p.y != Settings::hitbox.y) {
				MouseController::Move_Mouse(Settings::hitbox.x, Settings::hitbox.y);
			}
		}
	}
	if (Settings::Aimbot && MouseController::GetAsyncKeyState(VK_RBUTTON) && isVisible(Entity, i) && Settings::triggerbot) {
		POINT p;
		if (GetCursorPos(&p)) {
			if (GetCrossDistance(p.x, p.y, Settings::hitbox.x, Settings::hitbox.y) < Settings::triggerbot_distance) {
				Sleep(Settings::trigger_time);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			}
		}
	}
}