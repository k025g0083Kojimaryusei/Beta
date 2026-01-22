#include "UI.h"
#include <imgui.h>

UI::UI() {
	Init();
}

void UI::Init() {
	scoreBoardTransform_.Init(position_, scoreBoardW, scoreBoardH);
}

void UI::Draw() {
	ImGui::DragFloat2("position", &position_.x, 0.1f);
	scoreBoardTransform_.Init(position_, scoreBoardW, scoreBoardH);

	Quad screenSB = CameraManager::GetInstance()->GetUICamera().WorldToScreen(scoreBoardTransform_);
	Novice::DrawQuad(
		static_cast<int>(screenSB.v[0].x), static_cast<int>(screenSB.v[0].y),
		static_cast<int>(screenSB.v[1].x), static_cast<int>(screenSB.v[1].y),
		static_cast<int>(screenSB.v[2].x), static_cast<int>(screenSB.v[2].y),
		static_cast<int>(screenSB.v[3].x), static_cast<int>(screenSB.v[3].y),
		0, 0,
		static_cast<int>(scoreBoardTransform_.width),
		static_cast<int>(scoreBoardTransform_.height),
		scoreBoardTextureHandle_, WHITE
	);
}