#include "TitleLogo.h"
#include <cmath>

TitleLogo::TitleLogo()
{
	logoFrames_[0] = Novice::LoadTexture("./Textures/UI/Title/Logo/Btitle1.png");
	logoFrames_[1] = Novice::LoadTexture("./Textures/UI/Title/Logo/Btitle2.png");
	logoFrames_[2] = Novice::LoadTexture("./Textures/UI/Title/Logo/Btitle3.png");
	logoFrames_[3] = Novice::LoadTexture("./Textures/UI/Title/Logo/Btitle4.png");
	logoFrames_[4] = Novice::LoadTexture("./Textures/UI/Title/Logo/Btitle5.png");

	scaleEasing_.Init(0.0f, 1.0f, 180, EasingType::EASING_EASE_OUT_BACK);

}

void TitleLogo::Update() {
	sceneTimer_++;

	if (sceneTimer_ == 30)
	{
		scaleEasing_.Start();
	}

	scaleEasing_.Update();
	float logoScale = scaleEasing_.easingRate;

	isIntroFinished_ = (!scaleEasing_.isMove && logoScale >= 1.0f - 0.001f);

	if (isIntroFinished_)
	{
		frameCount_++;
		hoverOffset_ = std::sinf(frameCount_ * 0.04f) * 13.0f;
	}

}


void TitleLogo::Draw() {
	float logoScale = scaleEasing_.easingRate;
	if (logoScale <= 0.0f)
	{
		return;
	}

	int currentFrame = 0;
	if (isIntroFinished_)
	{
		currentFrame = (frameCount_ / frameDuration_) % kFrameCount;
	}

	int dW = static_cast<int>(logoW_ * logoScale);
	int dH = static_cast<int>(logoH_ * logoScale);

	int topY = centerY_ - dH / 2 + static_cast<int>(hoverOffset_);
	int bottomY = centerY_ + dH / 2 + static_cast<int>(hoverOffset_);

	Novice::DrawQuad(
		centerX_ - dW / 2, topY,
		centerX_ + dW / 2, topY,
		centerX_ - dW / 2, bottomY,
		centerX_ + dW / 2, bottomY,
		0, 0, logoW_, logoH_,
		logoFrames_[currentFrame],
		0xFFFFFFFF
	);
}
