// TitleScene2.cpp
#include "TitleScene2.h"

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
    cursorCurrentY_ = float(menuBaseY_);
    noiseTimer_ = 0;

    // Logo slide positions (change here to move the red line!)
    logoCurrentX_ = logo_.GetCenterX();
    logoStartX_ = logo_.GetCenterX();
    logoTargetX_ = 360.0f; // aligns it to your left red line!
}

void TitleScene2::Update(char* keys, char* preKeys)
{
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
        // Check for Enter to slide logo left
        if (!preKeys[DIK_RETURN] && keys[DIK_RETURN]) {
            logoStartX_ = logo_.GetCenterX();
            logoSlideT_ = 0.0f;
            state_ = TitleState::SlideLeft;
        }
        break;
    case TitleState::SlideLeft: {
        logoSlideT_ += logoSlideSpeed_;
        if (logoSlideT_ > 1.0f) logoSlideT_ = 1.0f;
        float t = logoSlideT_;
        float easeT = 1.0f - (1.0f - t) * (1.0f - t); // ease out
        logoCurrentX_ = logoStartX_ + (logoTargetX_ - logoStartX_) * easeT;
        logo_.SetPosition(logoCurrentX_, logo_.GetCenterY());
        logo_.UpdateShakeOnly();
        if (logoSlideT_ >= 1.0f) state_ = TitleState::MenuActive;
        break;
    }
    case TitleState::MenuActive:
        logo_.SetPosition(logoTargetX_, logo_.GetCenterY());
        logo_.UpdateShakeOnly();

        noiseTimer_++;

        // Menu navigation
        if (keys[DIK_UP] && !preKeys[DIK_UP])    selectedIndex_ = (selectedIndex_ + 2) % 3;
        if (keys[DIK_DOWN] && !preKeys[DIK_DOWN])selectedIndex_ = (selectedIndex_ + 1) % 3;
        // Cursor Y easing
        float targetY = float(menuBaseY_ + menuSpacingY_ * selectedIndex_);
        cursorCurrentY_ += (targetY - cursorCurrentY_) * kCursorEasingSpeed;

        if (noiseTimer_ >= 60) noiseTimer_ = 0;

        // Scene select (optional)
        if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
            nextSceneIndex_ = selectedIndex_;
        }

        break;
    }
}

void TitleScene2::Draw()
{
    // Optionally: bg_.Draw();
    Novice::DrawSprite(
        0, 0,
        bgTexture_,
        1.0f, 1.0f, 0.0f, WHITE
	);

    // Logo at current X
    logo_.DrawAt(logoCurrentX_, logo_.GetCenterY());

    // Always draw Enter key in bottom right (hover effect)
    Novice::DrawSprite(
        enterX_,
        enterY_ + static_cast<int>(hoverOffset_),
        enterTexture_,
        1.0f, 1.0f, 0.0f, WHITE
    );

    // -- Menu (after logo slides left and stays)
    if (state_ == TitleState::MenuActive) {
        for (int i = 0; i < 3; ++i) {
            int btnY = menuBaseY_ + menuSpacingY_ * i;
            int frame = 0;
            if (i == selectedIndex_ && noiseTimer_ < 15) {
                frame = (noiseTimer_ / 5) % 3;
            }
            // Menu word
            Novice::DrawSprite(menuBaseX_, btnY, btnTex_[i][frame], 1.0f, 1.0f, 0.0f, WHITE);

            // Bar under selected
            if (i == selectedIndex_) {
                // Draw bar directly below each menu word
                Novice::DrawSprite(
                    menuBaseX_, btnY + barGapY_,
                    barTex_[i], 1.0f, 1.0f, 0.0f, WHITE
                );
                // Draw cursor to left of menu word
                Novice::DrawSprite(
                    menuBaseX_ + cursorGapX_,
                    btnY,
                    cursorTex_, 1.0f, 1.0f, 0.0f, WHITE
                );
            }
        }
    }
}