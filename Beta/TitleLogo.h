#pragma once
#include <Novice.h>
#include "Easing.h"

class TitleLogo
{
public:
	TitleLogo();
	~TitleLogo() = default;

	void Update();
	void Draw();

	bool IsIntroFinished() const { return isIntroFinished_; }

private:
	static const int kFrameCount = 5;
	int logoFrames_[kFrameCount]{};

	int frameCount_ = 0;
	int frameDuration_ = 6;
	int sceneTimer_ = 0;
	float hoverOffset_ = 0.0f;
	bool isIntroFinished_ = false;

	int logoW_ = 1300;
	int logoH_ = 740;

	int centerX_ = 640;
	int centerY_ = 360;

	Easing scaleEasing_;
};

