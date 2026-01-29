#pragma once
class PlayBackground
{
public:

	PlayBackground();
	~PlayBackground() = default;

	void Update();
	void Draw();
	void DrawLogo();
	void TriggerRedFlash();

private:

	static const int kFrameCount = 5;
	int textureHandles_[kFrameCount]{};
	int logoTexture_ = 0;

	int currentFrame_ = 0;
	int frameCounter_ = 0;
	int frameChangeInterval_ = 5;

	int posX_ = 640;
	int posY_ = 360;
	int width_ = 1300;
	int height_ = 740;

	bool isRedFlashing_ = false;
	int redFlashTimer_ = 0;
	const int kRedFlashDuration_ = 16; // how many frames to show the full flash
	float redFlashAlpha_ = 0.0f; // (for fade out)
};

