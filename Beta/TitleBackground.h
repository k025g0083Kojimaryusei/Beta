#pragma once
#include <Novice.h>

class TitleBackground
{
public:
	TitleBackground();
	~TitleBackground() = default;

	void Update();
	void Draw();

private:
	static const int kFrameCount = 5;
	int textureHandles_[kFrameCount]{};

	int currentFrame_ = 0;
	int frameCounter_ = 0;
	int frameChangeInterval_ = 8;

	int posX_ = 640;
	int posY_ = 360;
	int width_ = 1300;
	int height_ = 740;
};

