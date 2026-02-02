#include "TutorialBackground.h"
#include <Novice.h>
#include <cmath>

TutorialBackground::TutorialBackground()
{
    textureHandles_[0] = Novice::LoadTexture("./Textures/UI/Background/ttestplay1.png");
    textureHandles_[1] = Novice::LoadTexture("./Textures/UI/Background/ttestplay2.png");
    textureHandles_[2] = Novice::LoadTexture("./Textures/UI/Background/ttestplay3.png");
    textureHandles_[3] = Novice::LoadTexture("./Textures/UI/Background/ttestplay4.png");
    textureHandles_[4] = Novice::LoadTexture("./Textures/UI/Background/ttestplay5.png");
    textureHandles_[5] = Novice::LoadTexture("./Textures/UI/Background/ttestplay6.png");
    textureHandles_[6] = Novice::LoadTexture("./Textures/UI/Background/ttestplay7.png");
    textureHandles_[7] = Novice::LoadTexture("./Textures/UI/Background/ttestplay8.png");
    // If you want a logo overlay for tutorial scene:
    //logoTexture_ = Novice::LoadTexture("./Textures/UI/tutorialbg/tutoriallogo.png");
}

void TutorialBackground::Update()
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

void TutorialBackground::Draw()
{
    int handle = textureHandles_[currentFrame_];
    Novice::DrawSprite(
        posX_ - width_ / 2,
        posY_ - height_ / 2,
        handle,
        1.0f, 1.0f,
        0.0f,
        WHITE);
}

void TutorialBackground::DrawLogo()
{
    static int frameCountForOverlay = 0;
    frameCountForOverlay++;
    float hoverOffset = (std::sinf(frameCountForOverlay * 0.04f) * 13.0f) - (10);

    Novice::DrawSprite(
        posX_ - width_ / 2,
        posY_ - height_ / 2 + static_cast<int>(hoverOffset),
        logoTexture_,
        1.0f, 1.0f,
        0.0f,
        WHITE);
}