#include "CreditScene.h"
#include <Novice.h>
#include <cmath>


CreditScene::CreditScene(SceneManager* manager)
	: sceneManager(manager), bg_()
{
	bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/credit3.png");
	enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");

    breathEasing_.Init(1.0f, 1.012f, 120, EasingType::EASING_EASE_IN_OUT_SINE); // scale: 1.0 <-> 1.012, 120 frames per cycle
    breathEasing_.Start();
    isBreathForward_ = true;
}

void CreditScene::Update(char* keys, char* preKeys)
{

	bg_.Update();

	if (!preKeys[DIK_RETURN] && keys[DIK_RETURN])
	{
		sceneManager->ChangeScene(SceneType::Title);
	}
	frameCount_++;

	// In CreditScene.cpp, Update()
	bgBreathPhase_ += bgBreathSpeed_;
	//bgColorPhase_ += bgColorSpeed_;

	hoverOffset_ = std::sinf(frameCount_ * 0.04f) * 13.0f; // Same as in TitleLogo

    // In CreditScene::Update
    breathEasing_.Update();
    if (!breathEasing_.isMove) {
        // Flip direction for yoyo effect
        isBreathForward_ = !isBreathForward_;
        if (isBreathForward_) {
            breathEasing_.Init(1.0f, 1.012f, 120, EasingType::EASING_EASE_IN_OUT_SINE);
        }
        else {
            breathEasing_.Init(1.012f, 1.0f, 120, EasingType::EASING_EASE_IN_OUT_SINE);
        }
        breathEasing_.Start();
    }
}

void CreditScene::Draw()
{

	bg_.Draw();

    // Calculate breathing scale and color tint for the background
    //float breathScale = 1.0f + std::sin(bgBreathPhase_) * 0.012f;
    //int brightness = 200 + static_cast<int>(std::sin(bgColorPhase_) * 28);
    //unsigned int tint = 0xFF000000 | (brightness << 16) | (brightness << 8) | brightness;

    // Draw animated background

    /*Novice::DrawBox(0,0,
        1280, 720,
        0.0f,
        BLACK,
        kFillModeSolid
	);*/

    float breathScale = breathEasing_.easingRate;

    Novice::DrawSprite(
        posX_ - static_cast<int>(width_ * breathScale / 2),
        posY_ - static_cast<int>(height_ * breathScale / 2),
        bgTexture_,
        breathScale, breathScale,
        0.0f,
        /*tint/color*/
        WHITE
    );

    // Enter key animation (remains as before)
    float scale = 1.0f;
    Novice::DrawSprite(
        enterX_,
        enterY_ + static_cast<int>(hoverOffset_),
        enterTexture_,
        scale, scale,
        0.0f,
        WHITE
    );
}