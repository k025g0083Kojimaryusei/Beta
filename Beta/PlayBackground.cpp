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
}

void PlayBackground::Draw()
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