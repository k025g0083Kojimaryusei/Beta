#include "TutorialScene.h"
#include <Novice.h>
#include <cmath>


TutorialScene::TutorialScene(SceneManager* manager)
	: sceneManager(manager), bg_(), tutorialBg_()
{
    //bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/credit3.png");
    enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");

    wasdTexHandles[0][0] = Novice::LoadTexture("./Textures/UI/Wkey1.png"); // W up
    wasdTexHandles[0][1] = Novice::LoadTexture("./Textures/UI/Wkey2.png"); // W down
    wasdTexHandles[1][0] = Novice::LoadTexture("./Textures/UI/Akey1.png"); // A up
    wasdTexHandles[1][1] = Novice::LoadTexture("./Textures/UI/Akey2.png"); // A down
    wasdTexHandles[2][0] = Novice::LoadTexture("./Textures/UI/Skey1.png"); // S up
    wasdTexHandles[2][1] = Novice::LoadTexture("./Textures/UI/Skey2.png"); // S down
    wasdTexHandles[3][0] = Novice::LoadTexture("./Textures/UI/Dkey1.png"); // D up
    wasdTexHandles[3][1] = Novice::LoadTexture("./Textures/UI/Dkey2.png"); // D down

    breathEasing_.Init(1.0f, 1.012f, 120, EasingType::EASING_EASE_IN_OUT_SINE); // scale: 1.0 <-> 1.012, 120 frames per cycle
    breathEasing_.Start();
    isBreathForward_ = true;
    Score::GetInstance()->ResetScore();





    miniGamePlay.Init();
}


void TutorialScene::Update(char* keys, char* preKeys)
{
    memcpy(keys_, keys, 256);

    Score::GetInstance()->ResetScore();

    bg_.Update();
	tutorialBg_.Update();



	miniGamePlay.Update(keys, preKeys);
	miniGamePlay.SetCameraZoom({ 0.5f, 0.5f });






    if (!preKeys[DIK_RETURN] && keys[DIK_RETURN])
    {
        sceneManager->ChangeScene(SceneType::Play);
        GameConfig::GetInstance()->SetCurrentWave(0);
        GameConfig::GetInstance()->SetCurrentStage(0);
        sceneManager->ChangeScene(SceneType::Play);
        SoundManager::Get().Stop("BGM");
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

void TutorialScene::Draw()
{
    Novice::DrawBox(100, 100, 200, 200, 0.0f, 0xFFFF0000, kFillModeSolid);
    bg_.Draw();
	tutorialBg_.Draw();



	miniGamePlay.DrawMainCamera();

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

    //float breathScale = breathEasing_.easingRate;

    //Novice::DrawSprite(
    //    posX_ - static_cast<int>(width_ * breathScale / 2),
    //    posY_ - static_cast<int>(height_ * breathScale / 2),
    //    bgTexture_,
    //    breathScale, breathScale,
    //    0.0f,
    //    /*tint/color*/
    //    WHITE
    //);

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
    // Get state for each key
    int keyW = (keys_[DIK_W]) ? 1 : 0;
    int keyA = (keys_[DIK_A]) ? 1 : 0;
    int keyS = (keys_[DIK_S]) ? 1 : 0;
    int keyD = (keys_[DIK_D]) ? 1 : 0;

    // Position (adjust as needed)
    int boxLeft = 860;
    int boxTop = 292;
    int gap = 0; // No gap; change if you want space between keys

    // Draw 4 keys horizontally, centered in the box
    Novice::DrawSprite(boxLeft + 42 + gap, boxTop, wasdTexHandles[0][keyW], 1.0f, 1.0f, 0.0f, WHITE); // W
    Novice::DrawSprite(boxLeft + 92 + gap, boxTop, wasdTexHandles[1][keyA], 1.0f, 1.0f, 0.0f, WHITE); // A
    Novice::DrawSprite(boxLeft + 142 + gap, boxTop, wasdTexHandles[2][keyS], 1.0f, 1.0f, 0.0f, WHITE); // S
    Novice::DrawSprite(boxLeft + 192 + gap, boxTop, wasdTexHandles[3][keyD], 1.0f, 1.0f, 0.0f, WHITE); // D
}