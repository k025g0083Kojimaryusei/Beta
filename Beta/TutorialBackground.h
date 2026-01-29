#pragma once
class TutorialBackground
{
public:
    TutorialBackground();
    ~TutorialBackground() = default;

    void Update();
    void Draw();
    void DrawLogo(); // If you want a logo overlay too

private:
    static const int kFrameCount = 8;
    int textureHandles_[kFrameCount]{};
    int logoTexture_ = 0;

    int currentFrame_ = 0;
    int frameCounter_ = 0;
    int frameChangeInterval_ = 12; // You can adjust for speed

    int posX_ = 640;
    int posY_ = 360;
    int width_ = 1300;
    int height_ = 740;
};