#pragma once

inline void Render_2D_Box(int x, int y, int w, int h, const ImU32& color, int thickness)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), ImGui::GetColorU32(color), 0, 0, thickness);
}

inline void RectFilled(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color);
}

inline static void FilledRectangle(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color);
}

inline void Box(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color);
}

inline void DrawCornerBox(int x, int y, int w, int h, int borderPx, ImColor color)
{
	RectFilled(x + borderPx, y, w / 3, borderPx, color);
	RectFilled(x + w - w / 3 + borderPx, y, w / 3, borderPx, color);
	RectFilled(x, y, borderPx, h / 3, color);
	RectFilled(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
	RectFilled(x + borderPx, y + h + borderPx, w / 3, borderPx, color);
	RectFilled(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color);
	RectFilled(x + w + borderPx, y, borderPx, h / 3, color);
	RectFilled(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
}

inline void DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color) {
	ImGui::GetBackgroundDrawList()->AddQuadFilled(p1, p2, p3, p4, color);
}

inline void SeerHealth(float x, float y, int shield, int max_shield, int armorType, int health) {

	int bg_offset = 3;
	int bar_width = 39.5;
	// 4steps...2*3=6
	// 38*4=152 152+6 = 158
	// 5steps...2*4=8
	// 30*5=150 150+8 = 158
	float max_health = 50.f;
	float shield_step = 25.0f;

	int shield_25 = 15;
	int steps = 5;

	ImVec2 bg1(x - bar_width / 2 - bg_offset, y);
	ImVec2 bg2(bg1.x - 10, bg1.y - 16);
	ImVec2 bg3(bg2.x + 5, bg2.y - 7);
	ImVec2 bg4(bg3.x + bar_width + bg_offset, bg3.y);
	ImVec2 bg5(bg4.x + 11, bg4.y + 18);
	ImVec2 bg6(x + bar_width / 2 + bg_offset, y);


	ImVec2 h1(bg1.x + 3, bg1.y - 4);
	ImVec2 h2(h1.x - 5, h1.y - 8);
	ImVec2 h3(h2.x + (float)health / max_health * bar_width, h2.y);
	ImVec2 h4(h1.x + (float)health / max_health * bar_width, h1.y);
	ImVec2 h3m(h2.x + bar_width, h2.y);
	ImVec2 h4m(h1.x + bar_width, h1.y);
	DrawQuadFilled(h1, h2, h3m, h4m, ImColor(10, 10, 30, 60));
	DrawQuadFilled(h1, h2, h3, h4, ImColor(255, 255, 255, 255));


	ImColor shieldCracked(97, 97, 97);
	ImColor shieldCrackedDark(67, 67, 67);

	ImColor shieldCol;
	ImColor shieldColDark; //not used, but the real seer q has shadow inside
	if (armorType == 1) { //white
		shieldCol = ImColor(247, 247, 247);
		shieldColDark = ImColor(164, 164, 164);
	}
	else if (armorType == 2) { //blue
		shieldCol = ImColor(39, 178, 255);
		shieldColDark = ImColor(27, 120, 210);
	}
	else if (armorType == 3) { //purple
		shieldCol = ImColor(206, 59, 255);
		shieldColDark = ImColor(136, 36, 220);
	}
	else if (armorType == 4) { //gold
		shieldCol = ImColor(255, 255, 79);
		shieldColDark = ImColor(218, 175, 49);
	}
	else if (armorType == 5) { //red
		shieldCol = ImColor(219, 2, 2);
		shieldColDark = ImColor(219, 2, 2);
	}
	else {
		shieldCol = ImColor(247, 247, 247);
		shieldColDark = ImColor(164, 164, 164);
	}
	int shield_tmp = shield;
	int shield1 = 0;
	int shield2 = 0;
	int shield3 = 0;
	int shield4 = 0;
	int shield5 = 0;
	if (shield_tmp > 25) {
		shield1 = 25;
		shield_tmp -= 25;
		if (shield_tmp > 25) {
			shield2 = 25;
			shield_tmp -= 25;
			if (shield_tmp > 25) {
				shield3 = 25;
				shield_tmp -= 25;
				if (shield_tmp > 25) {
					shield4 = 25;
					shield_tmp -= 25;
					shield5 = shield_tmp;
				}
				else {
					shield4 = shield_tmp;
				}
			}
			else {
				shield3 = shield_tmp;
			}
		}
		else {
			shield2 = shield_tmp;
		}
	}
	else {
		shield1 = shield_tmp;
	}
	ImVec2 s1(h2.x - 1, h2.y - 2);
	ImVec2 s2(s1.x - 3, s1.y - 5);
	ImVec2 s3(s2.x + shield1 / shield_step * shield_25, s2.y);
	ImVec2 s4(s1.x + shield1 / shield_step * shield_25, s1.y);
	ImVec2 s3m(s2.x + shield_25, s2.y);
	ImVec2 s4m(s1.x + shield_25, s1.y);

	ImVec2 ss1(s4m.x + 2, s1.y);
	ImVec2 ss2(s3m.x + 2, s2.y);
	ImVec2 ss3(ss2.x + shield2 / shield_step * shield_25, s2.y);
	ImVec2 ss4(ss1.x + shield2 / shield_step * shield_25, s1.y);
	ImVec2 ss3m(ss2.x + shield_25, s2.y);
	ImVec2 ss4m(ss1.x + shield_25, s1.y);

	ImVec2 sss1(ss4m.x + 2, s1.y);
	ImVec2 sss2(ss3m.x + 2, s2.y);
	ImVec2 sss3(sss2.x + shield3 / shield_step * shield_25, s2.y);
	ImVec2 sss4(sss1.x + shield3 / shield_step * shield_25, s1.y);
	ImVec2 sss3m(sss2.x + shield_25, s2.y);
	ImVec2 sss4m(sss1.x + shield_25, s1.y);

	ImVec2 ssss1(sss4m.x + 2, s1.y);
	ImVec2 ssss2(sss3m.x + 2, s2.y);
	ImVec2 ssss3(ssss2.x + shield4 / shield_step * shield_25, s2.y);
	ImVec2 ssss4(ssss1.x + shield4 / shield_step * shield_25, s1.y);
	ImVec2 ssss3m(ssss2.x + shield_25, s2.y);
	ImVec2 ssss4m(ssss1.x + shield_25, s1.y);

	ImVec2 sssss1(ssss4m.x + 2, s1.y);
	ImVec2 sssss2(ssss3m.x + 2, s2.y);
	ImVec2 sssss3(sssss2.x + shield5 / shield_step * shield_25, s2.y);
	ImVec2 sssss4(sssss1.x + shield5 / shield_step * shield_25, s1.y);
	ImVec2 sssss3m(sssss2.x + shield_25, s2.y);
	ImVec2 sssss4m(sssss1.x + shield_25, s1.y);
	if (max_shield == 50) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield != 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
	}
	else if (max_shield == 75) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield < 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
		else if (shield <= 75) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			if (shield < 75) {
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
		}
	}
	else if (max_shield == 100) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield < 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
		else if (shield <= 75) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			if (shield < 75) {
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
		}
		else if (shield <= 100) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			if (shield < 100) {
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
		}
	}
	else if (max_shield == 125) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield < 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
		else if (shield <= 75) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			if (shield < 75) {
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
		}
		else if (shield <= 100) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			if (shield < 100) {
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
		}
		else if (shield <= 125) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
			if (shield < 125) {
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sssss1, sssss2, sssss3, sssss4, shieldCol);
		}
	}
}

inline void Render_Head_Angle(int x, int y, int z, int x1, int y1, int z1) {
	Vector3 bottom1 = ProjectWorldToScreen(Vector3(x + 10, y - 10, z));
	Vector3 bottom2 = ProjectWorldToScreen(Vector3(x - 10, y - 10, z));
	Vector3 bottom3 = ProjectWorldToScreen(Vector3(x - 10, y + 10, z));
	Vector3 bottom4 = ProjectWorldToScreen(Vector3(x + 10, y + 10, z));
	Vector3 top1 = ProjectWorldToScreen(Vector3(x1 + 10, y1 - 10, z1 + 15));
	Vector3 top2 = ProjectWorldToScreen(Vector3(x1 - 10, y1 - 10, z1 + 15));
	Vector3 top3 = ProjectWorldToScreen(Vector3(x1 - 10, y1 + 10, z1 + 15));
	Vector3 top4 = ProjectWorldToScreen(Vector3(x1 + 10, y1 + 10, z1 + 15));

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ImColor(Settings::ESP_snap[0], Settings::ESP_snap[1], Settings::ESP_snap[2], Settings::ESP_snap[3]), 0.1f);
}