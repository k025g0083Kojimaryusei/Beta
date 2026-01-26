#include "TitleScene2.h"
#include <Novice.h>
#include <cmath>

TitleScene2::TitleScene2(SceneManager* manager)
    : sceneManager(manager), bg_(), logo_(), selectedIndex(0)
{
    logo_.SetIntroDuration(120); // You can change intro duration or rotate speed here
    logo_.SetRotateSpeed(2.5f);
    enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");
    bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/B.png");

}

void TitleScene2::Update(char* keys, char* preKeys)
{
    frameCount_++;
    (void)keys;     // Suppress unused parameter warning
    (void)preKeys;  // Suppress unused parameter warning
    //bg_.Update();
    logo_.Update();
    // ... (same input and menu as original TitleScene)
    hoverOffset_ = std::sinf(frameCount_ * 0.04f) * 13.0f; // Same as in TitleLogo
}

void TitleScene2::Draw()
{
    //bg_.Draw();

    Novice::DrawBox(0, 0,
        1280, 720,
        0.0f,
        BLACK,
        kFillModeSolid
    );

   Novice::DrawSprite(0,0,
        bgTexture_,
        1.0f, 1.0f,
        0.0f,
		WHITE
    );

    logo_.Draw();
    
    float scale = 1.0f;

    Novice::DrawSprite(
        enterX_, // X position
        enterY_ + static_cast<int>(hoverOffset_), // Y position with hover animation
        enterTexture_,
        scale, scale,
        0.0f,
        WHITE);
}