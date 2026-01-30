#include "TitleBackground.h"

TitleBackground::TitleBackground()
{
	textureHandles_[0] = Novice::LoadTexture("./Textures/UI/Title/B1.png");
	textureHandles_[1] = Novice::LoadTexture("./Textures/UI/Title/B2.png");
	textureHandles_[2] = Novice::LoadTexture("./Textures/UI/Title/B3.png");
	textureHandles_[3] = Novice::LoadTexture("./Textures/UI/Title/B4.png");
	textureHandles_[4] = Novice::LoadTexture("./Textures/UI/Title/B5.png");
}

void TitleBackground::Update()
{
	frameCounter_++;
	if (frameCounter_ >= frameChangeInterval_) {
		frameCounter_ = 0;
		currentFrame_++;
		if (currentFrame_ >= kFrameCount) {
			currentFrame_ = 0;
		}
	}
}

void TitleBackground::Draw()
{
	int handle = textureHandles_[currentFrame_];

	Novice::DrawSprite(
		posX_ - width_ /2,
		posY_ - height_ /2,
		handle,
		1.0f, 1.0f,
		0.0f,
		WHITE);
}
