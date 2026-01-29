#include "PlayBackground.h"
#include <Novice.h>
#include <cmath>

PlayBackground::PlayBackground()
{
	textureHandles_[0] = Novice::LoadTexture("./Textures/UI/background/bgg1.png");
	textureHandles_[1] = Novice::LoadTexture("./Textures/UI/background/bgg2.png");
	textureHandles_[2] = Novice::LoadTexture("./Textures/UI/background/bgg3.png");
	textureHandles_[3] = Novice::LoadTexture("./Textures/UI/background/bgg4.png");
	textureHandles_[4] = Novice::LoadTexture("./Textures/UI/background/bgg5.png");
	logoTexture_= Novice::LoadTexture("./Textures/UI/background/playlogo.png");
}

void PlayBackground::Update()
{
	frameCounter_++;
	if (frameCounter_ >= frameChangeInterval_) {
		frameCounter_ = 0;
		currentFrame_++;
		if (currentFrame_ >= kFrameCount) {
			currentFrame_ = 0;
		}
	}

	if (isRedFlashing_) {
		redFlashTimer_++;
		// Fade out: fade quickly at start then slower
		redFlashAlpha_ = 1.0f - (float)redFlashTimer_ / (float)kRedFlashDuration_;
		if (redFlashAlpha_ < 0.0f) redFlashAlpha_ = 0.0f;

		if (redFlashTimer_ > kRedFlashDuration_) {
			isRedFlashing_ = false;
			redFlashAlpha_ = 0.0f;
		}
	}
}

void PlayBackground::Draw()
{
	int handle = textureHandles_[currentFrame_];
	// Always draw BG with WHITE
	Novice::DrawSprite(
		posX_ - width_ / 2,
		posY_ - height_ / 2,
		handle,
		1.0f, 1.0f,
		0.0f,
		WHITE);

	// Draw the red overlay ON TOP (not below) when flashing
	if (isRedFlashing_ && redFlashAlpha_ > 0.0f) {
		int alpha = (int)(redFlashAlpha_ * 180); // 0~255, tweak as needed
		if (alpha > 255) alpha = 255;
		if (alpha < 0) alpha = 0;
		// RGBA color: red with alpha. For Novice, usually 0xRRGGBBAA or 0xAARRGGBB (test!).
		int flashColor = (0xFF << 24) | (0x00 << 16) | (0x00 << 8) | (alpha); // 0xFF0000AA (red A)
		// If Novice is 0xRRGGBBAA:
		flashColor = (0xFF << 24) | (alpha); // 0xFF0000AA (red with alpha at the end)
		Novice::DrawBox(
			posX_ - width_ / 2,
			posY_ - height_ / 2,
			width_,
			height_,
			0.0f,
			flashColor,
			kFillModeSolid);
	}
}

void PlayBackground::DrawLogo()
{
	static int frameCountForOverlay = 0;
	frameCountForOverlay++;
	float hoverOffset = (std::sinf(frameCountForOverlay * 0.04f) * 13.0f) - (10);

	Novice::DrawSprite(
		posX_ - width_ / 2 ,
		posY_ - height_ / 2 + static_cast<int>(hoverOffset),
		logoTexture_,
		1.0f, 1.0f,
		0.0f,
		WHITE);
}

void PlayBackground::TriggerRedFlash() {
	isRedFlashing_ = true;
	redFlashTimer_ = 0;
	redFlashAlpha_ = 1.0f; // start fully opaque
}