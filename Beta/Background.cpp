#include "Background.h"

Background::Background() {
	Init();
}

void Background::Init() {
	backgroundTransform_.Init({ 640.0f,360.0f }, backgroundW, backgroundH);

}

void Background::Draw() {
	Quad screenBG = CameraManager::GetInstance()->GetUICamera().WorldToScreen(backgroundTransform_);
	Novice::DrawQuad(
		static_cast<int>(screenBG.v[0].x), static_cast<int>(screenBG.v[0].y),
		static_cast<int>(screenBG.v[1].x), static_cast<int>(screenBG.v[1].y),
		static_cast<int>(screenBG.v[2].x), static_cast<int>(screenBG.v[2].y),
		static_cast<int>(screenBG.v[3].x), static_cast<int>(screenBG.v[3].y),
		0, 0,
		static_cast<int>(backgroundTransform_.width),
		static_cast<int>(backgroundTransform_.height),
		backgroundTextureHandle_, WHITE
	);
}