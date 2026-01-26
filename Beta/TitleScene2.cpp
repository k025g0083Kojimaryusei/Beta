// TitleScene2.cpp
#include "TitleScene2.h"
#include <cmath>

TitleScene2::TitleScene2(SceneManager* manager)
    : sceneManager(manager), bg_(), logo_()
{
    enterTexture_ = Novice::LoadTexture("./Textures/UI/enter.png");
    bgTexture_ = Novice::LoadTexture("./Textures/UI/BackGround/B.png");

    // Menu: play, ranking, credit PNG (3 versions for each for glitch animation)
    btnTex_[0][0] = Novice::LoadTexture("./Textures/UI/Title/Aselect1.png");
    btnTex_[0][1] = Novice::LoadTexture("./Textures/UI/Title/Aselect2.png");
    btnTex_[0][2] = Novice::LoadTexture("./Textures/UI/Title/Aselect3.png");
    btnTex_[1][0] = Novice::LoadTexture("./Textures/UI/Title/Bselect1.png");
    btnTex_[1][1] = Novice::LoadTexture("./Textures/UI/Title/Bselect2.png");
    btnTex_[1][2] = Novice::LoadTexture("./Textures/UI/Title/Bselect3.png");
    btnTex_[2][0] = Novice::LoadTexture("./Textures/UI/Title/Cselect1.png");
    btnTex_[2][1] = Novice::LoadTexture("./Textures/UI/Title/Cselect2.png");
    btnTex_[2][2] = Novice::LoadTexture("./Textures/UI/Title/Cselect3.png");

    // Bar and cursor
    barTex_[0] = Novice::LoadTexture("./Textures/UI/Title/bar1.png");
    barTex_[1] = Novice::LoadTexture("./Textures/UI/Title/bar2.png");
    barTex_[2] = Novice::LoadTexture("./Textures/UI/Title/bar3.png");
    cursorTex_ = Novice::LoadTexture("./Textures/UI/Title/choice.png");

    // Initial values for select menu
    selectedIndex_ = 0;
    cursorCurrentY_ = static_cast<float>(menuTextY_[0]);
    noiseTimer_ = 0;

    // Logo slide positions (change here to move the red line!)
    logoCurrentX_ = logo_.GetCenterX();
    logoStartX_ = logo_.GetCenterX();
    logoTargetX_ = 304.0f; // aligns it to your left red line!
}

void TitleScene2::Update(char* keys, char* preKeys)
{

    bg_.Update();

    frameCount_++;
    hoverOffset_ = std::sinf(frameCount_ * 0.04f) * 13.0f;

    switch (state_) {
    case TitleState::Intro:
        logo_.Update();
        logoCurrentX_ = logo_.GetCenterX();
        if (logo_.IsIntroFinished()) state_ = TitleState::Shake;
        break;
    case TitleState::Shake:
        logo_.Update();
        logoCurrentX_ = logo_.GetCenterX();
        if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
            // Start logo slide animation to target
            logoSlideEasing_.Init(logoCurrentX_, logoTargetX_, 30, EasingType::EASING_EASE_OUT_QUAD); // 30 frames for slide
            logoSlideEasing_.Start();
            state_ = TitleState::SlideLeft;
        }
        break;
    case TitleState::SlideLeft:
        logoSlideEasing_.Update();
        logoCurrentX_ = logoSlideEasing_.easingRate;
        logo_.SetPosition(logoCurrentX_, logo_.GetCenterY());
        logo_.Update(); // <--- now shakes with effect
        if (!logoSlideEasing_.isMove) {
            state_ = TitleState::MenuActive;
        }
        break;
    case TitleState::MenuActive:
        logo_.SetPosition(logoTargetX_, logo_.GetCenterY());
        logo_.Update();

        noiseTimer_++;

        // Up/down input (arrow keys and W/S, just like your old TitleScene)
        if ((keys[DIK_UP] && !preKeys[DIK_UP]) || (keys[DIK_W] && !preKeys[DIK_W])) {
            selectedIndex_ = (selectedIndex_ + 2) % 3;
            noiseTimer_ = 0;
        }
        if ((keys[DIK_DOWN] && !preKeys[DIK_DOWN]) || (keys[DIK_S] && !preKeys[DIK_S])) {
            selectedIndex_ = (selectedIndex_ + 1) % 3;
            noiseTimer_ = 0;
        }

        // Enter key to select
        if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
            switch (selectedIndex_) {
            case 0: // Play
                sceneManager->ChangeScene(SceneType::Play);
                break;
            case 1: // Ranking
                sceneManager->ChangeScene(SceneType::Ranking);
                break;
            case 2: // Credit
                sceneManager->ChangeScene(SceneType::Credit);
                break;
            }
        }

        // Easing toward currently selected menu text Y
        cursorCurrentY_ += ((float)menuTextY_[selectedIndex_] - cursorCurrentY_) * kCursorEasingSpeed;

        if (noiseTimer_ >= 60) noiseTimer_ = 0;
        break;
    }
}

void TitleScene2::Draw()
{
    bg_.Draw();

   /* Novice::DrawSprite(
        0, 0,
        bgTexture_,
        1.0f, 1.0f,
        0.0f,
        WHITE
    );*/

    logo_.DrawAt(logoCurrentX_, logo_.GetCenterY());

    Novice::DrawSprite(
        enterX_,
        enterY_ + static_cast<int>(hoverOffset_),
        enterTexture_, 1.0f, 1.0f, 0.0f, WHITE
    );

    if (state_ == TitleState::MenuActive) {
        // Draw bar under the selected item (uses fixed position array)
        Novice::DrawSprite(
            barX_[selectedIndex_], barY_[selectedIndex_],
            barTex_[selectedIndex_], 1.0f, 1.0f, 0.0f, WHITE
        );

        Novice::DrawSprite(
            cursorX_ - 56,
            static_cast<int>(cursorCurrentY_) + cursorYOffset_,
            cursorTex_, 1.0f, 1.0f, 0.0f, WHITE
        );

        // Draw menu text with possible glitch frames
        for (int i = 0; i < 3; ++i) {
            int frame = 0;
            if (i == selectedIndex_ && noiseTimer_ < 15) {
                frame = (noiseTimer_ / 5) % 3;
            }
            Novice::DrawSprite(menuTextX_[i], menuTextY_[i], btnTex_[i][frame], 1.0f, 1.0f, 0.0f, WHITE);
        }
    }
}