#include "ScoreScene.h"
#include <Novice.h>
#include <cmath>


ScoreScene::ScoreScene(SceneManager* manager)
    : sceneManager(manager), bg_()
{
    bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/score5.png");
    enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");

    breathEasing_.Init(1.0f, 1.012f, 120, EasingType::EASING_EASE_IN_OUT_SINE); // scale: 1.0 <-> 1.012, 120 frames per cycle
    breathEasing_.Start();
    isBreathForward_ = true;
	SoundManager::Get().Load("BGM", "./Sounds/bgm.mp3");
	SoundManager::Get().Play("BGM", 1.0f, true);
}

void ScoreScene::Update(char* keys, char* preKeys)
{

    bg_.Update();
	ScoreSystem::GetInstance()->InputName(keys, preKeys);
    if (!preKeys[DIK_RETURN] && keys[DIK_RETURN])
    {
		ScoreSystem::GetInstance()->Add(Score::GetInstance()->GetDisplayScore());
		ScoreSystem::GetInstance()->FocusOnLastAdded();
        sceneManager->ChangeScene(SceneType::Ranking);
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

void ScoreScene::Draw()
{

    bg_.Draw();

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

   ScoreSystem::GetInstance()->DrawScore(Score::GetInstance()->GetDisplayScore());

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